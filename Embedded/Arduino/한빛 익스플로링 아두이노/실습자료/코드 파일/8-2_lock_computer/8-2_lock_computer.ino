// 전등을 끄면 컴퓨터가 잠김
#include <Keyboard.h>

const int LIGHT = 1;     // 조도 센서를 아날로그 1번 핀에 연결
const int THRESHOLD = 500;  // 컴퓨터를 잠그기 위한 최대 조도
                            // 임계치 이하일 때 컴퓨터가 자동으로 잠김

void setup()
{
  Keyboard.begin();
}

void loop()
{
  int brightness = analogRead(LIGHT);   // 조도 센서 읽기

  if (brightness < THRESHOLD)
  {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('l');
    delay(100);
    Keyboard.releaseAll();
  }
}
