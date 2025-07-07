// 온도조절기로 시원하게 지내보자!
// 이 예제에서 온도는 항상 두 자리로 측정되는 것으로 가정한다.

// I2C 통신을 위한 Wire 라이브러리 포함 및 온도 센서의 주소 정의
#include <Wire.h>
#define TEMP_ADDR 72

// LCD 라이브러리 포함 및 초기화
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// 온도 기호 사용자 문자
byte degree[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000,
};

// 팬 켜짐 사용자 문자
byte fan_on[8] = {
  B00100,
  B10101,
  B01110,
  B11111,
  B01110,
  B10101,
  B00100,
  B00000,
};

// 팬 꺼짐 사용자 문자
byte fan_off[8] = {
  B00100,
  B00100,
  B00100,
  B11111,
  B00100,
  B00100,
  B00100,
  B00000,
};

// 핀 연결
const int SPEAKER = 8;
const int DOWN_BUTTON = 9;
const int UP_BUTTON = 10;
const int FAN = 11;

// 디바운싱을 위한 변수
boolean lastDownTempButton = LOW;
boolean currentDownTempButton = LOW;
boolean lastUpTempButton = LOW;
boolean currentUpTempButton = LOW;

int set_temp = 23;    // 설정 온도 디폴트값
boolean one_time = false;   // 경고음 1회 재생을 위한 상태 변수

void setup()
{
  pinMode(FAN, OUTPUT);

  // 온도 센서를 위한 Wire 객체 생성
  Wire.begin();

  // LCD의 행과 열 수 설정
  lcd.begin(16, 2);

  // 사용자 문자 생성
  lcd.createChar(0, degree);
  lcd.createChar(1, fan_off);
  lcd.createChar(2, fan_on);

  // LCD에 정적 메시지 출력
  lcd.setCursor(0, 0);
  lcd.print("Current:");
  lcd.setCursor(10, 0);
  lcd.write((byte)0);
  lcd.setCursor(11, 0);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Set:");
  lcd.setCursor(10, 1);
  lcd.write((byte)0);
  lcd.setCursor(11, 1);
  lcd.print("C");
  lcd.setCursor(15, 1);
  lcd.write(1);
}

// 2개 버튼을 모두 사용할 수 있도록 수정된 디바운싱 함수
boolean debounce(boolean last, int pin)
{
  boolean current = digitalRead(pin);
  if (last != current)
  {
    delay(5);
    current = digitalRead(pin);
  }
  return current;
}

void loop()
{
  // 온도값 읽어오기
  Wire.beginTransmission(TEMP_ADDR);  // 통신 시작
  Wire.write(0);        // 0번 레지스터 데이터 요청
  Wire.endTransmission();     // 요청 설정 종료

  // 1바이트 데이터 요청
  int returned_bytes = Wire.requestFrom(TEMP_ADDR, 1);

  // 슬레이브 장치에서 데이터를 수신하지 못한 경우, 오류 발생
  if (returned_bytes == 0)
  {
    lcd.clear();        // LCD 화면 지우기
    lcd.print("I2C Error");     // 오류 메시지 출력
    while (1);        //  프로그램 정지
  }

  int c = Wire.read();      // 섭씨 온도 얻기
  lcd.setCursor(8, 0);      // 커서 이동
  lcd.print(c);         // 온도 표시

  // 2개 버튼에 대한 디바운싱
  currentDownTempButton = debounce(lastDownTempButton, DOWN_BUTTON);
  currentUpTempButton = debounce(lastUpTempButton, UP_BUTTON);

  // 설정 온도 내림
  if (lastDownTempButton == LOW && currentDownTempButton == HIGH)
  {
    set_temp--;
  }
  // 설정 온도 올림
  else if (lastUpTempButton == LOW && currentUpTempButton == HIGH)
  {
    set_temp++;
  }

  // LCD에 설정 온도 변경
  lcd.setCursor(8, 1);
  lcd.print(set_temp);
  lastDownTempButton = currentDownTempButton;
  lastUpTempButton = currentUpTempButton;

  // 설정 온도 이상으로 온도가 오른 경우
  if (c >= set_temp)
  {

    // 처음 설정 온도 이상으로 온도가 올라 아직 스피커로 경고음을 재생하지 않은 경우
    if (!one_time)
    {
      tone(SPEAKER, 400);
      delay(500);
      one_time = true;
    }
    // 한 번 경고음을 재생한 후 스피커를 끔
    else
    {
      noTone(SPEAKER);
    }
    // 팬을 켜고 LCD에 팬 동작 문자 출력
    digitalWrite(FAN, HIGH);
    lcd.setCursor(15, 1);
    lcd.write(2);
  }
  // 설정 온도 미만인 경우
  else
  {
    noTone(SPEAKER);    // 경고음 재생을 중단
    one_time = false;   // 상태 변수 ’one_beep’ 초기화
    digitalWrite(FAN, LOW); // 팬을 끔
    lcd.setCursor(15, 1);
    lcd.write(1);     // 팬 정지 문자 출력
  }
}
