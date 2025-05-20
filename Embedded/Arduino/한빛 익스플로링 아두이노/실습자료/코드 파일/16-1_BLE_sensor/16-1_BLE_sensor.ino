// BLE 연결을 통해 가변저항값을 전송

// nRF51 SPI 라이브러리 포함
#include "Adafruit_BluefruitLE_SPI.h"

// 32U4 Feather 보드에서 nRF51 칩은 하드웨어 SPI 핀에 연결되어 있다. 
// BLT 객체를 생성할 때는 칩 선택(CS, 8), 인터럽트(IRG, 7), 리셋(RST, 4) 등
// 3개 연결 핀만 매개변수로 지정하면 된다. 
Adafruit_BluefruitLE_SPI ble(8, 7, 4);

// BLE 모듈 설정이 필요한 경우 true로 설정한다.
// true로 설정되면 공장 초기화 후 브로드캐스트 이름을 변경한다. 
// true로 설정하여 매번 설정을 진행하여도 문제가 되지는 않는다. 
// 한 번 설정한 이후 다시 설정하지 않으려면 false로 설정하면 된다. 
const bool PERFORM_CONFIGURATION = true;

// 스마트폰에서 BLE 장치가 보여지는 이름
const String BLE_NAME = "Jeremy's Sensor";

// 가변저항을 A0 핀에 연결
const int POT = A0;

// 내장 LED는 13번 핀에 연결되어 있음
const int STATUS_LED = 13;

void setup(void)
{
  // LED 연결 핀을 출력으로 설정
  pinMode(STATUS_LED, OUTPUT);

  // 시리얼 터미널로 디버깅 정보 출력
  Serial.begin(9600);

  // 32U4는 하드웨어로 지원되는 USB 인터페이스를 가지고 있으므로 
  // BLE 모듈을 초기화하기 전에 시리얼 모니터와 연결되어야 한다면
  // 아래 문장을 주석으로 처리하지 않고 그대로 두어야 한다. 
  // 시리얼 모니터를 사용하지 않거나 배터리로 동작하는 경우라면
  // 아래 문장을 주석으로 처리하는 것이 좋다. 
  while (!Serial);

  // BLE 모듈에 연결
  Serial.print(F("Initializing BLE Module..."));
  if (!ble.begin())
  {
    Serial.println("");
    Serial.println(F("Couldn't connect to nRF51 Module."));
    while (1);
  }
  Serial.println(F("Ready!"));

  // 초기화가 지정된 경우 BLE 칩을 공장 초기화한다. 
  // 설정이 잘못되어 BLE 모듈이 정상적으로 동작하지 않는 경우
  // 모듈의 공장 초기화를 통해 복구할 수 있다. 
  // 공장 초기화 후에는 브로드캐스트 이름을 설정한다. 
  if (PERFORM_CONFIGURATION)
  {
    // 모듈의 공장 초기화
    Serial.print(F("Resetting to Defaults..."));
    if (!ble.factoryReset())
    {
      Serial.println("");
      Serial.println(F("Couldn't reset module."));
      while (1);
    }
    Serial.println(F("Done!"));

    // AT 명령으로 브로드캐스트 이름 설정
    Serial.print(F("Setting Device name..."));
    ble.print(F("AT+GAPDEVNAME="));
    ble.println(BLE_NAME);
    if (!ble.waitForOK())
    {
      Serial.println(F("Could not set name."));
      while (1);
    }
    ble.reset();      // 바뀐 이름이 적용되도록 모듈 리셋
    Serial.println(F("Done!"));
  }

  // 명령 모드에서 데이터 모드로 전환
  ble.setMode(BLUEFRUIT_MODE_DATA);
}

void loop(void)
{
  // 스마트폰과 블루투스 모듈이 연결되어 있지 않으면 연결될 때까지 대기
  if (!ble.isConnected())
  {
    Serial.print("Waiting to connect to a smartphone...");
    while (!ble.isConnected())
    {
      delay(1000);
    }
    Serial.println("Connected!");
  }

  // 가변저항값 읽기
  int val = analogRead(POT);

  // 시리얼 모니터로 가변저항값 출력
  Serial.print(F("Analog Value: "));
  Serial.print(val);
  Serial.print(F("\tSending..."));

  // BLE의 시리얼 통신 에뮬레이션을 통해 데이터를 BLE 모듈로 전송
  // 데이터 전송 중 LED 켬
  digitalWrite(STATUS_LED, HIGH);
  ble.println(val);

  // BLE 모듈이 데이터 수신을 확인할 때까지 대기
  ble.waitForOK();
  Serial.println(F("OK!"));
  digitalWrite(STATUS_LED, LOW);  // 전송 완료 후 LED 끔
}
