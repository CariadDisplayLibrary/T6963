#include <T6963.h>
#include <Display7Seg.h>
#include <Topaz.h>

// Adjust these to match your setup
#define PIN_RD 35
#define PIN_WR 34
#define PIN_CD 37
#define PIN_CE 36
#define PIN_D0 26
#define PIN_D1 27
#define PIN_D2 28
#define PIN_D3 29
#define PIN_D4 30
#define PIN_D5 31
#define PIN_D6 32
#define PIN_D7 33
#define PIN_RES 38

T6963 lcd(PIN_RD, PIN_WR, PIN_CD, PIN_CE, PIN_D0, PIN_D1, PIN_D2, PIN_D3, PIN_D4, PIN_D5, PIN_D6, PIN_D7, PIN_RES);

// Define your control button pin here
#define BUTTON PIN_BTN1

void setup() {
    lcd.initializeDevice();
    lcd.setTextColor(Color::White, Color::White);

    pinMode(BUTTON, INPUT);
}

void loop() {
    static uint32_t start = 0;
    static bool running = false;
    static bool buttonState = digitalRead(BUTTON);

    static uint32_t secs = 0;
    static uint32_t mins = 0;
    static uint32_t hours = 0;
    static uint32_t tens = 0;

    if (digitalRead(BUTTON) != buttonState) {
        buttonState = digitalRead(BUTTON);
        if (buttonState == HIGH) {
            running = !running;
            if (running) {
                start = millis();
            }
        }
    }

    if (running) {
        uint32_t tsecs = (millis() - start) / 1000;
        secs = tsecs % 60;
        mins = (tsecs / 60) % 60;
        hours = (tsecs / 3600) % 24;
        tens = ((millis() - start) / 100) % 10;
    }

    lcd.startBuffer();
    lcd.fillScreen(Color::Black);

    lcd.setFont(Fonts::Display7Seg48);
    lcd.setCursor(10, 10);
    lcd.printf("%02d %02d %02d %d",
        hours, mins, secs, tens);

    lcd.setFont(Fonts::Topaz);
    lcd.setCursor(58, 45);
    lcd.print("h");
    lcd.setCursor(58+72, 45);
    lcd.print("m");
    lcd.setCursor(58+72+72, 45);
    lcd.print("s");

    lcd.fillCircle(69, 20, 4, Color::White);
    lcd.fillCircle(69, 41, 4, Color::White);
    lcd.fillCircle(69+72, 20, 4, Color::White);
    lcd.fillCircle(69+72, 41, 4, Color::White);
    lcd.fillCircle(69+72+72, 20, 4, Color::White);
    lcd.fillCircle(69+72+72, 41, 4, Color::White);

    lcd.endBuffer();

    delay(10);
}
