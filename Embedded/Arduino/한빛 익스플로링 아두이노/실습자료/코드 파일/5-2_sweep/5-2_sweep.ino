// 회전 거리 센서
#include <Servo.h>

const int SERVO = 9;     // 서보 모터를 9번 핀에 연결
const int IR = 0;     // 적외선 거리 센서를 아날로그 0번 핀에 연결
const int LED1 = 3;     // LED 1 연결 핀
const int LED2 = 5;     // LED 2 연결 핀
const int LED3 = 6;     // LED 3 연결 핀
const int LED4 = 11;    // LED 4 연결 핀

Servo myServo;      // 서보 모터 제어 객체
int dist1 = 0;      // 1번 영역에서 물체까지의 거리
int dist2 = 0;      // 2번 영역에서 물체까지의 거리
int dist3 = 0;      // 3번 영역에서 물체까지의 거리
int dist4 = 0;      // 4번 영역에서 물체까지의 거리

void setup()
{
  myServo.attach(SERVO);  // 서보 모터를 서보 모터 제어 객체에 연결
  pinMode(LED1, OUTPUT);  // LED 1 연결 핀을 출력으로 설정
  pinMode(LED2, OUTPUT);  // LED 2 연결 핀을 출력으로 설정
  pinMode(LED3, OUTPUT);  // LED 3 연결 핀을 출력으로 설정
  pinMode(LED4, OUTPUT);  // LED 4 연결 핀을 출력으로 설정
}

void loop()
{
  // 서보 모터를 4개의 영역으로 회전하고 거리를 측정하여 LED 상태를 바꿈
  dist1 = readDistance(15);   // 15도로 회전하여 거리 측정
  analogWrite(LED1, dist1);   // LED 1 밝기 조절
  delay(300);       // 다음 영역 측정 시점까지의 지연 시간
  dist2 = readDistance(65);   // 65도로 회전하여 거리 측정
  analogWrite(LED2, dist2);   // LED 2 밝기 조절
  delay(300);       // 다음 영역 측정 시점까지의 지연 시간
  dist3 = readDistance(115);  // 115도로 회전하여 거리 측정
  analogWrite(LED3, dist3);   // LED 3 밝기 조절
  delay(300);       // 다음 영역 측정 시점까지의 지연 시간
  dist4 = readDistance(165);  // 165도로 회전하여 거리 측정
  analogWrite(LED4, dist4);   // LED 4 밝기 조절
  delay(300);       // 다음 영역 측정 시점까지의 지연 시간
}

int readDistance(int pos)
{
  myServo.write(pos);       // 지정한 각도로 회전
  delay(600);         // 서보 모터의 회전 완료 대기
  int dist = analogRead(IR);    // 적외선 거리 센서 읽기
  dist = map(dist, 50, 500, 0, 255);  // 거리 센서 값을 LED 밝기로 매핑
  dist = constrain(dist, 0, 255);     // LED 밝기의 범위 제한
  return dist;        // 변환된 거리(즉, LED 밝기) 반환
}
