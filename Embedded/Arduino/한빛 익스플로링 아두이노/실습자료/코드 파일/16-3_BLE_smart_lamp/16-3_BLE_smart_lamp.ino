// 스마트폰의 연결 상태에 따라 자동으로 램프 제어

// nRF51 SPI 라이브러리 포함
#include "Adafruit_BluefruitLE_SPI.h"

// 32U4 Feather 보드에서 nRF51 칩은 하드웨어 SPI 핀에 연결되어 있다. 
// BLT 객체를 생성할 때는 칩 선택(CS, 8), 인터럽트(IRG, 7), 리셋(RST, 4) 등
// 3개 연결 핀만 매개변수로 지정하면 된다. 
Adafruit_BluefruitLE_SPI ble(8, 7, 4);

// 스마트폰에서 BLE 장치가 보여지는 이름
const String BLE_NAME = "Smart Lamp";

// 동작 범위를 제어하기 위한 전력 레벨 상수 설정
// 사용할 수 있는 옵션값 : -40, -20, -16, -12, -8, -4, 0, 4
// 숫자가 클수록 연결 범위는 늘어난다. 
const int POWER_LEVEL = -20;

// 전등 제어를 위한 핀
const int LAMP_PIN = 5;

void setup(void)
{
  // 전등 제어핀을 출력으로 설정하고 전등을 끔
  pinMode(LAMP_PIN, OUTPUT);
  digitalWrite(LAMP_PIN, LOW);

  // 시리얼 모니터로 디버깅 정보 출력
  Serial.begin(9600);

  // 32U4는 하드웨어로 지원되는 USB 인터페이스를 가지고 있으므로 
  // BLE 모듈을 초기화하기 전에 시리얼 모니터와 연결되어야 한다면
  // 아래 문장을 주석으로 처리하지 않고 그대로 두어야 한다. 
  // 시리얼 모니터를 사용하지 않거나 배터리로 동작하는 경우라면
  // 아래 문장을 주석으로 처리하는 것이 좋다. 
  // while (!Serial);

  // BLE 모듈에 연결
  Serial.print(F("Initializing BLE Module..."));
  if (!ble.begin())
  {
    Serial.println("");
    Serial.println(F("Couldn't connect to nRF51 Module."));
    while (1);
  }
  Serial.println(F("Ready!"));

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
  Serial.println(F("Done!"));

  // 전력 레벨 설정
  Serial.print(F("Setting Power level..."));
  ble.print(F("AT+BLEPOWERLEVEL="));
  ble.println(String(POWER_LEVEL));
  if (!ble.waitForOK())
  {
    Serial.println(F("Power Level Setting Error."));
    while (1);
  }
  Serial.println(F("Done!"));

  // HID 키보드 프로파일 활성화
  // 전용 애플리케이션 없이 연결이 가능하도록 하기 위해 필요하다. 
  Serial.print(F("Enabling HID Keyboard..."));
  ble.println(F("AT+BLEKEYBOARDEN=1"));
  if (!ble.waitForOK())
  {
    Serial.println(F("Could not enable HID Keyboard Profile."));
    while (1);
  }
  Serial.println(F("Done!"));

  ble.reset();        // 바뀐 설정이 적용되도록 모듈 리셋
}

void loop(void)
{
  if (ble.isConnected())
  {
    // BLE 장치와 연결된 경우 전등 켜기
    digitalWrite(LAMP_PIN, HIGH);
  }
  if (!ble.isConnected())
  {
    // BLE 장치와 연결이 끊어진 경우 전등 끄기
    digitalWrite(LAMP_PIN, LOW);
  }
}
