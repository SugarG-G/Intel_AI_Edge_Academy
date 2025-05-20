#include <Keyboard.h>

const int TEMP = 0;     // 온도 센서를 아날로그 0번 핀에 연결
const int LIGHT = 1;    // 조도 센서를 아날로그 1번 핀에 연결
const int LED = 3;    // 붉은색 LED를 3번 핀에 연결
const int BUTTON = 2;     // 버튼을 2번 핀에 연결

boolean lastButton = LOW;   // 이전 버튼 상태
boolean currentButton = LOW;  // 현재 버튼 상태
boolean running = false;  // 디폴트 값은 로깅 기능이 꺼진 상태임
int counter = 1;    // 로깅하는 데이터 항목의 인덱스

void setup()
{
  pinMode (LED, OUTPUT);  // LED 연결 핀을 출력으로 설정
  Keyboard.begin();     // 키보드 에뮬레이션 시작
}

void loop()
{
  currentButton = debounce(lastButton);     // 디바운싱 처리된 버튼 상태 읽기

  if (lastButton == LOW && currentButton == HIGH)   // 버튼을 누른 경우
    running = !running;           // 로깅 기능 반전

  lastButton = currentButton;   // 버튼 상태 초기화

  if (running)      // 현재 데이터 로깅 기능이 켜진 상태인 경우
  {
    digitalWrite(LED, HIGH);  // LED 켜기
    if (millis() % 1000 == 0)   // 경과 시간이 1000의 정수배인 경우
    {
      int temperature = analogRead(TEMP);   // 온도 읽기
      int brightness = analogRead(LIGHT);   // 조도 읽기

      Keyboard.print(counter);      // 인덱스 값 타이핑
      Keyboard.print(",");      // 콤마 타이핑
      Keyboard.print(temperature);    // 온도 타이핑
      Keyboard.print(",");      // 콤마 타이핑
      Keyboard.println(brightness);     // 조도와 새 줄(리턴) 타이핑

      counter++;        // 인덱스 값 증가
    }
  }
  else
  {
    digitalWrite(LED, LOW);     // 로깅 기능이 꺼진 상태일 때 LED 끄기
  }
}

/*
  디바운싱 함수
  이전 버튼의 상태를 매개변수로 받고
  디바운싱 처리된 현재 버튼 상태를 반환
*/
boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON);  // 현재 버튼 상태 읽기
  if (last != current)      // 이전 상태와 다른 경우
  {
    delay(5);         // 5밀리초 대기
    current = digitalRead(BUTTON);  // 버튼 상태 다시 읽기
  }
  return current;       // 현재 버튼 상태 반환
}
