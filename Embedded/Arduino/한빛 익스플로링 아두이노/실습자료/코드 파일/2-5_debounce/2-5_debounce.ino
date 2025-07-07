const int LED = 9;       // LED는 9번 핀에 연결
const int BUTTON = 2;       // 버튼은 2번 핀에 연결
boolean lastButton = LOW;     // 버튼의 이전 상태 저장
boolean currentButton = LOW;    // 버튼의 현재 상태 저장
boolean ledOn = false;      // LED의 현재 상태 (on/off)

void setup()
{
  pinMode (LED, OUTPUT);    // LED 핀을 출력으로 설정
  pinMode (BUTTON, INPUT);    // 버튼 핀을 입력으로 설정 (생략 가능)
}

/*
  디바운싱 함수
  버튼의 이전 상태를 매개변수로 전달하면
  디바운싱된 버튼의 현재 상태를 얻을 수 있다.
*/
boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON);  // 버튼 상태 읽기
  if (last != current)      // 이전 상태와 현재 상태가 다르면...
  {
    delay(5);         // 5ms 대기
    current = digitalRead(BUTTON);  // 버튼 상태 다시 읽기
  }
  return current;       // 버튼의 현재 상태 반환
}

void loop()
{
  currentButton = debounce(lastButton);   // 디바운싱된 버튼 상태 읽기
  if (lastButton == LOW && currentButton == HIGH)  // 버튼을 누르면...
  {
    ledOn = !ledOn;       // LED 상태 값 반전
  }
  lastButton = currentButton;     // 이전 버튼 상태를 현재 버튼 상태로 설정
  digitalWrite(LED, ledOn);     // LED 상태 변경
}
