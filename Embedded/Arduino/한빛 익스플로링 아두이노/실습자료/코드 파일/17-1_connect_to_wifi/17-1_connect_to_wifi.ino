// WINC1500 칩을 사용하는 Feather M0 보드를 와이파이 네트워크에 연결

#include <SPI.h>
#include <WiFi101.h>

// 와이파이 네트워크 정보 : 네트워크 이름(SSID)와 비밀번호
const char WIFI_SSID[] = "네트워크 이름";
const char WIFI_PASSWORD[] = "네트워크 비밀번호";

// 연결 상태를 나타내기 위해 내장 LED 사용
const int ONBOARD_LED = 13;

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
  WiFi.setTimeout(5000);      // 와이파이 연결을 위해 최대 5초 대기 while (wifi_status != WL_CONNECTED)
  {
    wifi_status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  }
  Serial.println("Connected!\n");
  // 와이파이 네트워크에 연결되었으면 내장 LED를 켬
  digitalWrite(ONBOARD_LED, HIGH);

  // DHCP를 통해 할당받은 IP 주소 출력
  IPAddress ip = WiFi.localIP();
  Serial.print("This Arduino's IP is: ");
  Serial.println(ip);
  Serial.println("");
}

void loop()
{
  // 아무런 작업도 하지 않음
}
