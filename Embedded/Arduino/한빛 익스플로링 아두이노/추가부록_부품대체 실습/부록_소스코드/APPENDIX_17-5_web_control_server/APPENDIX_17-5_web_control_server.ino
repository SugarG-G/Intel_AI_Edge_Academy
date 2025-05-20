#include <AltSoftSerial.h>
#include <WiFiEsp.h>

AltSoftSerial ESP;       // 미리 정해진 핀 사용

// 와이파이 네트워크 정보 : 네트워크 이름(SSID)와 비밀번호
char WIFI_SSID[] = "네트워크 이름";
char WIFI_PASSWORD[] = "네트워크 비밀번호";

// 클라이언트 데이터 수신 버퍼 제어
const int MAX_LENGTH = 100;
char incoming_line[MAX_LENGTH + 1], ch;
int index;

// 와이파이 액세스 포인트와의 연결 상태 관리
int wifi_status = WL_IDLE_STATUS;

// HTML 폼을 통해 제어할 핀 번호
const int RED = 5;
const int GREEN = 10;
const int BLUE = 11;
const int SPEAKER = A5;

WiFiEspServer server(80);

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 시리얼 통신 초기화
  ESP.begin(9600);      // 와이파이 모듈과의 시리얼 통신 초기화

  // LED 연결 핀 설정
  pinMode(RED, OUTPUT);
  digitalWrite(RED, HIGH);  // 공통 양극 방식 RGB LED로 HIGH를 출력하면 꺼짐
  pinMode(GREEN, OUTPUT);
  digitalWrite(GREEN, HIGH);  // 공통 양극 방식 RGB LED로 HIGH를 출력하면 꺼짐
  pinMode(BLUE, OUTPUT);
  digitalWrite(BLUE, HIGH);   // 공통 양극 방식 RGB LED로 HIGH를 출력하면 꺼짐

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
    String command = "";

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

      // GET에 의한 요청 수행
      // "GET /?L=10 HTTP/1.1"과 같은 형식을 가지는 데이터 해석
      if (strstr(incoming_line, "GET")) {
        Serial.print(incoming_line);  // 'GET'으로 시작하는 문장만 출력

        // "L=10" 형식의 명령 분리
        for (int i = 6; ; i++) {
          if (incoming_line[i] == ' ' || incoming_line[i] == '\n') {
            break;
          }
          command += incoming_line[i];
        }
        Serial.println(String(" => 분리된 명령 : ") + command); 
      }

      // 현재 수신한 줄이 ‘\r’과 ‘\n’ 만으로 이루어진 빈 줄인 경우
      // HTTP 요청 데이터 수신이 끝남
      if (strlen(incoming_line) == 2 && incoming_line[1] == '\n') {
        // 완료된 요청에 대해 폼 페이지를 응답으로 전송
        // 응답 코드 200 : 요청을 정상적으로 수신하였음을 나타냄
        client.println(F("HTTP/1.1 200 OK"));
        client.println(F("Content-type:text/html"));
        client.println(F("Connection:close"));
        client.println();

        client.println(F("<!DOCTYPE HTML>"));   // 데이터 시작
        client.println(F("<html>"));

        // favicon.ico 요청을 없애기 위해 추가
        client.println(F("<head>"));
        client.println(F("<link rel='icon' href='data:,'>"));
        client.println(F("</head>"));

        client.println(F("<body>"));

        // 빨간색 LED 토글 버튼을 누른 경우
        client.print(F("<form action='' method='get'>"));
        client.print(F("<input type='hidden' name='L' value='5' />"));
        client.print(F("<input type='submit' value='Toggle Red' />"));
        client.print(F("</form>"));

        // 초록색 LED 토글 버튼을 누른 경우
        client.print(F("<form action='' method='get'>"));
        client.print(F("<input type='hidden' name='L' value='10' />"));
        client.print(F("<input type='submit' value='Toggle Green' />"));
        client.print(F("</form>"));

        // 파란색 LED 토글 버튼을 누른 경우
        client.print(F("<form action='' method='get'>"));
        client.print(F("<input type='hidden' name='L' value='11'/>"));
        client.print(F("<input type='submit' value='Toggle Blue' />"));
        client.print(F("</form>"));

        // 스피커를 위한 재생 주파수 조정 슬라이드바
        client.print(F("<form action='' method='get'>"));
        client.print(
        F("<input type='range' name='S' min='0' max='1000' step='100' value='0'/>"));
        client.print(F("<input type='submit' value='Set Frequency' />"));
        client.print(F("</form>"));

        // 다른 하드웨어 제어를 위해 다른 폼을 여기에 추가할 수 있음

        client.println(F("</html>"));
        client.println(F("</body>"));

        // HTTP 응답의 끝을 나타내기 위한 빈 줄
        client.println();

        // 현재 클라이언트와의 연결 종료

        while (client.connected()) {
          client.flush();       // 수신 버퍼 비우기
          client.stop();
          delay(100);
        }

        // 수신된 명령에 따라 하드웨어 제어
        if (command.startsWith("L=")) {
          int led_pin = command.substring(2).toInt();
          Serial.print(" => TOGGLING PIN: ");
          Serial.println(led_pin);
          Serial.println();
          digitalWrite(led_pin, !digitalRead(led_pin));
        }
        else if (command.startsWith("S=")) {
          int speaker_freq = command.substring(2).toInt();
          Serial.print(" => SETTING SPEAKER FREQUENCY TO: ");
          Serial.println(speaker_freq);
          Serial.println();
          if (speaker_freq == 0) noTone(SPEAKER);
          else tone(SPEAKER, speaker_freq);
        }
        else {
          Serial.println();
        }

        // 다른 명령 처리를 위해 'else if' 문을 추가할 수 있음

      }
    }
  }
}
