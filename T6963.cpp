#include <T6963.h>

void T6963::initializeDevice() {
    pinMode(_wr, OUTPUT);
    pinMode(_rd, OUTPUT);
    pinMode(_cd, OUTPUT);
    pinMode(_ce, OUTPUT);
    pinMode(_d0, OUTPUT);
    pinMode(_d1, OUTPUT);
    pinMode(_d2, OUTPUT);
    pinMode(_d3, OUTPUT);
    pinMode(_d4, OUTPUT);
    pinMode(_d5, OUTPUT);
    pinMode(_d6, OUTPUT);
    pinMode(_d7, OUTPUT);
    digitalWrite(_wr, HIGH);
    digitalWrite(_rd, HIGH);
    digitalWrite(_cd, HIGH);
    digitalWrite(_ce, LOW);
    data(0);
    data(0);
    command(T6963_SET_GRAPHIC_HOME_ADDRESS);
    data(256 / 8);
    data(0);
    command(T6963_SET_GRAPHIC_AREA);
    data(0);
    data(8);
    command(T6963_SET_TEXT_HOME_ADDRESS);
    data(256 / 8);
    data(0);
    command(T6963_SET_TEXT_AREA);
    //data(((32 / 2) - 1));
    data(0b11110);
    data(0x0);
    command(T6963_SET_OFFSET_REGISTER);
    command(T6963_DISPLAY_MODE | 0b1000);
    command(T6963_MODE_SET);
}

void T6963::setPixel(int x, int y, color_t color) {
    uint8_t row;
    uint8_t col;
    uint8_t pixel;
    uint8_t mask;

    if((x < 0) ||(x >= 256) || (y < 0) || (y >= 64))
        return;

    row = y;
    col = x >> 3;
    pixel = x & 0x07;
    mask = 1<<(7 - pixel);
    if (color) {
        _buffer[col | (row * 32)] |= mask;
    } else {
        _buffer[col | (row * 32)] &= ~mask;
    }

    if (_buffered == 0) {
        data(0);
        data(0);
        command(T6963_SET_ADDRESS_POINTER);
        command(T6963_SET_DATA_AUTO_WRITE);

        for (int i = 0; i < 2048; i++) {
            data(_buffer[i]);
        }

        command(T6963_AUTO_RESET);
    }
}

void T6963::data(uint8_t d) {
    digitalWrite(_cd, LOW);
    digitalWrite(_d0, d & 0x01);
    digitalWrite(_d1, d & 0x02);
    digitalWrite(_d2, d & 0x04);
    digitalWrite(_d3, d & 0x08);
    digitalWrite(_d4, d & 0x10);
    digitalWrite(_d5, d & 0x20);
    digitalWrite(_d6, d & 0x40);
    digitalWrite(_d7, d & 0x80);
    digitalWrite(_wr, LOW);
    delayMicroseconds(1);
    digitalWrite(_wr, HIGH);
}

void T6963::command(uint8_t d) {
    digitalWrite(_cd, HIGH);
    digitalWrite(_d0, d & 0x01);
    digitalWrite(_d1, d & 0x02);
    digitalWrite(_d2, d & 0x04);
    digitalWrite(_d3, d & 0x08);
    digitalWrite(_d4, d & 0x10);
    digitalWrite(_d5, d & 0x20);
    digitalWrite(_d6, d & 0x40);
    digitalWrite(_d7, d & 0x80);
    digitalWrite(_wr, LOW);
    delayMicroseconds(1);
    digitalWrite(_wr, HIGH);
}

void T6963::endBuffer() {
    _buffered--;
    if (_buffered <= 0) {
        _buffered = 0;
        data(0);
        data(0);
        command(T6963_SET_ADDRESS_POINTER);
        command(T6963_SET_DATA_AUTO_WRITE);

        for (int i = 0; i < 2048; i++) {
            data(_buffer[i]);
        }

        command(T6963_AUTO_RESET);
    }
}

void T6963::startBuffer() {
    _buffered++;
}

void T6963::fillScreen(color_t c) {
    memset(_buffer, c ? 255 : 0, 2048);
    if (_buffered == 0) {
        data(0);
        data(0);
        command(T6963_SET_ADDRESS_POINTER);
        command(T6963_SET_DATA_AUTO_WRITE);

        for (int i = 0; i < 2048; i++) {
            data(_buffer[i]);
        }

        command(T6963_AUTO_RESET);
    }
}

