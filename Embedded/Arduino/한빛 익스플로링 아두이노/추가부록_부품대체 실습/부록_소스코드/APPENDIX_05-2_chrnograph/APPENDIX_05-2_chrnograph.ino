#include <Stepper.h>

const int STEPS_PER_REV = 2048;   // 1회전을 위한 스텝 수

// 모터 드라이브에 연결된 핀 IN1, IN3, IN2, IN4 => A, /A, B, /B 순서
Stepper chronograph(STEPS_PER_REV, 8, 10, 9, 11);

// 1분에 1회전하기 위한 스텝 사이의 시간 간격 :
// 60초 * 1000밀리초/초 / 2048스텝
const float MS_PER_STEP = 60000.0 / 2048;

int BTN_START = 7;      // 시작 버튼
int BTN_STOP = 6;       // 정지 버튼

// 시간 및 스텝 수 관리를 위한 변수
unsigned long last_time = 0;
unsigned long curr_time = 0;
int steps_taken = 0;

void setup() {
  chronograph.setSpeed(15);     // 분당 회전수

  pinMode(BTN_START, INPUT_PULLUP);
  pinMode(BTN_STOP, INPUT_PULLUP);
}

void loop() {
  // 무한루프로 시작 버튼을 누를 때까지 대기한다.
  // 마지막의 세미콜론은 주어진 조건을 만족하지 않을 때까지
  // 조건 검사를 계속 시행하도록 한다.
  while (digitalRead(BTN_START) == HIGH);

  last_time = millis(); // 스톱워치 시작 시간 얻기

  // 정지 버튼을 누르거나 1분이 경과할 때까지 반복
  while (digitalRead(BTN_STOP) == HIGH && steps_taken < STEPS_PER_REV) {
    curr_time = millis();
    // 스텝 간격 시간이 경과했을 때 1스텝 회전
    // 한 스텝 간격이 정수가 아닌 실수이므로 전체 스텝 수를 기준으로 계산
    if (curr_time - last_time >= MS_PER_STEP * (steps_taken + 1)) {
      chronograph.step(1);    // 1스텝 회전
      steps_taken++;      // 스텝 수 관리 변숫값 증가
    }
  }

  // 이 단계는 정지 버튼을 누르거나 1분이 경과했을 때 실행된다.
  // 완전히 1회전이 이루어지지 않은 경우 시계바늘을 시작 위치로 옮긴다.
  if (steps_taken < STEPS_PER_REV) chronograph.step(-steps_taken);
  // 스텝 수 관리 변수 초기화
  steps_taken = 0;
}
