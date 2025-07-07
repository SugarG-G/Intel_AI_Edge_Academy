// 가변저항 값을 컴퓨터로 전송

const int POT = 0;     // 가변저항을 아날로그 0번 핀에 연결
int val;            // 변환된 가변저항 값 저장을 위한 변수
void setup()
{
  Serial.begin(9600);     // 시리얼 통신 시작
}

void loop()
{
  // 가변저항 값을 읽어 1바이트 값으로 변환
  val = map(analogRead(POT), 0, 1023, 0, 255);
  Serial.println(val);    // 컴퓨터로 변환한 값 전송
  delay(50);        // 컴퓨터의 버퍼 넘침을 방지하기 위한 지연 시간
}
