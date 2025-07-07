// 가변저항으로 서보 모터 제어
#include <Servo.h>

const int SERVO = 9;       // 서보 모터를 9번 핀에 연결
const int POT = 0;      // 가변저항을 아날로그 0번 핀에 연결

Servo myServo;
int val = 0;          // 가변저항 값 저장

void setup()
{
  // 서보 객체에 서보 모터 제어핀 연결
  myServo.attach(SERVO);
}

void loop()
{
  val = analogRead(POT);    // 가변저항 읽기
  val = map(val, 0, 1023, 0, 179);  // 가변저항 값을 각도로 변환
  myServo.write(val);       // 서보 모터의 회전 각도 설정
  delay(15);          // 서보 모터의 회전 대기
}
