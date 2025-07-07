// 웹에서 실시간 날씨 데이터 얻어 7세그먼트 표시장치에 온도 표시하기

#include <SPI.h>
#include <WiFi101.h>
#include <Arduino_JSON.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

// 와이파이 네트워크 정보 : 네트워크 이름(SSID)와 비밀번호
const char WIFI_SSID[] = "네트워크 이름";
const char WIFI_PASSWORD[] = "네트워크 비밀번호";

// API 요청을 위한 상수
const char SERVER[] = "api.openweathermap.org";
const char HOST_STRING[] = "HOST: api.openweathermap.org";
const String API_KEY = "사용자의 API 키";
const String CITY = "Busan";     // 원하는 도시 이름 지정
String UNITS = "F";     // F(화씨) 또는 C(섭씨)

// 연결 상태를 나타내기 위해 내장 LED 사용
const int ONBOARD_LED = 13;

// 7세그먼트 표시장치 객체 생성
Adafruit_7segment seven_seg_display = Adafruit_7segment();

// 아두이노는 클라이언트로 동작
WiFiClient client;

// 와이파이 액세스 포인트와의 연결 상태 관리
int wifi_status = WL_IDLE_STATUS;

void setup()
{
  // 와이파이 칩을 위한 연결 핀 설정
  WiFi.setPins(8, 7, 4, 2);

  // LED 연결 핀 설정
  pinMode(ONBOARD_LED, OUTPUT);
  digitalWrite(ONBOARD_LED, LOW);

  // 7세그먼트 표시장치의 I2C 주소 설정
  seven_seg_display.begin(0x70);

  // 시리얼 인터페이스 시작
  Serial.begin(9600);

  // M0는 하드웨어로 지원되는 USB 인터페이스를 가지고 있으므로
  // 와이파이 모듈을 초기화하기 전에 시리얼 모니터와 연결되어야 한다면
  // 아래 문장을 주석으로 처리하지 않고 그대로 두어야 한다. 
  // 시리얼 모니터를 사용하지 않거나 배터리로 동작하는 경우라면
  // 아래 문장을 주석으로 처리하는 것이 좋다. 
  // while(!Serial);

  Serial.println("Web-Connected Temperature Display");

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
}

void loop()
{
  // API 요청 준비
  String api_units = "metric";
  if (UNITS == "F")
  {
    api_units = "imperial";
  }
  String request =  "GET /data/2.5/weather?units=" +
                api_units +
                "&q=" +
                CITY +
                "&appid=" +
                API_KEY +
                " HTTP/1.1";

  // 서버에 연결하고 API 요청 전송
  if (client.connect(SERVER, 80))
  {
    Serial.println("Sending Request: ");
    Serial.println(request);
    Serial.println("");
    client.println(request);
    client.println(HOST_STRING);
    client.println("Connection: close");
    client.println();
  }

  // 서버 응답 대기
  while (!client.available());

  // '{'로 시작되는 JSON 객체를 수신하기 전에 서버에서 수신한 헤더 데이터는 
  // 사용하지는 않지만, 디버깅을 위해 헤더 데이터를 시리얼 모니터로 출력한다. 
  while (true)
  {
    char h = client.read();
    if (h == '{') break;
    Serial.print(h);
  }

  // JSON 형식 데이터 수신이 시작되면 문자열로 저장
  String json = "{";
  do
  {
    char c = client.read();
    json += c;
  } while (client.connected());
  client.stop();
  JSONVar api_object = JSON.parse(json);
  Serial.println("Raw JSON:");
  Serial.println(api_object);
  double temp = (double) api_object["main"]["temp"];
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.println(UNITS);

  // 온도 정보를 시리얼 모니터에 표시
  int temp_round = constrain(round(temp), -99, 999);
  Serial.print("Displaying: ");
  Serial.print(temp_round);
  Serial.println(UNITS);

  // 오른쪽 정렬로 표시되므로 10을 곱해 왼쪽으로 한 자리 이동
  // 오른쪽 끝에는 "C"나 "F"의 온도 단위 기호 표시
  seven_seg_display.print(temp_round * 10);

  // 온도 기호 표시
  seven_seg_display.writeDigitRaw(2, 0x10);

  // 온도 단위 기호 표시
  if (UNITS == "F")
  {
    seven_seg_display.writeDigitRaw(4, 0x71);   // "F" 출력
    UNITS = "C";        // 다음 출력은 섭씨로 출력
  }
  else
  {
    seven_seg_display.writeDigitRaw(4, 0x39);   // "C" 출력
    UNITS = "F";        // 다음 출력은 화씨로 출력
  }

  // 7세그먼트 표시장치로 출력
  seven_seg_display.writeDisplay();

  // 온도 정보를 다시 얻어오기 전에 1분 대기
  Serial.print("Waiting one minute before next check.");
  for (int i = 0; i < 60; i++)
  {
    Serial.print(".");
    delay(1000);          // 1초 대기
  }
  Serial.println("");
  Serial.println("");
}
