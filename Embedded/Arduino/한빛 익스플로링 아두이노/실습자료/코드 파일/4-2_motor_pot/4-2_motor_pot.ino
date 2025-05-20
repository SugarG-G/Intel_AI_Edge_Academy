// 가변저항으로 모터 회전 속도 제어
const int MOTOR = 9;       // 9번 핀에 모터 연결
const int POT = 0;      // 아날로그 0번 핀에 가변저항 연결

int val = 0;

void setup()
{
  pinMode (MOTOR, OUTPUT);
}

void loop()
{
  val = analogRead(POT);
  val = map(val, 0, 1023, 0, 255);
  analogWrite(MOTOR, val);
}
