// 시작/정지/초기화 기능을 가진 1분 스톱워치
#include <Stepper.h>

// 대부분의 NEMA-17 모터는 200 스텝에 1회전한다.
const int STEPS_PER_REV = 200;   // 200 스텝/회전

// 1분에 1회전하기 위한 스텝 사이의 시간 간격 :
// 60초 * 1000밀리초/초 / 200스텝 = 300 밀리초/스텝
const int MS_PER_STEP = 300;

// H-브리지 드라이버 연결에 사용되는 아두이노 핀
const int COIL1_MC1 = 2;    // 코일 1 스위치 1 제어
const int COIL1_MC2 = 3;    // 코일 1 스위치 2 제어
const int COIL2_MC1 = 4;    // 코일 2 스위치 1 제어
const int COIL2_MC2 = 5;    // 코일 2 스위치 2 제어

// 버튼 연결 핀
const int START = 8;      // 시작 버튼
const int STOP = 9;       // 정지 버튼

// 시간 및 스텝 수 관리를 위한 변수
unsigned long last_time = 0;
unsigned long curr_time = 0;
int steps_taken = 0;

// 스위치 제어 핀을 사용하여 스테퍼 라이브러리 초기화
Stepper chronograph(STEPS_PER_REV, COIL1_MC1, COIL1_MC2, COIL2_MC1, COIL2_MC2);

void setup()
{
  // 각 스텝의 회전이 가능한 한 빨리 이루어지도록 기본 회전 속도 설정
  chronograph.setSpeed(200);    // 기본 회전 속도, 200 RPM
  // 버튼의 풀업 저항 설정
  pinMode(START, INPUT_PULLUP);
  pinMode(STOP, INPUT_PULLUP);
}

void loop()
{
  // 무한루프로 시작 버튼을 누를 때까지 대기한다.
  // 마지막의 세미콜론은 주어진 조건을 만족하지 않을 때까지
  // 조건 검사를 계속 시행하도록 한다.
  while (digitalRead(START) == HIGH);

  last_time = millis();       // 스톱워치 시작 시간 얻기

  // 정지 버튼을 누르거나 1분이 경과할 때까지 반복
  while (digitalRead(STOP) == HIGH && steps_taken < STEPS_PER_REV)
  {
    curr_time = millis();

    // 스텝 간격 시간이 경과했을 때 1스텝 회전
    if (curr_time - last_time >= MS_PER_STEP)
    {
      chronograph.step(1);    // 1스텝 회전
      steps_taken++;      // 스텝 수 관리 변숫값 증가
      last_time = curr_time;    // 마지막 1회전 진행 시간을 현재 시간으로 설정
    }
  }

  // 이 단계는 정지 버튼을 누르거나 1분이 경과했을 때 실행된다.
  // 완전히 1회전이 이루어지지 않은 경우 시계바늘을 시작 위치로 옮긴다.
  if (steps_taken < STEPS_PER_REV) chronograph.step(-steps_taken);
  // 스텝 수 관리 변수 초기화
  steps_taken = 0;
}
