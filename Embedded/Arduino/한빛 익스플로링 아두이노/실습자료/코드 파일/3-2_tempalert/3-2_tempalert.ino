// 온도 경보!
const int BLED = 9;       // 파란색 LED 음극을 9번 핀에 연결
const int GLED = 10;      // 초록색 LED 음극을 10번 핀에 연결
const int RLED = 11;      // 빨간색 LED 음극을 11번 핀에 연결
const int TEMP = 0;       // 온도 센서를 A0 핀에 연결

const int LOWER_BOUND = 139;    // 온도 하한값
const int UPPER_BOUND = 147;    // 온도 상한값

int val = 0;          // 아날로그 입력 값을 저장하는 변수

void setup()
{
  pinMode (BLED, OUTPUT);     // 파란색 LED 핀을 출력으로 설정
  pinMode (GLED, OUTPUT);     // 초록색 LED 핀을 출력으로 설정
  pinMode (RLED, OUTPUT);     // 빨간색 LED 핀을 출력으로 설정
}

void loop()
{
  val = analogRead(TEMP);
  if (val < LOWER_BOUND)    // LED를 파란색으로 켬
  {
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, LOW);
  }
  else if (val > UPPER_BOUND)   // LED를 빨간색으로 켬
  {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, HIGH);
  }
  else                // LED를 초록색으로 켬
  {
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, HIGH);
  }
}
