// 스피커를 통한 노래 재생
#include "pitches.h"       // 음높이가 정의된 헤더 파일
const int SPEAKER = 9;      // 스피커 연결 핀

// 음높이 배열
int notes[] = {
  NOTE_A4, NOTE_E3, NOTE_A4, 0,
  NOTE_A4, NOTE_E3, NOTE_A4, 0,
  NOTE_E4, NOTE_D4, NOTE_C4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C4, NOTE_D4,
  NOTE_E4, NOTE_E3, NOTE_A4, 0
};

// (밀리초 단위) 음길이 배열
int times[] = {
  250, 250, 250, 250,
  250, 250, 250, 250,
  125, 125, 125, 125, 125, 125, 125, 125,
  250, 250, 250, 250
};

void setup()
{
  // 각 음을 지정한 높이와 지정한 시간 동안 재생
  for (int i = 0; i < 20; i++)
  {
    tone(SPEAKER, notes[i], times[i]);
    delay(times[i]);
  }
}

void loop()
{
  // 리셋 버튼을 눌러 다시 재생
}
