int PINS[] = {8, 9, 10, 11, 12};    // 수신기 연결 핀
// 수신기 핀의 출력 상태
boolean states[] = {false, false, false, false};
boolean state_change = false;   // 수신기 핀의 출력 변화 여부

void setup() {
  for (int i = 0; i < 5; i++) {   // 수신기 핀이 연결된 핀을 입력으로 설정
    pinMode(PINS[i], INPUT);
  }

  Serial.begin(9600);     // 시리얼 연결 초기화
}

void loop() {
  state_change = false;

  for (int i = 0; i < 4; i++) {
    boolean current_state = digitalRead(PINS[i]); // 수신기 핀의 출력을 검사

    // 이전 상태와 다른 경우, 즉, 리모컨 버튼이 눌러진 경우
    if (current_state != states[i]) { 
      state_change = true;    // 상태 변화 플래그 설정
      states[i] = current_state;    // 현재 상태 설정
    }
  }

  // 4개 리모컨 버튼 중 하나라도 상태가 변한 경우에만 시리얼 모니터로 상태 출력
  if (state_change) {
    for (int i = 0; i < 4; i++) {
      Serial.print(states[i] ? 'O' : '.' );
      Serial.print('\t');
    }
    Serial.println();
  }
}
