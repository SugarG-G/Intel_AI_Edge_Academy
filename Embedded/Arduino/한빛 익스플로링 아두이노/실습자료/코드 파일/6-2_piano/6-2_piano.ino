// 5음 음계 피아노 : C(도), D(레), E(미), G(솔), A(라)
#define NOTE_C 262       // C(도) 음의 주파수(Hz)
#define NOTE_D 294      // D(레) 음의 주파수(Hz)
#define NOTE_E 330      // E(미) 음의 주파수(Hz)
#define NOTE_G 392      // G(솔) 음의 주파수(Hz)
#define NOTE_A 440      // A(라) 음의 주파수(Hz)

const int SPEAKER = 9;      // 스피커를 9번 핀에 연결

const int BUTTON_C = 7;     // C(도) 음에 해당하는 버튼 연결 핀
const int BUTTON_D = 6;     // D(레) 음에 해당하는 버튼 연결 핀
const int BUTTON_E = 5;     // E(미) 음에 해당하는 버튼 연결 핀
const int BUTTON_G = 4;     // G(솔) 음에 해당하는 버튼 연결 핀
const int BUTTON_A = 3;     // A(라) 음에 해당하는 버튼 연결 핀

void setup()
{
  // tone() 함수는 입출력 핀을 출력으로 설정하므로
  // 초기화 작업은 필요하지 않음
}

void loop()
{
  while (digitalRead(BUTTON_C))
    tone(SPEAKER, NOTE_C);
  while (digitalRead(BUTTON_D))
    tone(SPEAKER, NOTE_D);
  while (digitalRead(BUTTON_E))
    tone(SPEAKER, NOTE_E);
  while (digitalRead(BUTTON_G))
    tone(SPEAKER, NOTE_G);
  while (digitalRead(BUTTON_A))
    tone(SPEAKER, NOTE_A);

  // 모든 버튼이 눌러지지 않은 경우 음 재생을 멈춤
  noTone(SPEAKER);
}
