// H-브리지를 사용한 간단한 스테핑 모터 제어
#include <Stepper.h>

// 모터 관련 상수
// 대부분의 NEMA-17 모터는 200 스텝에 1회전한다.
const int STEPS_PER_REV = 200;   // 200 스텝/회전

// H-브리지 드라이버 연결에 사용되는 아두이노 핀
const int COIL1_MC1 = 2;    // 코일 1 스위치 1 제어
const int COIL1_MC2 = 3;    // 코일 1 스위치 2 제어
const int COIL2_MC1 = 4;    // 코일 2 스위치 1 제어
const int COIL2_MC2 = 5;    // 코일 2 스위치 2 제어

// 스위치 제어 핀을 사용하여 스테퍼 라이브러리 초기화
Stepper myStepper(STEPS_PER_REV, COIL1_MC1, COIL1_MC2, COIL2_MC1, COIL2_MC2);

void setup()
{
  // 스테핑 모터 회전 속도 설정
  myStepper.setSpeed(60);     // 60 RPM(분당 회전수)
}

void loop()
{
  myStepper.step(STEPS_PER_REV);  // 한 쪽 방향으로 1회전
  delay(500);

  myStepper.step(-STEPS_PER_REV); // 다른 방향으로 1회전
  delay(500);
}
