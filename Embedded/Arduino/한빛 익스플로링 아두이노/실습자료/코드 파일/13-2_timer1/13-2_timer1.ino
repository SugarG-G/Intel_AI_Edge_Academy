// 아두이노 우노의 타이머 인터럽트 사용
#include <TimerOne.h>
const int LED = 13;

void setup()
{
  pinMode(LED, OUTPUT);
  Timer1.initialize(1000000);   // 1000000마이크로초마다 인터럽트 발생
  Timer1.attachInterrupt(blinky); // 타이머 인터럽트 발생 시 “blinky” 함수 호출
}

void loop()
{
  // LED를 깜빡이게 하는 것 이외의 코드를 추가할 수 있다!
}

// 타이머 인터럽트 처리 함수
void blinky()
{
  digitalWrite(LED, !digitalRead(LED));   // LED 상태 반전
}
