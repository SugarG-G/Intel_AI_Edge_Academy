// 마우스를 만들어 보자!
#include <Mouse.h>

const int LEFT_BUTTON = 4;   // 마우스 왼쪽 버튼을 4번 핀에 연결
const int MIDDLE_BUTTON = 3;  // 마우스 가운데 버튼을 3번 핀에 연결
const int RIGHT_BUTTON = 2;   // 마우스 오른쪽 버튼을 2번 핀에 연결

const int X_AXIS = 0;     // 조이스틱 x축 방향 가변저항을 아날로그 0번 핀에 연결
const int Y_AXIS = 1;     // 조이스틱 y축 방향 가변저항을 아날로그 1번 핀에 연결
void setup()
{
  Mouse.begin();
}

void loop()
{
  int xVal = readJoystick(X_AXIS);  // x축 방향 이동량 얻기
  int yVal = readJoystick(Y_AXIS);  // y축 방향 이동량 얻기

  Mouse.move(xVal, yVal, 0);    // 실제 마우스 커서를 이동시킴

  readButton(LEFT_BUTTON, MOUSE_LEFT);  // 마우스 왼쪽 버튼 제어
  readButton(MIDDLE_BUTTON, MOUSE_MIDDLE);  // 마우스 가운데 버튼 제어
  readButton(RIGHT_BUTTON, MOUSE_RIGHT);  // 마우스 오른쪽 버튼 제어

  delay(5);           // 마우스의 반응 속도 제어
}

// 조이스틱(가변저항) 값을 읽고 마우스 커서 이동량으로 변환한 후
// 마우스 커서의 떨림과 흐름 방지를 위한 데드존(dead zone) 추가
int readJoystick(int axis)
{
  int val = analogRead(axis);     // 아날로그 값 읽기
  val = map(val, 0, 1023, -10, 10);   // 아날로그 값을 커서 이동량으로 변환

  if (val <= 2 && val >= -2)    // 데드존 추가
    return 0;
  else              // 변환된 값 반환
    return val;
}

// 버튼 상태를 읽어 마우스의 버튼 명령으로 처리
void readButton(int pin, char mouseCommand)
{
  // 버튼을 눌렀을 때 마우스 버튼을 누른 상태가 아니라면 마우스 버튼을 누름
  if (digitalRead(pin) == HIGH)
  {
    if (!Mouse.isPressed(mouseCommand))
    {
      Mouse.press(mouseCommand);
    }
  }
  // 버튼을 놓았을 때 마우스 버튼을 누른 상태라면 마우스 버튼을 놓음
  else
  {
    if (Mouse.isPressed(mouseCommand))
    {
      Mouse.release(mouseCommand);
    }
  }
}
