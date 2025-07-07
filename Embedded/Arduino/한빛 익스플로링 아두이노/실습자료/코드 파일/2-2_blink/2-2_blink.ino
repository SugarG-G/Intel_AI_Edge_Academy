const int LED = 9;      // LED 핀을 9번 핀으로 정의
void setup()
{
  pinMode(LED, OUTPUT);     // LED 핀을 출력으로 설정
}

void loop()
{
  for (int i = 100; i <= 1000; i = i + 100)
  {
    digitalWrite(LED, HIGH);
    delay(i);
    digitalWrite(LED, LOW);
    delay(i);
  }
}
