// 수신한 모든 문자를 되돌려 줌
char data;           // 수신한 문자 저장

void setup()
{
  Serial.begin(9600);       // 9600 보율로 시리얼 포트 통신 속도 설정
}

void loop()
{
  // 수신한 데이터가 있는 경우에만 되돌려 줌
  if (Serial.available() > 0)
  {
    data = Serial.read();       // 수신한 데이터 1바이트 읽기
    Serial.print(data);       // 읽은 데이터를 컴퓨터로 되돌려 주기
  }
}
