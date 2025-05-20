// 라이트 라이더 애니메이션 만들기
const int SER = 8;     // 이동 레지스터 데이터 핀에 연결, 시리얼 데이터 출력
const int LATCH = 9;    // 이동 레지스터 래치 핀에 연결
const int CLK = 10;     // 이동 레지스터 클록 핀에 연결

// 각 단계에서 LED 제어에 사용될 값
int seq[14] = {1, 2, 4, 8, 16, 32, 64, 128, 64, 32, 16, 8, 4, 2};

void setup()
{
  // 이동 레지스터와 연결된 핀을 출력으로 설정
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
}

void loop()
{
  for (int i = 0; i < 14; i++)
  {
    digitalWrite(LATCH, LOW);     // 래치 핀에 LOW 출력, 데이터 전송 시작
    // MSB 우선으로 8비트 데이터를 시리얼로 이동 레지스터에 출력
    shiftOut(SER, CLK, MSBFIRST, seq[i]);
    digitalWrite(LATCH, HIGH);    // 래치 핀에 HIGH 출력, 데이터 전송 종료
    delay(100);         // 애니메이션 속도
  }
}
