// I2C 온도 센서에서 온도를 읽고
// 시리얼 통신을 통해 컴퓨터에 출력

// Wire 라이브러리 포함
#include <Wire.h>
int temp_address = 72;       // 온도 센서 주소로 2진수 1001000에 해당

void setup()
{
  // 9600 보율로 시리얼 통신 시작
  Serial.begin(9600);
  // Wire 클래스의 객체 생성 및 초기화
  Wire.begin();
}

void loop()
{
  // 데이터 전송 시작
  // 특정 주소의 슬레이브 장치로 주소를 전송함으로써 시작
  Wire.beginTransmission(temp_address);
  // 0번 데이터 레지스터의 온도 정보를 요청한다는 0의 값 전송
  Wire.write(0);
  // 전송 종료
  Wire.endTransmission();

  // 슬레이브 장치에서 온도 읽기
  // 특정 주소의 슬레이브 장치에 1바이트 정보 요청
  int returned_bytes = Wire.requestFrom(temp_address, 1);

  // 슬레이브 장치에서 데이터를 수신하지 못한 경우, 오류 발생
  if (returned_bytes == 0)
  {
    Serial.println("I2C Error");    // 오류 발생 출력
    while (1);        // 프로그램 정지
  }

  // 온도 정보를 읽어 변수에 저장
  int c = Wire.read();

  // 섭씨를 화씨로 변환
  int f = round(c * 9.0 / 5.0 + 32.0);

  // 시리얼 모니터로 섭씨와 화씨 온도 출력
  Serial.print(c);
  Serial.print("C ");
  Serial.print(f);
  Serial.println("F");

  delay(500);
}
