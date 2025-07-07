// 자동 조명등
const int WLED = 9;     // 백색 LED 양극을 9번 핀에 연결 (PWM 출력 핀)
const int LIGHT = 0;    // 조도 센서를 A0 핀에 연결
const int MIN_LIGHT = 200;  // 최소 조도 값
const int MAX_LIGHT = 900;  // 최대 조도 값
int val = 0;        // 아날로그 입력값을 저장하는 변수

void setup()
{
  pinMode(WLED, OUTPUT);  // 백색 LED 연결 핀을 출력으로 설정
}

void loop()
{
  val = analogRead(LIGHT);      // 조도 센서 읽기
  val = map(val, MIN_LIGHT, MAX_LIGHT, 255, 0); // 조도 -> 밝기 선형 사상
  val = constrain(val, 0, 255);       // 밝기 범위 제한
  analogWrite(WLED, val);       // LED 밝기 제어
}
