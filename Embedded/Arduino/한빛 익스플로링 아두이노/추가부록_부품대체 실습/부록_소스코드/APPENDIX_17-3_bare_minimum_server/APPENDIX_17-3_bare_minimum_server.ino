#include <AltSoftSerial.h>
#include <WiFiEsp.h>

AltSoftSerial ESP;       // 미리 정해진 핀 사용

// 와이파이 네트워크 정보 : 네트워크 이름(SSID)와 비밀번호
char WIFI_SSID[] = "네트워크 이름";
char WIFI_PASSWORD[] = "네트워크 비밀번호";

// 클라이언트 데이터 수신 버퍼 제어
const int MAX_LENGTH = 200;
char incoming_line[MAX_LENGTH + 1], ch;
int index;

// 와이파이 액세스 포인트와의 연결 상태 관리
int wifi_status = WL_IDLE_STATUS;

WiFiEspServer server(80);

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 시리얼 통신 초기화
  ESP.begin(9600);      // 와이파이 모듈과의 시리얼 통신 초기화

  WiFi.init(&ESP);      // ESP-01 모듈 초기화

  Serial.print("연결할 액세스 포인트 : ");
  Serial.println(WIFI_SSID);

  wifi_status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  if (wifi_status != WL_CONNECTED) {
    Serial.println("** AP에 연결할 수 없습니다.");
    while (1);
  }
  else {
    Serial.println("* AP에 연결되었습니다.");
    Serial.println();
  }

  // 서버 시작
  server.begin();
  Serial.println("서버가 시작되었습니다!");

  // DHCP를 통해 할당받은 IP 주소 출력
  IPAddress ip = WiFi.localIP();
  Serial.print("아두이노를 컨트롤하기 위해 접속할 주소 : http://");
  Serial.println(ip);
  Serial.println();
}

void loop() {
  // 클라이언트 요청 검사
  WiFiEspClient client = server.available();

  // 클라이언트(브라우저)의 요청을 서버가 수신한 경우
  if (client) {
    Serial.println("** 새로운 클라이언트가 연결되었습니다.");

    // 클라이언트가 연결되어 있으면 줄 단위로 데이터를 수신
    while (client.connected()) {
      index = 0;

      // do-while 루프를 사용하여 첫 번째 문자를 수신하여 저장하기 전에는
      // 형식 검사가 이루어지지 않도록 함
      do {
        while (!client.available());    // 바이트 데이터 수신 대기
        ch = client.read();     // 수신 데이터 읽기

        incoming_line[index] = ch;
        index = (index + 1) % MAX_LENGTH;
      } while (ch != '\n');
      incoming_line[index] = 0;

      Serial.print(incoming_line);    // 줄 단위 데이터 출력

      // 현재 수신한 줄이 ‘\r’과 ‘\n’ 만으로 이루어진 빈 줄인 경우
      // HTTP 요청 데이터 수신이 끝남
      if (strlen(incoming_line) == 2 && incoming_line[1] == '\n') {
        // HTTP 요청에 대해 코드 200을 사용하여 응답 전송
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection:close");
        client.println();

        // 현재 클라이언트와의 연결 종료
        while(client.connected()) {
          client.flush();
          client.stop();
          delay(100);
        }
      }
    }
  }
}
