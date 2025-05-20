// 가속도 센서를 사용하여 빛과 소리 제어

// 센서 라이브러리 포함
// 센서 라이브러리 내에서 아두이노의 SPI 라이브러리와 Unified Sensor Library를 포함
#include <Adafruit_LIS3DH.h>

// 사용 핀 정의
// SPI 통신을 위한 핀은 디폴트 핀을 사용하므로 별도 지정하지 않지만
// CS/SS 핀은 슬레이브별로 하나씩 필요하므로 핀을 지정해야 함
const int RED_PIN = 6;
const int GREEN_PIN = 5;
const int BLUE_PIN = 3;
const int SPEAKER = 9;
const int CS_PIN = 10;

// 5음 음계 C(도) D(레) E(미) G(솔) A(라)
#define NOTE_C 262     // Hz
#define NOTE_D 294    // Hz
#define NOTE_E 330    // Hz
#define NOTE_G 392    // Hz
#define NOTE_A 440    // Hz
#define NOTE_C2 523     // Hz

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
  pinMode(BLUE_PIN, OUTPUT);
  digitalWrite(BLUE_PIN, HIGH);
}

void loop()
{
  // x, y, z축 방향의 가속도 읽기
  accel.read();

  // 지표면에 수직인 가속도 센서 축 보상
  // 1G에 해당하는 원시값을 뺌
  long norm_z = accel.z - 16384;

  // 임계치 조절을 위해 모든 가속도 값을 시리얼 모니터로 출력
  Serial.print(accel.x);
  Serial.print(" ");
  Serial.print(accel.y);
  Serial.print(" ");
  Serial.println(norm_z);

  // 가속도 센서 칩의 움직임에 따라 100ms 길이로 다른 높이의 음 재생
  if (accel.x < -5000) tone(SPEAKER, NOTE_C, 100);
  if (accel.x > 5000) tone(SPEAKER, NOTE_D, 100);
  if (accel.y < -5000) tone(SPEAKER, NOTE_E, 100);
  if (accel.y > 5000) tone(SPEAKER, NOTE_G, 100);
  if (norm_z < -5000) tone(SPEAKER, NOTE_A, 100);
  if (norm_z > 5000) tone(SPEAKER, NOTE_C2, 100);

  // 가속도 센서 칩의 움직임에 비례하여 LED 밝기 조절
  analogWrite(RED_PIN, constrain(map(abs(accel.x), 5000, 20000, 255, 0), 0, 255));
  analogWrite(GREEN_PIN, constrain(map(abs(accel.y), 5000, 20000, 255, 0), 0, 255));
  analogWrite(BLUE_PIN, constrain(map(abs(norm_z), 5000, 20000, 255, 0), 0, 255));
}
