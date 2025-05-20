// LCD에 문자열과 증가하는 숫자 표시

// LCD 라이브러리 포함
#include <LiquidCrystal.h>

// 시간은 0부터 시작
int time = 0;

// LCD 연결에 사용된 아두이노 핀으로 라이브러리 초기화
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup()
{
  // LCD를 지정한 수의 행과 열로 설정
  lcd.begin(16, 2);
  // LCD에 문자열 출력
  lcd.print("Jeremy's Display");
}

void loop()
{
  // 커서를 두 번째 줄 첫 번째 칸으로 옮김
  lcd.setCursor(0, 1);
  // 현재 시간 표시
  lcd.print(time);
  // 1초 대기
  delay(1000);
  // 시간 증가
  time++;
}
