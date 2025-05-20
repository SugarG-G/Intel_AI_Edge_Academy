// 아두이노 웹 서버를 통해 LED와 피에조 버저 제어
// 일부 코드는 Tom Igoe가 작성한 아두이노의 예제에서 발췌하여 사용하였음

#include <SPI.h>
#include <WiFi101.h>

// 와이파이 네트워크 정보 : 네트워크 이름(SSID)와 비밀번호
const char WIFI_SSID[] = "네트워크 이름";
const char WIFI_PASSWORD[] = "네트워크 비밀번호";

// 연결 상태를 나타내기 위해 내장 LED 사용
const int ONBOARD_LED = 13;

// HTML 폼을 통해 제어할 핀 번호
const int RED = 5;
const int GREEN = 10;
const int BLUE = 11;
const int SPEAKER = A5;

// 서버는 HTTP 표준 포트인 80번 포트로 클라이언트 요청 대기
WiFiServer server(80);

// 와이파이 액세스 포인트와의 연결 상태 관리
int wifi_status = WL_IDLE_STATUS;

void setup()
{
  // 와이파이 칩을 위한 연결 핀 설정
  WiFi.setPins(8, 7, 4, 2);

  // LED 연결 핀 설정
  pinMode(ONBOARD_LED, OUTPUT);
  digitalWrite(ONBOARD_LED, LOW);
  pinMode(RED, OUTPUT);
  digitalWrite(RED, HIGH);  // 공통 양극 방식 RGB LED로 HIGH를 출력하면 꺼짐
  pinMode(GREEN, OUTPUT);
  digitalWrite(GREEN, HIGH);  // 공통 양극 방식 RGB LED로 HIGH를 출력하면 꺼짐
  pinMode(BLUE, OUTPUT);
  digitalWrite(BLUE, HIGH);   // 공통 양극 방식 RGB LED로 HIGH를 출력하면 꺼짐

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
    String command = "";
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

      // GET에 의한 요청 수행
      // "GET /?L=10 HTTP/1.1"과 같은 형식을 가지는 데이터 해석
      if (incoming_line.startsWith("GET /?"))
      {
        // "L=10" 형식의 명령 분리
        command = incoming_line.substring(6, incoming_line.indexOf(" HTTP/1.1"));
      }

      // 현재 수신한 줄이 ‘\r’과 ‘\n’ 만으로 이루어진 빈 줄인 경우
      // HTTP 요청 데이터 수신이 끝남
      if (incoming_line == "\r\n")
      {
        // 완료된 요청에 대해 폼 페이지를 응답으로 전송
        // 응답 코드 200 : 요청을 정상적으로 수신하였음을 나타냄
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println();

        // 빨간색 LED 토글 버튼을 누른 경우
        client.print("<form action='' method='get'>");
        client.print("<input type='hidden' name='L' value='" + String(RED) + "' />");
        client.print("<input type='submit' value='Toggle Red' />");
        client.print("</form>");

        // 초록색 LED 토글 버튼을 누른 경우
        client.print("<form action='' method='get'>");
        client.print("<input type='hidden' name='L' value='" + String(GREEN) + "' />");
        client.print("<input type='submit' value='Toggle Green' />");
        client.print("</form>");

        // 파란색 LED 토글 버튼을 누른 경우
        client.print("<form action='' method='get'>");
        client.print("<input type='hidden' name='L' value='" + String(BLUE) + "'/>");
        client.print("<input type='submit' value='Toggle Blue' />");
        client.print("</form>");

        // 스피커를 위한 재생 주파수 조정 슬라이드바
        client.print("<form action='' method='get'>");
        client.print(
          "<input type='range' name='S' min='0' max='1000' step='100' value='0'/>");
        client.print("<input type='submit' value='Set Frequency' />");
        client.print("</form>");

        // 다른 하드웨어 제어를 위해 다른 폼을 여기에 추가할 수 있음

        // HTTP 응답의 끝을 나타내기 위한 빈 줄
        client.println();

        // 현재 클라이언트와의 연결 종료
        delay(50);
        client.stop();

        // 수신된 명령에 따라 하드웨어 제어
        if (command.startsWith("L="))
        {
          int led_pin = command.substring(2).toInt();
          Serial.print("TOGGLING PIN: ");
          Serial.println(led_pin);
          Serial.println("");
          digitalWrite(led_pin, !digitalRead(led_pin));
        }
        else if (command.startsWith("S="))
        {
          int speaker_freq = command.substring(2).toInt();
          Serial.print("SETTING SPEAKER FREQUENCY TO: ");
          Serial.println(speaker_freq);
          Serial.println("");
          if (speaker_freq == 0) noTone(SPEAKER);
          else tone(SPEAKER, speaker_freq);
        }
        
        // 다른 명령 처리를 위해 'else if' 문을 추가할 수 있음
        
      }
    }
  }
}
