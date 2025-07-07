// 방의 출입 데이터 로깅

// PCF8523이 아니라 DS1307 칩을 사용하는 경우 주석 표시를 제거해야 한다.
//#define RTC_CHIP_IS_DS1307

// 강제로 시간을 설정하기 위해서는 주석 표시를 제거해야 한다.
// 현장에 설치하여 사용할 때에는 주석으로 처리되어 있어야 한다.
//#define FORCE_UPDATE

#include <SD.h>     // SD 카드 라이브러리 포함
#include <Wire.h>     // RTC의 I2C 통신을 위한 라이브러리
#include "RTClib.h"     // RTC 라이브러리

// SD 카드는 하드웨어 SPI 핀에 연결되어 있고
// RTC는 하드웨어 I2C 핀에 연결되어 있다.

// 디폴트값을 사용하는 경우에도 CS 핀을 항상 지정해야 한다.
const int CS_PIN = 10;

// 적외선 거리 센서는 아날로그 0번 A0 핀에 연결한다.
const int IR_PIN = 0;

// 사용하는 RTC 칩 종류에 따라 생성되는 RTC 객체 종류 지정
#ifdef RTC_CHIP_IS_DS1307
RTC_DS1307 RTC;
String chip = "DS1307";
#else
RTC_PCF8523 RTC;
String chip = "PCF8532";
#endif

// RTC 시간의 변경 여부 결정
#ifdef FORCE_UPDATE
bool update_clock = true;
#else
bool update_clock = false;
#endif

// 날짜와 시간을 나타내는 문자열 변수
String time, date;

// 거리 측정과 관련된 변수 초기화
int raw = 0;
int raw_prev = 0;
boolean active = false;
int update_time = 0;

void updateDateTime()
{
  // 현재 날짜와 시간 정보를 문자열로 변환
  DateTime datetime = RTC.now();
  String year = String(datetime.year(), DEC);
  String month = String(datetime.month(), DEC);
  String day = String(datetime.day(), DEC);
  String hour = String(datetime.hour(), DEC);
  String minute = String(datetime.minute(), DEC);
  String second = String(datetime.second(), DEC);

  // 날짜와 시간 정보를 하나의 문자열로 연결
  date = year + "/" + month + "/" + day;
  time = hour + ":" + minute + ":" + second;
}

void setup()
{
  Serial.begin(9600);

  // CS 핀은 출력으로 설정해야 한다.
  pinMode(CS_PIN, OUTPUT);

  // RTC 라이브러리 초기화
  RTC.begin();

  // RTC가 동작하지 않는 경우에는 RTC의 현재 시간을 업데이트
#ifdef RTC_CHIP_IS_DS1307
  if (!RTC.isrunning()) update_clock = true;
#else
  if (!RTC.initialized()) update_clock = true;
#endif

  // RTC가 동작하지 않거나 강제 업데이트를 선택한 경우
  // RTC 시간을 컴퓨터의 컴파일 시간으로 설정
  if (update_clock)
  {
    Serial.print(F("Setting "));
    Serial.print(chip);
    Serial.print(F(" time to compile time..."));
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
    Serial.println(F("Done!"));
  }
  else
  {
    Serial.print(chip);
    Serial.println(F(" time is already set!"));
  }

  // 날짜와 시간 출력
  updateDateTime();
  Serial.print(F("RTC Date: "));
  Serial.println(date);
  Serial.print(F("RTC time: "));
  Serial.println(time);

  // SD 카드 초기화
  Serial.print(F("Initializing SD Card..."));
  if (!SD.begin(CS_PIN))
  {
    Serial.println(F("Card Failure!"));
    while (1);
  }
  Serial.println(F("Card Ready!"));

  // 열의 헤더 출력
  File dataFile = SD.open("log.csv", FILE_WRITE);
  if (dataFile)
  {
    dataFile.println(F("\nNew Log Started!"));
    dataFile.println(F("Date,Time,Raw,Active"));
    dataFile.close(); //Data isn't written until we run close()!

    // 디버깅 목적으로 화면에 같은 내용을 출력
    Serial.println(F("\nNew Log Started!"));
    Serial.println(F("Date,Time,Raw,Active"));
  }
  else
  {
    Serial.println(F("Couldn't open log file"));
    while (1);
  }
}

void loop()
{
  updateDateTime();     // 현재 날짜와 시간 얻기

  // 움직임 데이터 수집, 아날로그 거리 센서 값 읽기
  raw = analogRead(IR_PIN);
  // 이전 센서값과 75 이상 차이가 나는 경우는
  // 센서 앞에서 물체가 움직였음을 나타낸다.
  if (abs(raw - raw_prev) > 75)
    active = true;
  else
    active = false;
  raw_prev = raw;

  // 데이터를 쓰기 위해 파일 열기
  if (active || update_time == 20)
  {
    File dataFile = SD.open("log.csv", FILE_WRITE);
    if (dataFile)
    {
      dataFile.print(date);
      dataFile.print(F(","));
      dataFile.print(time);
      dataFile.print(F(","));
      dataFile.print(raw);
      dataFile.print(F(","));
      dataFile.println(active);
      dataFile.close();     // 연결을 닫을 때까지 데이터는 파일에 기록되지 않음

      // 디버깅 목적으로 화면에 같은 내용을 출력
      Serial.print(date);
      Serial.print(F(","));
      Serial.print(time);
      Serial.print(F(","));
      Serial.print(raw);
      Serial.print(F(","));
      Serial.println(active);
    }
    else
    {
      Serial.println(F("Couldn't open log file"));
    }
    update_time = 0;
  }
  delay(50);
  update_time++;
}
