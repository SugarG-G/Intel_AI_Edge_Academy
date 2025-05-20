// 간단한 모터 회전 속도 제어 프로그램
const int MOTOR = 9;       // 9번 핀에 모터 연결

void setup()
{
  pinMode (MOTOR, OUTPUT);
}

void loop()
{
  for (int i = 0; i < 256; i++)   // 회전 속도 증가
  {
    analogWrite(MOTOR, i);
    delay(10);
  }
  delay(2000);
  for (int i = 255; i >= 0; i--)    // 회전 속도 감소
  {
    analogWrite(MOTOR, i);
    delay(10);
  }
  delay(2000);
}
