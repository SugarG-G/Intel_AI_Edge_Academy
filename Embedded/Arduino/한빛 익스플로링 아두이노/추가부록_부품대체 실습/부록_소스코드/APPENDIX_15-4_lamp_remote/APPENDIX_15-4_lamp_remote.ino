// 모멘터리 형식의 RF 수신기가 사용된 것으로 가정한다.
// 모멘터리 형식 RF 수신기는 푸시 버튼과 유사한 방식으로 동작한다.
// 리모컨의 버튼이 눌린 상태이면 수신기 모듈의 D3 핀은 HIGH 상태가 되고
// 리모컨의 버튼이 눌리지 않은 상태이면 수신기 모듈의 D3 핀은 LOW 상태가 된다.

#include "pitches.h"       // 음높이를 정의하는 헤더 파일 포함

// 수신기 모듈의 "D3" 핀이 연결된 아두이노 입출력 핀 번호
const int TRIGGER_PIN = 11;

const int SPEAKER = 6;      // 스피커 연결 핀
const int LAMP = 2;       // LED 제어 핀

// 재생할 멜로디의 음 높이 배열
int notes[] = {NOTE_E3, NOTE_A4, NOTE_C5};

// 밀리초 단위의 음길이 배열
int times[] = {250, 250, 250};

// LED의 디폴트 상태는 OFF
bool lamp_on = false;

void setup() {
  pinMode(LAMP, OUTPUT);    // LED 제어 핀을 출력으로 설정
  digitalWrite(LAMP, lamp_on);    // LED는 꺼진 상태로 시작
}

void loop() {
  // 버튼이 눌리면 LED의 상태를 바꿈
  if (digitalRead(TRIGGER_PIN)) {
    lamp_on = !lamp_on;       // LED 제어를 위한 변수 상태 반전
    digitalWrite(LAMP, lamp_on);    // LED을 현재 상태로 설정
    // LED의 상태 변화 방향(ON->OFF 또는 OFF->ON)에 따라 다른 멜로디 재생
    if (lamp_on) {
      // LED가 켜질 때의 멜로디 재생 : 순방향
      for (int i = 0; i < 3; i++) {
        tone(SPEAKER, notes[i], times[i]);
        delay(times[i]);
      }
    }
    else {
      // LED가 꺼질 때의 멜로디 재생 : 역방향
      for (int i = 2; i >= 0; i--) {
        tone(SPEAKER, notes[i], times[i]);
        delay(times[i]);
      }
    }
    // 멜로디 재생이 끝난 후에도 버튼이 눌러진 상태에 있으면 버튼을 뗄 때까지 대기
    // 리모컨 신호에 대한 디바운싱 효과를 얻을 수 있음
    while (digitalRead(TRIGGER_PIN));
  }
}
