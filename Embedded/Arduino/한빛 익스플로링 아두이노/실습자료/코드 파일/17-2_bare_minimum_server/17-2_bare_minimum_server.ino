// 아두이노를 사용한 간단한 서버
// 일부 코드는 Tom Igoe가 작성한 아두이노의 예제에서 발췌하여 사용하였음

#include <SPI.h>
#include <WiFi101.h>

// 와이파이 네트워크 정보 : 네트워크 이름(SSID)와 비밀번호
const char WIFI_SSID[] = "네트워크 이름";
const char WIFI_PASSWORD[] = "네트워크 비밀번호";

// 연결 상태를 나타내기 위해 내장 LED 사용
const int ONBOARD_LED = 13;

// 서버는 HTTP 표준 포트인 80번 포트로 클라이언트 요청 대기
WiFiServer server(80);

// 와이파이 액세스 포인트와의 연결 상태 관리
int wifi_status = WL_IDLE_STATUS;

void setup()
{
  // 와이파이 칩을 위한 연결 핀 설정
  WiFi.setPins(8, 7, 4, 2);

  // LED 연결 핀을 출력으로 설정하고 끈 상태로 둠
  pinMode(ONBOARD_LED, OUTPUT);
  digitalWrite(ONBOARD_LED, LOW);

  // 시리얼 인터페이스 시작
  Serial.begin(9600);

  // M0는 하드웨어로 지원되는 USB 인터페이스를 가지고 있으므로
  // 와이파이 모듈을 초기화하기 전에 시리얼 모니터와 연결되어야 한다면
  // 아래 문장을 주석으로 처리하지 않고 그대로 두어야 한다. 
  // 시리얼 모니터를 사용하지 않거나 배터리로 동작하는 경우라면
  // 아래 문장을 주석으로 처리하는 것이 좋다. 
  while (!Serial);

  Serial.print("Connecting to: ");
  Serial.println(WIFI_SSID);
  WiFi.setTimeout(5000);      // 와이파이 연결을 위해 최대 5초 대기
  while (wifi_status != WL_CONNECTED)
  {
    wifi_status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  }
  Serial.println("Connected!\n");
  // 와이파이 네트워크에 연결되었으면 내장 LED를 켬
  digitalWrite(ONBOARD_LED, HIGH);

  // 서버 시작
  server.begin();
  Serial.println("Server Started!");

  // DHCP를 통해 할당받은 IP 주소 출력
  IPAddress ip = WiFi.localIP();
  Serial.print("Control this Arduino at: http://");
  Serial.println(ip);
  Serial.println("");
}

void loop()
{
  // 클라이언트 요청 검사
  WiFiClient client = server.available();

  // 클라이언트(브라우저)의 요청을 서버가 수신한 경우
  if (client)
  {
    // 클라이언트가 연결되어 있으면 줄 단위로 데이터를 수신
    while (client.connected())
    {
      // 수신 데이터를 줄 단위로 읽음
      String incoming_line = "";
      // do-while 루프를 사용하여 첫 번째 문자를 수신하여 저장하기 전에는
      // 형식 검사가 이루어지지 않도록 함
      do
      {
        while (!client.available());    // 바이트 데이터 수신 대기
        char c = client.read();     // 수신 데이터 읽기
        incoming_line += c;     // 현재 줄에 이어 붙이기
      } while (!incoming_line.endsWith("\r\n"));

      Serial.print(incoming_line);    // 줄 단위 데이터 출력

      // 현재 수신한 줄이 ‘\r’과 ‘\n’ 만으로 이루어진 빈 줄인 경우
      // HTTP 요청 데이터 수신이 끝남
      if (incoming_line == "\r\n")
      {
        // HTTP 요청에 대해 코드 200을 사용하여 응답 전송
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println();

        // 현재 클라이언트와의 연결 종료
        delay(50);
        client.stop();
      }
    }
  }
}
