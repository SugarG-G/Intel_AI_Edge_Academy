// 가속도 센서의 z축 방향 값을 이용하여 방향 감지

// 센서 라이브러리 포함
// 센서 라이브러리 내에서 아두이노의 SPI 라이브러리와 Unified Sensor Library를 포함
#include <Adafruit_LIS3DH.h>

// 사용 핀 정의
// SPI 통신을 위한 핀은 디폴트 핀을 사용하므로 별도 지정하지 않지만
// CS/SS 핀은 슬레이브별로 하나씩 필요하므로 핀을 지정해야 함
const int RED_PIN = 6;
const int GREEN_PIN = 5;
const int CS_PIN = 10;

// 하드웨어 SPI 인터페이스를 사용하여 가속도 센서 초기화
Adafruit_LIS3DH accel = Adafruit_LIS3DH(CS_PIN);

void setup()
{
  Serial.begin(9600);     // 센서 값 출력을 위해 시리얼 포트 초기화

  // 가속도 센서 연결
  if (!accel.begin())
  {
    Serial.println("Could not find accelerometer.");
    while (1);      // 연결 오류가 발생하면 무한 루프로 진입
  }

  // 가속도 센서의 측정 범위를 +/-2G로 설정
  accel.setRange(LIS3DH_RANGE_2_G);

  // LED의 음극에 연결된 핀을 출력으로 설정하고 LED를 끔
  // 공통 양극 방식 LED를 사용하므로 HIGH를 출력해야 LED가 꺼짐
  pinMode(RED_PIN, OUTPUT);
  digitalWrite(RED_PIN, HIGH);
  pinMode(GREEN_PIN, OUTPUT);
  digitalWrite(GREEN_PIN, HIGH);
}

void loop()
{
  // x, y, z축 방향의 가속도 읽기
  accel.read();

  // z축 방향의 원시값 출력
  Serial.print("Raw: ");
  Serial.print(accel.z);

  // z축 방향 원시값을 +/-2G 범위의 가속도 값으로 변환
  Serial.print("\tActual: ");
  Serial.print((float(accel.z) / 32768.0) * 2.0);
  Serial.println("G");

  // 센서가 지면을 향하고 있는 경우
  if (accel.z < 0)
  {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
  }
  else
  {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
  }

  // 100ms 간격으로 가속도 값 확인
  delay(100);
}
