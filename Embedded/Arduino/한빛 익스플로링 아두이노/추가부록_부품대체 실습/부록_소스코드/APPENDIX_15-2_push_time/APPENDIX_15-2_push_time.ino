// 모멘터리 형식의 RF 수신기가 사용된 것으로 가정한다. 
// 모멘터리 형식 RF 수신기는 푸시 버튼과 유사한 방식으로 동작한다. 
// 리모컨의 버튼이 눌린 상태이면 수신기 모듈의 D3 핀은 HIGH 상태가 되고
// 리모컨의 버튼이 눌리지 않은 상태이면 수신기 모듈의 D3 핀은 LOW 상태가 된다. 

// 수신기 모듈의 "D3" 핀이 연결된 아두이노 입출력 핀 번호
const int TRIGGER_PIN = 11;

// 리모컨 A 버튼이 눌렸을 때 켜지는 LED가 연결된 핀 번호
const int LED_PIN = 13;

// 버튼이 눌리기 시작한 시간 저장을 위한 변수
unsigned long start_time;

// 버튼이 눌리기 시작했을 때 메시지 출력을 위한 변수
boolean announced;

void setup() {
  Serial.begin(9600);
  Serial.println("RF Test");

  pinMode(LED_PIN, OUTPUT);   // LED 연결 핀을 출력으로 설정
}

void loop() {
  digitalWrite(LED_PIN, LOW);     // 버튼이 눌리지 않았을 때 LED 끔
  announced = false;      // 현재 버튼은 눌리지 않은 상태에 있음

  // 버튼이 눌린 동안은 while 루프에 머무름
  while (digitalRead(TRIGGER_PIN)) {
    // 버튼이 눌리기 시작할 때 한 번만 동작
    if (!announced) {
      start_time = millis();
      Serial.print("PRESSED...");
      announced = true;       // 버튼을 누르기 시작할 때 한 번만 메시지 출력
    }
    digitalWrite(LED_PIN, HIGH);
  }

  // 버튼을 눌렀다 뗄 때 버튼을 누른 시간을 출력
  if (announced) {
    Serial.print("RELEASED after ");
    unsigned long duration = millis() - start_time;
    // 소수점 이하 2자리의 초 단위로 버튼을 누른 시간 출력
    Serial.print(duration / 1000.0); 
    Serial.println(" second(s).");
  }
}
