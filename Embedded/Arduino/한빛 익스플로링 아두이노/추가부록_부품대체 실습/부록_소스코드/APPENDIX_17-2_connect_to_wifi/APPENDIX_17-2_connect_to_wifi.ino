#include <AltSoftSerial.h>
#include <WiFiEsp.h>

AltSoftSerial ESP;       // 미리 정해진 핀 사용

// 와이파이 네트워크 정보 : 네트워크 이름(SSID)와 비밀번호
char WIFI_SSID[] = "네트워크 이름";
char WIFI_PASSWORD[] = "네트워크 비밀번호";

// 와이파이 액세스 포인트와의 연결 상태 관리
int wifi_status = WL_IDLE_STATUS;

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

  // DHCP를 통해 할당받은 IP 주소 출력
  IPAddress ip = WiFi.localIP();
  Serial.print("아두이노의 IP 주소 : ");
  Serial.println(ip);
}

void loop() {
  // 아무런 작업도 하지 않음
}
