// 이동 레지스터와 시리얼 통신을 사용하여
// I2C 온도 센서에서 읽은 온도를 LED 막대그래프와 프로세싱으로 나타냄

// Wire 라이브러리 포함
#include <Wire.h>

const int SER = 8;     // 이동 레지스터 데이터 핀에 연결, 시리얼 데이터 출력
const int LATCH = 9;    // 이동 레지스터 래치 핀에 연결
const int CLK = 10;     // 이동 레지스터 클록 핀에 연결

int temp_address = 72;    // 온도 센서의 주소

// 가능한 LED 설정값
int vals[8] = {1, 3, 7, 15, 31, 63, 127, 255};

void setup()
{
  // 9600 보율로 시리얼 통신 시작
  Serial.begin(9600);
  // Wire 클래스의 객체 생성 및 초기화
  Wire.begin();

  // 이동 레지스터와 연결된 핀을 출력으로 설정
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
}

void loop()
{
  // 데이터 전송 시작
  // 특정 주소의 슬레이브 장치로 주소를 전송함으로써 시작
  Wire.beginTransmission(temp_address);
  // 0번 데이터 레지스터의 온도 정보를 요청함을 나타내는 0의 값 전송
  Wire.write(0);
  // 전송 종료
  Wire.endTransmission();

  // 슬레이브 장치에서 온도 읽기
  // 특정 주소의 슬레이브 장치에 1바이트 정보 요청
  int returned_bytes = Wire.requestFrom(temp_address, 1);

  // 슬레이브 장치에서 데이터를 수신하지 못한 경우, 오류 발생
  if (returned_bytes == 0)
  {
    Serial.print("Err,Err.");     // 오류 발생 출력
    while (1);        // 프로그램 정지
  }

  // 온도 정보를 읽어 변수에 저장
  int c = Wire.read();

  // 온도를 LED 설정으로 변환
  int graph = map(c, 24, 31, 0, 7);
  graph = constrain(graph, 0, 7);

  digitalWrite(LATCH, LOW);     // 래치 핀에 LOW 출력, 데이터 전송 시작
  // MSB 우선으로 8비트 데이터를 시리얼로 이동 레지스터에 출력
  shiftOut(SER, CLK, MSBFIRST, vals[graph]);
  digitalWrite(LATCH, HIGH);    // 래치 핀에 HIGH 출력, 데이터 전송 종료

  // 섭씨를 화씨로 변환
  int f = round(c * 9.0 / 5.0 + 32.0);

  Serial.print(c);
  Serial.print("C,");
  Serial.print(f);
  Serial.print("F.");

  delay(500);
}
