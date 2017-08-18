#ifndef _T6963_H
#define _T6963_H

#include <DisplayCore.h>

class T6963 : public DisplayCore {
    private:
    public:
        uint8_t _buffer[2048];

        uint8_t _rd;
        uint8_t _wr;
        uint8_t _cd;
        uint8_t _ce;

        uint8_t _d0;
        uint8_t _d1;
        uint8_t _d2;
        uint8_t _d3;
        uint8_t _d4;
        uint8_t _d5;
        uint8_t _d6;
        uint8_t _d7;

        uint8_t _res;

        int _buffered;

        static const uint8_t T6963_CURSOR_PATTERN_SELECT = 0xA0;
        static const uint8_t T6963_DISPLAY_MODE = 0x90;
        static const uint8_t T6963_MODE_SET = 0x80;
        static const uint8_t T6963_SET_CURSOR_POINTER = 0x21;
        static const uint8_t T6963_SET_OFFSET_REGISTER = 0x22;
        static const uint8_t T6963_SET_ADDRESS_POINTER = 0x24;
        static const uint8_t T6963_SET_TEXT_HOME_ADDRESS = 0x40;
        static const uint8_t T6963_SET_TEXT_AREA = 0x41;
        static const uint8_t T6963_SET_GRAPHIC_HOME_ADDRESS = 0x42;
        static const uint8_t T6963_SET_GRAPHIC_AREA = 0x43;
        static const uint8_t T6963_SET_DATA_AUTO_WRITE = 0xB0;
        static const uint8_t T6963_SET_DATA_AUTO_READ = 0xB1;
        static const uint8_t T6963_AUTO_RESET = 0xB2;

        static const uint8_t T6963_DATA_WRITE_AND_INCREMENT = 0xC0;
        static const uint8_t T6963_DATA_READ_AND_INCREMENT = 0xC1;
        static const uint8_t T6963_DATA_WRITE_AND_DECREMENT = 0xC2;
        static const uint8_t T6963_DATA_READ_AND_DECREMENT = 0xC3;
        static const uint8_t T6963_DATA_WRITE_AND_NONVARIALBE = 0xC4;
        static const uint8_t T6963_DATA_READ_AND_NONVARIABLE = 0xC5;

        static const uint8_t T6963_SCREEN_PEEK = 0xE0;
        static const uint8_t T6963_SCREEN_COPY = 0xE8;

        void data(uint8_t d);
        void command(uint8_t c);



    public:

        T6963(
            uint8_t rd, uint8_t wr, uint8_t cd, uint8_t ce,
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
            uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
            uint8_t res = 255
        ) : _rd(rd), _wr(wr), _cd(cd), _ce(ce),
            _d0(d0), _d1(d1), _d2(d2), _d3(d3),
            _d4(d4), _d5(d5), _d6(d6), _d7(d7),
            _res(res), _buffered(0) {
            _width = 256;
            _height = 64;
        }

        void initializeDevice();

        void invertDisplay(boolean __attribute__((unused)) i) {}
        void displayOn() {}
        void displayOff() {}
        void setRotation(int __attribute__((unused)) rotation) {}
        void setPixel(int x, int y, color_t color);

        void startBuffer();
        void endBuffer();

        void fillScreen(color_t c);

};

#endif
