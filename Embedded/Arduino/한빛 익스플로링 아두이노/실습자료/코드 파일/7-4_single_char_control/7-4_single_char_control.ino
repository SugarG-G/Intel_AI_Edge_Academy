// 하나의 문자로 1개 LED를 제어

const int LED = 9;      // 9번 핀에 LED 연결
char data;          // 수신한 문자 저장

void setup()
{
  Serial.begin(9600);       // 9600 보율로 시리얼 포트 통신 속도 설정
  pinMode(LED, OUTPUT);
}

void loop()
{
  // 버퍼에 수신한 데이터가 있을 때만 동작
  if (Serial.available() > 0)
  {
    data = Serial.read();       // 수신한 데이터 1바이트 읽기
    // LED 켜기
    if (data == '1')
    {
      digitalWrite(LED, HIGH);
      Serial.println("LED ON");
    }
    // LED 끄기
    else if (data == '0')
    {
      digitalWrite(LED, LOW);
      Serial.println("LED OFF");
    }
  }
}
