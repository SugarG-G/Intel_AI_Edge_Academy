// 이동 레지스터를 사용하여 번갈아 켜지는 LED 패턴 표시
const int SER = 8;     // 이동 레지스터 데이터 핀에 연결, 시리얼 데이터 출력
const int LATCH = 9;    // 이동 레지스터 래치 핀에 연결
const int CLK = 10;     // 이동 레지스터 클록 핀에 연결

void setup()
{
  // 이동 레지스터와 연결된 핀을 출력으로 설정
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);

  digitalWrite(LATCH, LOW);   // 래치 핀에 LOW 출력, 이동 레지스터 값 출력 금지
  // MSB 우선으로 8비트 데이터를 시리얼로 이동 레지스터에 출력
  shiftOut(SER, CLK, MSBFIRST, B10101010);
  digitalWrite(LATCH, HIGH);  // 래치 핀에 HIGH 출력 – LED에 표시
}

void loop()
{
  // 반복 작업은 필요하지 않음
}
