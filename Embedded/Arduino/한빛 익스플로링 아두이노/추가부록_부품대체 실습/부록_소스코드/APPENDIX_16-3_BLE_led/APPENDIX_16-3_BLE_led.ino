#include <SoftwareSerial.h>

SoftwareSerial HM10(3, 2);     // (RX, TX) -> HM-10의 (TX, RX)

// 제어할 LED는 5번 핀에 연결되어 있음
const int CTRL_LED = 5;

// LED 상태와 제어 및 반환 문자열을 위한 변수
bool led_state = LOW;
String cmd = "";
String reply = "";

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 시리얼 통신 초기화
  HM10.begin(9600);       // 블루투스 모듈과의 시리얼 통신 초기화

  pinMode(CTRL_LED, OUTPUT);
}

void loop() {
  // 수신 데이터가 있으면 읽어 LED 제어 명령을 찾아낸다.
  while (HM10.available() > 0) {
    // 새 줄 문자를 만날 때까지 수신 데이터를 읽어 버퍼에 저장한다.
    cmd = HM10.readStringUntil('\n');
    Serial.print(F("Received Command: "));
    Serial.println(cmd);

    // 소문자로 변환하여 대소문자 관계없이 명령을 인식할 수 있도록 한다.
    cmd.toLowerCase();

    // "red" 또는 "led" 문자열이 발견되면 해석을 시작한다.
    if (cmd.indexOf(F("red")) != -1 || cmd.indexOf(F("led")) != -1) {
      // "on" 포함 여부 검사
      if (cmd.indexOf(F("on")) != -1) {   // "on"이 포함된 경우
        led_state = HIGH;
        reply = F("OK! The LED has been turned on.");
      }

      // "off" 포함 여부 검사
      else if (cmd.indexOf(F("off")) != -1) {
        led_state = LOW;
        reply = F("OK! The LED has been turned off.");
      }

      // "toggle" 포함 여부 검사
      else if (cmd.indexOf(F("toggle")) != -1) {
        led_state = !led_state;
        if (led_state) reply = F("OK! The LED has been toggled on.");
        else reply = F("OK! The LED has been toggled off.");
      }

      // "red" 또는 "led"가 포함되어 있지만 LED 제어 키워드가 포함되어 있지 않음
      else {
        if (led_state) reply = F("The LED is currently on.");
        else reply = F("The LED is currently off.");
      }

      // LED 상태 설정
      digitalWrite(CTRL_LED, led_state);
    }
    else {
      reply = F("Command not understood.");
    }

    // 수신한 명령 문자열에 대한 응답 전송
    HM10.println(reply);
    Serial.print(F("Replied With: "));
    Serial.println(reply);
  }
}
