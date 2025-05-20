// 여러 개의 값을 동시에 보냄
// 전송하는 데이터 형식 : <0~100>,<0~100>,< 0~100 > \n
// 각 값은 R, G, B LED의 밝기를 퍼센트로 나타냄

// LED 연결 핀
const int RED = 11;
const int GREEN = 10;
const int BLUE = 9;

void setup()
{
  Serial.begin(9600);       // 9600 보율로 시리얼 포트 통신 속도 설정
  Serial.setTimeout(10);      // 정숫값 수신 대기 시간

  // LED 연결 핀을 출력으로 설정
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  // LED는 끈 상태로 시작
  // 공통 양극 방식을 사용하므로 음극에 HIGH를 출력하여 LED를 끔
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
}

void loop()
{
  // 버퍼에 수신된 데이터가 존재하는 경우 읽음
  if (Serial.available() > 0)
  {
    // 시리얼을 통해 3개의 정숫값을 수신
    // parseInt 함수는 블로킹 함수로 정수가 수신될 때까지 대기함
    // parseInt 함수는 쉼표나 새 줄 문자가 발견된 경우 완전한 정숫값으로 인식함
    // parseInt 함수는 정수가 수신되기 전 숫자가 아닌 문자는 제거하지만
    //               정수가 수신된 이후 숫자가 아닌 문자는 제거하지 않음
    int val1 = Serial.parseInt();
    int val2 = Serial.parseInt();
    int val3 = Serial.parseInt();

    // 정수 3개를 읽은 후 버퍼에 남은 데이터는 삭제함
    while (Serial.available())
    {
      Serial.read();
    }

    // 수신한 값이 0%에서 100% 사이의 값이 되도록 제한
    int val1c = constrain(val1, 0, 100);
    int val2c = constrain(val2, 0, 100);
    int val3c = constrain(val3, 0, 100);

    // 퍼센트로 표시된 밝기를 아날로그 값으로 변환
    int rval = map(val1c, 0, 100, 255, 0);  // 첫 번째 유효한 정수
    int gval = map(val2c, 0, 100, 255, 0);  // 두 번째 유효한 정수
    int bval = map(val3c, 0, 100, 255, 0);  // 세 번째 유효한 정수

    // LED 밝기 설정
    analogWrite(RED, rval);
    analogWrite(GREEN, gval);
    analogWrite(BLUE, bval);

    // LED 제어에 사용된 값 출력
    Serial.println("Red: " + String(val1c) + "%");
    Serial.println("Green: " + String(val2c) + "%");
    Serial.println("Blue: " + String(val3c) + "%\n");
  }
}
