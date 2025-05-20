// SD 카드 읽기와 쓰기

#include <SD.h>     // SD 카드 라이브러리 포함

// 이들 핀은 SD 카드 라이브러리에서 디폴트값으로 정의되어 있다.
// MOSI = Pin 11
// MISO = Pin 12
// SCLK = PIN 13

// 디폴트값을 사용하는 경우에도 CS 핀을 항상 지정해야 한다.
const int CS_PIN = 10;

// 디폴트 갱신 주기는 5초
int refresh_rate = 5000;

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing Card");

  // CS 핀은 출력으로 설정해야 한다.
  pinMode(CS_PIN, OUTPUT);

  if (!SD.begin(CS_PIN))
  {
    Serial.println("Card Failure");
    while (1);
  }
  Serial.println("Card Ready");

  // speed.txt 파일에서 설정 정보 읽기
  File commandFile = SD.open("speed.txt");
  if (commandFile)
  {
    Serial.println("Reading Command File");

    while (commandFile.available())
    {
      refresh_rate = commandFile.parseInt();
    }
    Serial.print("Refresh Rate = ");
    Serial.print(refresh_rate);
    Serial.println("ms");
    commandFile.close();  // 읽기가 끝나면 파일 닫음
  }
  else
  {
    Serial.println("Could not read command file.");
    Serial.print("Will use default refresh rate of ");
    Serial.print(refresh_rate);
    Serial.println("ms!");
  }
}

void loop()
{
  long timeStamp = millis();
  String dataString = "Hello There!";

  // 데이터를 쓰기 위해 파일 열기
  File dataFile = SD.open("log.csv", FILE_WRITE);
  if (dataFile)
  {
    dataFile.print(timeStamp);
    dataFile.print(",");
    dataFile.println(dataString);
    dataFile.close();     // 연결을 닫을 때까지 데이터는 파일에 기록되지 않음

    // 디버깅 목적으로 화면에 같은 내용을 출력
    Serial.print(timeStamp);
    Serial.print(",");
    Serial.println(dataString);
  }
  else
  {
    Serial.println("Couldn't open log file");
  }
  delay(refresh_rate);
}
