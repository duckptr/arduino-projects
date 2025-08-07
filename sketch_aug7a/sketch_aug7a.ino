#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C 주소와 LCD 크기 (모듈에 맞춰 조정)
#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

void setup() {
  Wire.begin();            // I2C 버스 시작
  lcd.init();              // LCD 초기화
  lcd.backlight();         // 백라이트 켜기
  lcd.clear();             // 화면 지우기

  // 첫 줄에 메시지 출력
  lcd.setCursor(0, 0);
  lcd.print("Hello, Arduino!");
  
  // 둘째 줄에 추가 메시지 (원하면 삭제)
  lcd.setCursor(0, 1);
  lcd.print("LCD Test");
}

void loop() {
  // 여기는 비워두어도 됩니다.
}
