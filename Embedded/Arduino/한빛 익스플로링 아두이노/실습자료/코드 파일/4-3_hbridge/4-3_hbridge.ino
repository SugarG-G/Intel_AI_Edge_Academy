// H-브리지를 사용한 모터 제어
const int EN = 9;       // H-브리지 1 활성화 핀
const int MC1 = 3;      // 모터 제어 1
const int MC2 = 2;      // 모터 제어 2
const int POT = 0;      // 아날로그 0번 핀에 가변저항 연결

int val = 0;          // 가변저항 값 (0~1023) 저장
int velocity = 0;         // 모터 회전 속도 (0~255) 저장

void setup()
{
  pinMode(EN, OUTPUT);
  pinMode(MC1, OUTPUT);
  pinMode(MC2, OUTPUT);
  brake();          // 모터를 정지한 상태로 초기화
}

void loop()
{
  val = analogRead(POT);

  if (val > 562)        // 정방향 회전
  {
    velocity = map(val, 563, 1023, 0, 255);
    forward(velocity);
  }
  else if (val < 462)     // 역방향 회전
  {
    velocity = map(val, 461, 0, 0, 255);
    reverse(velocity);
  }
  else                // 브레이크
  {
    brake();
  }
}

// 모터를 주어진 속도(0~255)로 정방향으로 회전
void forward (int rate)
{
  digitalWrite(EN, LOW);
  digitalWrite(MC1, HIGH);
  digitalWrite(MC2, LOW);
  analogWrite(EN, rate);
}

// 모터를 주어진 속도(0~255)로 역방향으로 회전
void reverse (int rate)
{
  digitalWrite(EN, LOW);
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, HIGH);
  analogWrite(EN, rate);
}

// 모터 정지
void brake ()
{
  digitalWrite(EN, LOW);
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, LOW);
  digitalWrite(EN, HIGH);
}
