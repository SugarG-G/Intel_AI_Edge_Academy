// 물체까지의 거리를 막대그래프로 나타내기
const int SER = 8;     // 이동 레지스터 데이터 핀에 연결, 시리얼 데이터 출력
const int LATCH = 9;    // 이동 레지스터 래치 핀에 연결
const int CLK = 10;     // 이동 레지스터 클록 핀에 연결
const int DIST = 0;     // 적외선 거리 센서를 0번 핀에 연결

// 막대그래프 표현을 위한 LED 제어값
int vals[9] = {0, 1, 3, 7, 15, 31, 63, 127, 255};

// 거리 센서가 반환하는 최댓값
int maxVal = 500;

// 거리 센서가 반환하는 최솟값
int minVal = 0;

void setup()
{
  // 이동 레지스터와 연결된 핀을 출력으로 설정
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
}

void loop()
{
  int distance = analogRead(DIST);
  distance = map(distance, minVal, maxVal, 0, 8);
  distance = constrain(distance, 0, 8);

  digitalWrite(LATCH, LOW);     // 래치 핀에 LOW 출력, 데이터 전송 시작
  // MSB 우선으로 8비트 데이터를 시리얼로 이동 레지스터에 출력
  shiftOut(SER, CLK, MSBFIRST, vals[distance]);
  digitalWrite(LATCH, HIGH);    // 래치 핀에 HIGH 출력, 데이터 전송 종료
  delay(10);          // 애니메이션 속도
}
