// 하드웨어 디바운싱을 사용한 버튼으로 인터럽트 사용하기

// 버튼 연결 핀
const int BTN = 2;     // 디바운싱 된 버튼 입력을 2번 핀에 연결
const int RED = 11;     // 빨간색 LED 음극을 11번 핀에 연결
const int GREEN = 10;     // 초록색 LED 음극을 10번 핀에 연결
const int BLUE = 9;     // 파란색 LED 음극을 9번 핀에 연결

// 휘발성 변수는 인터럽트 처리 함수 내에서 값 변경이 가능
volatile int selectedLED = RED;

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  // RGB LED를 끈 상태에서 시작
  // 공통 양극 방식이므로 HIGH를 출력해야 LED가 꺼짐
  digitalWrite(RED, HIGH);
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, HIGH);

  // 슈미트 트리거 입력은 반전되어 있으므로 상승 에지에서 인터럽트 발생
  attachInterrupt(digitalPinToInterrupt(BTN), swap, RISING);
}

void swap()
{
  // 현재 선택된 LED를 끔 (공통 양극 방식이므로 HIGH 출력으로 LED 끔)
  digitalWrite(selectedLED, HIGH);
  // 새로운 LED 선택
  if (selectedLED == GREEN)
    selectedLED = RED;
  else if (selectedLED == RED)
    selectedLED = BLUE;
  else if (selectedLED == BLUE)
    selectedLED = GREEN;
}

void loop()
{
  // LED 밝기를 서서히 증가
  // 공통 양극 방식이므로 음극에 작은 값을 출력해야 밝아지는 반전된 값을 사용
  for (int i = 255; i >= 0; i--)
  {
    analogWrite(selectedLED, i);
    delay(10);
  }
  // LED 밝기를 서서히 감소
  // 공통 양극 방식이므로 음극에 큰 값을 출력해야 어두워지는 반전된 값을 사용
  for (int i = 0; i <= 255; i++)
  {
    analogWrite(selectedLED, i);
    delay(10);
  }
  delay(1000);
}
