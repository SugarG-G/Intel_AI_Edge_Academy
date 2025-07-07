#include <AltSoftSerial.h>
#include <WiFiEsp.h>

AltSoftSerial ESP;       // 미리 정해진 핀 사용

// 와이파이 네트워크 정보 : 네트워크 이름(SSID)와 비밀번호
char WIFI_SSID[] = "네트워크 이름";
char WIFI_PASSWORD[] = "네트워크 비밀번호";

// API 요청을 위한 상수
const char SERVER[] = "api.openweathermap.org";
const char HOST_STRING[] = "HOST: api.openweathermap.org";
const String API_KEY = "사용자의 API 키";
const String CITY = "Busan";    // 원하는 도시 이름 지정

// 연결 상태를 나타내기 위해 내장 LED 사용
const int ONBOARD_LED = 13;

// 데이터 수신 버퍼 제어
const int MAX_LENGTH = 200;
char json[MAX_LENGTH + 1], ch;
int index;

// 아두이노는 클라이언트로 동작
WiFiEspClient client;

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
    Serial.println(F("** AP에 연결할 수 없습니다."));
    while (1);
  }
  else {
    Serial.println(F("* AP에 연결되었습니다."));
    Serial.println();
  }

  // API 요청 준비
  String request = "GET /data/2.5/weather?units=metric&q=" +
          CITY +
          "&appid=" +
          API_KEY +
          " HTTP/1.1";

  // 서버에 연결하고 API 요청 전송
  if (client.connect(SERVER, 80)) {
    Serial.println(F("Sending Request: "));
    Serial.println(request);
    Serial.println("");
    client.println(request);
    client.println(HOST_STRING);
    client.println(F("Connection: close"));
    client.println();
  }

  // 서버 응답 대기
  while (!client.available());

  // '{'로 시작되는 JSON 객체를 수신하기 전에 서버에서 수신한 헤더 데이터는
  // 사용하지는 않지만, 디버깅을 위해 헤더 데이터를 시리얼 모니터로 출력한다.
  while (true) {
    char h = client.read();
    if (h == '{') break;
    Serial.print(h);
  }

  // JSON 형식 데이터 수신이 시작되면 문자열로 저장
  index = 0;
  do {
    ch = client.read();
    if (index < MAX_LENGTH) {
      json[index] = ch;
      index++;
    }

    Serial.print(ch);
  } while (client.connected());
  json[index] = 0;

  char *ptr = strstr(json, "\"temp\":");
  Serial.print("\nTemperature = ");
  for (int i = 0; ; i++) {
    ch = ptr[7 + i];
    if (ch == ',') break;
    Serial.print(ch);
  }
  Serial.println("C");
}

void loop() {
  // setup() 함수에서 한 번만 데이터를 얻어 표시하므로 loop() 함수는 비어 있다.
}
