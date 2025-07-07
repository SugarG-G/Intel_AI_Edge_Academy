// 가변저항 읽기 프로그램
const int POT = 0;     // 아날로그 0번 핀에 가변저항 연결
int val = 0;        // 가변저항 값을 읽어 저장하기 위한 변수

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  val = analogRead(POT);
  Serial.println(val);
  delay(500);
}
