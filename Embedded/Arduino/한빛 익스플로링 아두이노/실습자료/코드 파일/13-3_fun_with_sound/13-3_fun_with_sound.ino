// 하드웨어 인터럽트와 타이머 인터럽트를 사용하여 음 재생

// TimerOne 라이브러리 포함
#include <TimerOne.h>

const int BTN = 2;     // 디바운싱된 버튼 입력을 2번 핀에 연결
const int SPEAKER = 12;   // 스피커를 12번 핀에 연결

// 재생할 음의 기본 주파수 정의
#define NOTE_C 65
#define NOTE_D 73
#define NOTE_E 82
#define NOTE_F 87
#define NOTE_G 98
#define NOTE_A 110
#define NOTE_B 123

// 휘발성 변수는 인터럽트 처리 함수 내에서 값 변경 가능
volatile int key = NOTE_C;
volatile int octave_multiplier = 1;

void setup()
{
  Serial.begin(9600);     // 시리얼 통신 초기화
  pinMode (SPEAKER, OUTPUT);    // 스피커 연결 핀을 출력으로 설정

  //슈미터 트리거 입력은 반전되어 있으므로 상승 에지에서 인터럽트 발생
  attachInterrupt(digitalPinToInterrupt(BTN), changeKey, RISING);

  // 타이머 인터럽트 설정
  Timer1.initialize(500000);    // 0.5초 간격으로 인터럽트 발생
  Timer1.attachInterrupt(changePitch);  // 타이머 인터럽트 발생 시 “changePitch” 함수 호출
}

void changeKey()
{
  octave_multiplier = 1;
  if (key == NOTE_C)
    key = NOTE_D;
  else if (key == NOTE_D)
    key = NOTE_E;
  else if (key == NOTE_E)
    key = NOTE_F;
  else if (key == NOTE_F)
    key = NOTE_G;
  else if (key == NOTE_G)
    key = NOTE_A;
  else if (key == NOTE_A)
    key = NOTE_B;
  else if (key == NOTE_B)
    key = NOTE_C;
}

// 타이머 인터럽트 처리 함수
void changePitch()
{
  octave_multiplier = octave_multiplier * 2;
  if (octave_multiplier > 16) octave_multiplier = 1;
  tone(SPEAKER, key * octave_multiplier);
}

void loop()
{
  Serial.print("Key: ");
  Serial.print(key);
  Serial.print(" Multiplier: ");
  Serial.print(octave_multiplier);
  Serial.print(" Frequency: ");
  Serial.println(key * octave_multiplier);
  delay(100);
}
