const int LED = 9;       // LED는 9번 핀에 연결
const int BUTTON = 2;       // 버튼은 2번 핀에 연결

void setup()
{
  pinMode (LED, OUTPUT);    // LED 핀을 출력으로 설정
  pinMode (BUTTON, INPUT);    // 버튼 핀을 입력으로 설정 (생략 가능)
}
void loop()
{
  if (digitalRead(BUTTON) == LOW)
  {
    digitalWrite(LED, LOW);
  }
  else
  {
    digitalWrite(LED, HIGH);
  }
}
