const int BLED = 9;       // 파란색 LED 음극을 9번 핀에 연결
const int GLED = 10;      // 초록색 LED 음극을 10번 핀에 연결
const int RLED = 11;      // 빨간색 LED 음극을 11번 핀에 연결
const int BUTTON = 2;       // 버튼을 2번 핀에 연결

boolean lastButton = LOW;     // 버튼의 이전 상태
boolean currentButton = LOW;    // 버튼의 현재 상태
int ledMode = 0;      // LED 상태, 0~7의 값을 순환

void setup()
{
  pinMode (BLED, OUTPUT);     // 파란색 LED 핀을 출력으로 설정
  pinMode (GLED, OUTPUT);     // 초록색 LED 핀을 출력으로 설정
  pinMode (RLED, OUTPUT);     // 빨간색 LED 핀을 출력으로 설정
  pinMode (BUTTON, INPUT);    // 버튼 핀을 입력으로 설정(생략 가능)
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

/*
  LED 상태 선택
  LED 상태 번호를 매개변수로 전달하고 그에 따라 LED 상태를 변경한다.
  사용된 RGB LED는 공통 양극 방식이므로 해당 색상의 LED를 켜기 위해서는
  해당 LED의 음극이 연결된 핀을 LOW로 설정해야 한다.
*/
void setMode(int mode)
{
  if (mode == 1)        // 빨간색
  {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, HIGH);
  }
  else if (mode == 2)     // 초록색
  {
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, HIGH);
  }
  else if (mode == 3)     // 파란색
  {
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, LOW);
  }
  else if (mode == 4)     // 보라색 (빨간색 + 파란색)
  {
    analogWrite(RLED, 127);
    analogWrite(GLED, 255);
    analogWrite(BLED, 127);
  }
  else if (mode == 5)     // 청록색 (파란색 + 초록색)
  {
    analogWrite(RLED, 255);
    analogWrite(GLED, 127);
    analogWrite(BLED, 127);
  }
  else if (mode == 6)     // 주황색 (초록색 + 빨간색)
  {
    analogWrite(RLED, 127);
    analogWrite(GLED, 127);
    analogWrite(BLED, 255);
  }
  else if (mode == 7)     // 흰색 (초록색 + 빨간색 + 파란색)
  {
    analogWrite(RLED, 170);
    analogWrite(GLED, 170);
    analogWrite(BLED, 170);
  }
  else                // LED 끄기 (mode == 0)
  {

    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, HIGH);
  }
}

void loop()
{
  currentButton = debounce(lastButton); // 디바운싱된 버튼 상태 읽기
  if (lastButton == LOW & & currentButton == HIGH)  // 버튼이 눌러졌으면...
  {
    ledMode++;        // LED 상태 증가
  }
  lastButton = currentButton;     // 이전 버튼 상태를 현재 버튼 상태로 설정
  // LED 상태를 모두 나타낸 후에는
  // LED 상태 카운터를 0으로 설정
  if (ledMode == 8) ledMode = 0;
  setMode(ledMode);       // LED 상태 변경
}
