#include <SoftwareSerial.h>

SoftwareSerial HM10(3, 2);     // (RX, TX) -> HM-10의 (TX, RX)

const int POT = A0;       // 가변저항을 A0 핀에 연결

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 시리얼 통신 초기화
  HM10.begin(9600);       // 블루투스 모듈과의 시리얼 통신 초기화
}

void loop() {
  int val = analogRead(POT);

  // 시리얼 모니터로 가변저항값 출력
  Serial.print(F("Analog Value: "));
  Serial.println(val);

  HM10.println(val);      // 스마트폰으로 가변저항 값 전송

  delay(1000);
}
