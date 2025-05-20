const int LED = 9;      // LED 핀을 9번 핀으로 정의
void setup()
{
  pinMode(LED, OUTPUT);     // LED 핀을 출력으로 설정
}

void loop()
{
  for (int i = 0; i < 256; i++)
  {
    analogWrite(LED, i);
    delay(10);
  }
  for (int i = 255; i >= 0; i--)
  {
    analogWrite(LED, i);
    delay(10);
  }
}
