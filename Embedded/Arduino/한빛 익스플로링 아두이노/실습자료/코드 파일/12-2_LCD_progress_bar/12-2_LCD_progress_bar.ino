// LCD에 진행바 표시

// LCD 라이브러리 포함
#include <LiquidCrystal.h>

// LCD 연결에 사용된 아두이노 핀으로 라이브러리 초기화
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// 진행바를 나타내기 위한 사용자 문자 정의
byte p20[8] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
};
byte p40[8] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
};
byte p60[8] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
};
byte p80[8] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
};
byte p100[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

void setup()
{
  // LCD를 지정한 수의 행과 열로 설정
  lcd.begin(16, 2);
  // LCD에 문자열 출력
  lcd.print("Jeremy's Display");

  // 진행바 문자 생성
  lcd.createChar(0, p20);
  lcd.createChar(1, p40);
  lcd.createChar(2, p60);
  lcd.createChar(3, p80);
  lcd.createChar(4, p100);
}

void loop()
{
  // 커서를 두 번째 줄 첫 번째 칸으로 옮김
  lcd.setCursor(0, 1);
  // 두 번째 줄 끝에 도달하면 16개의 공백문자(‘ ’)로 두 번째 줄을 모두 지움
  lcd.print("                ");

  // 두 번째 줄의 16개 위치에 문자 표시
  for (int i = 0; i < 16; i++)
  {
    // 각 문자 위치에 5개의 진행바 문자 번갈아 표시
    for (int j = 0; j < 5; j++)
    {
      lcd.setCursor(i, 1);  // 커서 위치 이동
      lcd.write(j);     // 진행바 문자 변경
      delay(100);     // 0.1초 대기
    }
  }
}
