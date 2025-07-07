// 모멘터리 형식의 RF 수신기가 사용된 것으로 가정한다.
// 모멘터리 형식 RF 수신기는 푸시 버튼과 유사한 방식으로 동작한다.
// 리모컨의 버튼이 눌린 상태이면 수신기 모듈의 D3 핀은 HIGH 상태가 되고
// 리모컨의 버튼이 눌리지 않은 상태이면 수신기 모듈의 D3 핀은 LOW 상태가 된다.

#include "pitches.h"       // 음높이를 정의하는 헤더 파일 포함

// 수신기 모듈의 "D3" 핀이 연결된 아두이노 입출력 핀 번호
const int TRIGGER_PIN = 11;

const int SPEAKER = 6;      // 스피커 연결 핀

// 재생할 멜로디의 음 높이 배열
int notes[] = {
  NOTE_A4, NOTE_E3, NOTE_A4, 0,
  NOTE_A4, NOTE_E3, NOTE_A4, 0,
  NOTE_E4, NOTE_D4, NOTE_C4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C4, NOTE_D4,
  NOTE_E4, NOTE_E3, NOTE_A4, 0
};

// 밀리초 단위의 음길이 배열
int times[] = {
  250, 250, 250, 250,
  250, 250, 250, 250,
  125, 125, 125, 125, 125, 125, 125, 125,
  250, 250, 250, 250
};

void setup() {
  // 초기화는 필요하지 않다.
}

void loop() {
  // 버튼이 눌려 아두이노 핀으로 HIGH가 입력되면 멜로디를 한 번 재생한다.
  if (digitalRead(TRIGGER_PIN)) {
    for (int i = 0; i < 20; i++) {
      tone(SPEAKER, notes[i], times[i]);
      delay(times[i]);
    }
    // 멜로디 재생이 끝난 후에도 버튼이 눌린 상태에 있으면
    // 버튼을 뗄 때까지 기다려 멜로디가 연속해서 재생되지 않도록 한다.
    while (digitalRead(TRIGGER_PIN));
  }
}
