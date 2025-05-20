#include <AltSoftSerial.h>

AltSoftSerial ESP;       // 미리 정해진 핀 사용

void setup() {
  Serial.begin(9600);       // 컴퓨터와의 시리얼 통신 초기화
  ESP.begin(9600);      // ESP 모듈과의 시리얼 통신 초기화
}

void loop() {
  if (Serial.available()) {       // 시리얼 모니터 → 아두이노 → ESP 모듈
    char ch = Serial.read();
    Serial.write(ch);
    ESP.write(ch);
  }

  if (ESP.available()) {      // ESP 모듈 → 아두이노 → 시리얼 모니터
    char ch = ESP.read();
    Serial.write(ch);
  }
}
