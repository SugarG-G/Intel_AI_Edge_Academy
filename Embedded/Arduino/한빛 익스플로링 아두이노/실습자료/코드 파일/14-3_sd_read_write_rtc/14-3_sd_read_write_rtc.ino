// RTC를 사용한 SD 카드 읽기와 쓰기

// PCF8523이 아니라 DS1307 칩을 사용하는 경우 아래 문장의 주석 기호를 삭제해야 한다.
//#define RTC_CHIP_IS_DS1307


// 강제로 시간을 설정하기 위해서는 아래 문장의 주석 기호를 삭제해야 한다. 
// 현장에 설치하여 사용할 때에는 아래 문장의 주석 기호를 삭제해서는 안 된다. 
//#define FORCE_UPDATE

#include <SD.h>     // SD 카드 라이브러리 포함
#include <Wire.h>     // RTC의 I2C 통신을 위한 라이브러리
#include "RTClib.h"     // RTC 라이브러리

// SD 카드는 하드웨어 SPI 핀에 연결되어 있고
// RTC는 하드웨어 I2C 핀에 연결되어 있다. 

// 디폴트값을 사용하는 경우에도 CS 핀을 항상 지정해야 한다. 
const int CS_PIN = 10;

// 디폴트 갱신 주기 5초는 speed.txt 파일 내용으로 교체될 수 있다. 
int refresh_rate = 5000;

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

  // 갱신 주기 정보(speed.txt)를 읽어 갱신 주기 설정
  File commandFile = SD.open("speed.txt");
  if (commandFile)
  {
    Serial.print(F("Reading Command File..."));

    while (commandFile.available())
    {
      refresh_rate = commandFile.parseInt();
    }
    Serial.print(F("Refresh Rate = "));
    Serial.print(refresh_rate);
    Serial.println(F("ms"));
    commandFile.close();  // 읽기가 끝나면 파일 닫음
  }
  else
  {
    Serial.println(F("Could not read command file."));
    Serial.print(F("Will use default refresh rate of "));
    Serial.print(refresh_rate);
    Serial.println(F("ms!"));
  }

  // 열의 헤더 출력
  File dataFile = SD.open("log.csv", FILE_WRITE);
  if (dataFile)
  {
    dataFile.println(F("\nNew Log Started!"));
    dataFile.println(F("Date,Time,Phrase"));
    dataFile.close(); //Data isn't written until we run close()!

    // 디버깅 목적으로 화면에 같은 내용을 출력
    Serial.println(F("\nNew Log Started!"));
    Serial.println(F("Date,Time,Phrase"));
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
  String dataString = "Hello There!";

  // 데이터를 쓰기 위해 파일 열기
  File dataFile = SD.open("log.csv", FILE_WRITE);
  if (dataFile)
  {
    dataFile.print(date);
    dataFile.print(F(","));
    dataFile.print(time);
    dataFile.print(F(","));
    dataFile.println(dataString);
    dataFile.close();     // 연결을 닫을 때까지 데이터는 파일에 기록되지 않음

    // 디버깅 목적으로 화면에 같은 내용을 출력
    Serial.print(date);
    Serial.print(F(","));
    Serial.print(time);
    Serial.print(F(","));
    Serial.println(dataString);
  }
  else
  {
    Serial.println(F("Couldn't open log file!"));
  }
  delay(refresh_rate);
}
