// 빛을 따라 움직이는 자동 주행 자동차

// H-브리지 제어 핀
const int RIGHT_EN = 9;     // 오른쪽 모터 활성화 제어
const int RIGHT_MC1 = 2;    // 오른쪽 모터를 위한 스위치 1 제어
const int RIGHT_MC2 = 3;    // 오른쪽 모터를 위한 스위치 2 제어
const int LEFT_EN = 10;     // 왼쪽 모터 활성화 제어
const int LEFT_MC1 = 4;     // 왼쪽 모터를 위한 스위치 1 제어
const int LEFT_MC2 = 5;     // 왼쪽 모터를 위한 스위치 2 제어

// 포토 레지스터(조도센서) 연결 핀
const int LEFT_LIGHT_SENSOR = 0;  // 아날로그 0번 핀의 포토레지스터
const int RIGHT_LIGHT_SENSOR = 1;   // 아날로그 1번 핀의 포토레지스터
// 이동 및 속도 제어를 위한 임계값

const int LIGHT_THRESHOLD_MIN = 810;  // 이동 시작을 위한 포토레지스터 최솟값
const int LIGHT_THRESHOLD_MAX = 1100; // 이동 시작을 위한 포토레지스터 최댓값
const int SPEED_MIN = 150;    // 최소 모터 회전 속도
const int SPEED_MAX = 255;    // 최대 모터 회전 속도

void setup()
{
  // H-브리지 제어 핀을 출력으로 설정
  pinMode(RIGHT_EN, OUTPUT);
  pinMode(RIGHT_MC1, OUTPUT);
  pinMode(RIGHT_MC2, OUTPUT);
  pinMode(LEFT_EN, OUTPUT);
  pinMode(LEFT_MC1, OUTPUT);
  pinMode(LEFT_MC2, OUTPUT);

  // 양 쪽 모터를 정지한 상태로 초기화
  brake("left");
  brake("right");

  // 움직임 제어에 필요한 임계치 조정을 위한 시리얼 인터페이스
  Serial.begin(9600);
}

void loop()
{
  // 포토레지스터(조도 센서) 읽기
  int left_light = analogRead(LEFT_LIGHT_SENSOR);
  int right_light = analogRead(RIGHT_LIGHT_SENSOR);

  // 시리얼 모니터 출력의 스크롤을 늦추기 위한 짧은 지연 시간(50ms)
  delay(50);

  // 각 조도센서의 값에 비례하여 반대쪽 모터 속도 조절
  // 조도센서 값이 임계치 이하이면 반대쪽 모터는 정지
  // Note:  왼쪽 센서는 오른쪽 모터의 속도를, 오른쪽 센서는 왼쪽 모터의 속도를 조절
  //        왼쪽으로 회전하기 위해서는 오른쪽 모터의 회전 속도를 증가
  Serial.print("Right: ");
  Serial.print(right_light);
  Serial.print(" ");
  if (right_light >= LIGHT_THRESHOLD_MIN) // 오른쪽 포토레지스터(조도센서)
  {
    // 조도센서 값을 속도로 변환(map)하고 범위를 제한(constrain)
    int left_speed = map(right_light,
                         LIGHT_THRESHOLD_MIN, LIGHT_THRESHOLD_MAX,
                         SPEED_MIN, SPEED_MAX);
    left_speed = constrain(left_speed, SPEED_MIN, SPEED_MAX);
    Serial.print(left_speed);   // 모터 속도 출력
    forward("left", left_speed);  // 반대쪽(왼쪽) 모터 속도를 계산한 값으로 설정
  }
  else
  {
    Serial.print("0");
    brake("left");  // 조도센서 값이 임계치 이하일 경우 반대쪽 모터 정지
  }

  Serial.print("\tLeft: ");
  Serial.print(left_light);
  Serial.print(" ");
  if (left_light >= LIGHT_THRESHOLD_MIN)  // 왼쪽 포토레지스터(조도센서)
  {
    // 조도센서 값을 속도로 변환(map)하고 범위를 제한(constrain)
    int right_speed = map(left_light,
                          LIGHT_THRESHOLD_MIN, LIGHT_THRESHOLD_MAX,
                          SPEED_MIN, SPEED_MAX);
    right_speed = constrain(right_speed, SPEED_MIN, SPEED_MAX);
    Serial.println(right_speed);  // 모터 속도 출력
    forward("right", right_speed);  // 반대쪽(오른쪽) 모터 속도를 계산한 값으로 설정
  }
  else
  {
    Serial.println("0");
    brake("right");     // 조도센서 값이 임계치 이하일 경우 반대쪽 모터 정지
  }
}

// 모터 회전 속도를 지정한 값(0~255)으로 설정
// 모터는 "left" 또는 "right"로 왼쪽 또는 오른쪽 모터 지정
void forward (String motor, int rate)
{
  if (motor == "left")
  {
    digitalWrite(LEFT_EN, LOW);
    digitalWrite(LEFT_MC1, HIGH);
    digitalWrite(LEFT_MC2, LOW);
    analogWrite(LEFT_EN, rate);
  }
  else if (motor == "right")
  {
    digitalWrite(RIGHT_EN, LOW);
    digitalWrite(RIGHT_MC1, HIGH);
    digitalWrite(RIGHT_MC2, LOW);
    analogWrite(RIGHT_EN, rate);
  }
}

// 모터 정지, 정지하는 모터는 "left" 또는 "right"로 왼쪽 또는 오른쪽 모터 지정
void brake (String motor)
{
  if (motor == "left")
  {
    digitalWrite(LEFT_EN, LOW);
    digitalWrite(LEFT_MC1, LOW);
    digitalWrite(LEFT_MC2, LOW);
    digitalWrite(LEFT_EN, HIGH);
  }
  else if (motor == "right")
  {
    digitalWrite(RIGHT_EN, LOW);
    digitalWrite(RIGHT_MC1, LOW);
    digitalWrite(RIGHT_MC2, LOW);
    digitalWrite(RIGHT_EN, HIGH);
  }
}
