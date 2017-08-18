#include <T6963.h>
#include <Display7Seg.h>
#include <Topaz.h>

// RD  WR  CD  CE  D0  D1  D2  D3  D4  D5  D6  D7
T6963 lcd(35, 34, 37, 36, 26, 27, 28, 29, 30, 31, 32, 33);
    
void setup() {
    lcd.initializeDevice();
}

void loop() {
    lcd.setCursor(10, 10);
    lcd.startBuffer();
    lcd.fillScreen(Color::Black);
    uint32_t tsecs = millis() / 1000;
    uint32_t secs = tsecs % 60;
    uint32_t mins = (tsecs / 60) % 60;
    uint32_t hours = (tsecs / 3600) % 24;
    uint32_t tens = (millis() / 100) % 10;
    lcd.setFont(Fonts::Display7Seg48);
    lcd.printf("%02d %02d %02d %d",
        hours, mins, secs, tens);
    lcd.fillCircle(69, 20, 4, Color::White);
    lcd.fillCircle(69, 41, 4, Color::White);
    lcd.fillCircle(69+72, 20, 4, Color::White);
    lcd.fillCircle(69+72, 41, 4, Color::White);
    lcd.fillCircle(69+72+72, 20, 4, Color::White);
    lcd.fillCircle(69+72+72, 41, 4, Color::White);

    lcd.setFont(Fonts::Topaz);
    lcd.setTextColor(Color::White, Color::White);
    lcd.setCursor(58, 45);
    lcd.print("h");
    lcd.setCursor(58+72, 45);
    lcd.print("m");
    lcd.setCursor(58+72+72, 45);
    lcd.print("s");
    lcd.endBuffer();
    delay(10);
}
