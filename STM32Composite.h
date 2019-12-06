#pragma once

#include "font8x6.h"

// Cheatsheet: http://www.batsocks.co.uk/readme/video_timing.htm

/*
 * Uncomment #define SLOW_MODE if you do not want to use the -O3 optimizer
 * this will increase the size of the pixels dramatically.
 * this is not recommended
 */
//#define SLOW_MODE

#define NOP __asm__ __volatile__("nop\n\t")

// Port manipulation

#define signalOn GPIOB->regs->BSRR = 0b0000001000000000
#define signalOff GPIOB->regs->BRR = 0b0000001000000000

#define syncOn GPIOB->regs->BSRR = 0b0000000100000000
#define syncOff GPIOB->regs->BRR = 0b0000000100000000

#define SYNC PB8
#define SIGNAL PB9

#define WHITE 0xF
#define BLACK 0x0

namespace VIDEO {

// You can define your own width and height if the defaults do not suite you for
// some reason (like you neeed more ram but don't want to use slow mode or
// something)
#if !defined(WIDTH) && !defined(HEIGHT)
#ifdef SLOW_MODE
const int height = 64;
const int width = 32;
uint8_t matrix[64][16];
#endif
#ifndef SLOW_MODE
const int height = 128;
const int width = 128;
uint8_t matrix[128][64];
#endif
#else
const int height = HEIGHT;
const int width = WIDTH;
uint8_t matrix[height][WIDTH/2];
#endif


volatile int lines = 1;

struct vector {
    int x,y;
};

vector cursorPosition;

void putPixel(int x, int y, uint8_t color) {
    y++;
    if (x % 2 == 0) {
        color <<= 4;
    }
    matrix[min(height - 1, y)][x/2] |= color;
}
void drawFastHLine(int x, int y, int length, uint8_t color) {
    for (int i = 0; i < length; i++) {
        putPixel(i + x, y, color);
    }
}
void drawFastVLine(int x, int y, int length, uint8_t color) {
    for (int i = 0; i < length; i++) {
        putPixel(x, i + y, color);
    }
}

void drawFullRect(int x1, int y1, int x2, int y2, uint8_t color) {
    for (int i = 0; i < y2 - y1; i++) {
        drawFastHLine(x1, y1 + i, x2 - x1, color);
    }
}
void drawRect(int x1, int y1, int x2, int y2, uint8_t color) {
    drawFastHLine(x1, y1, x2 - x1, color);
    drawFastVLine(x1, y1, y2 - y1, color);
    drawFastVLine(x2, y1, y2 - y1, color);
    drawFastHLine(x1, y2, x2 - x1 + 1, color);
}

// This is based on Bresenham's line algorithm:
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
namespace internalLinePlotting {  // This set of line drawing functions. I put
                                  // it in a separate nested namespace to avoid
                                  // confusion for the user.
void plotLineLow(int x1, int y1, int x2, int y2, uint8_t color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    int D = 2 * dy - dx;
    int y = y1;
    for (int x = x1; x < x2; x++) {
        putPixel(x, y, color);
        if (D > 0) {
            y += yi;
            D -= 2 * dy;
        }
        D += 2 * dy;
    }
}
void plotLineHigh(int x1, int y1, int x2, int y2, uint8_t color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    int D = 2 * dx - dy;
    int x = x1;

    for (int y = y1; y < y2; y++) {
        putPixel(x, y, color);
        if (D > 0) {
            x += xi;
            D -= 2 * dy;
        }
        D += 2 * dx;
    }
}
}  // namespace internalLinePlotting
void drawLine(int x1, int y1, int x2, int y2, uint8_t color) {
    if (abs(y2 - y1) < abs(x2 - x1)) {
        if (x1 > x2) {
            internalLinePlotting::plotLineLow(x2, y2, x1, y1, color);
        } else {
            internalLinePlotting::plotLineLow(x1, y1, x2, y2, color);
        }
    } else {
        if (y1 > y2) {
            internalLinePlotting::plotLineHigh(x2, y2, x1, y1, color);
        } else {
            internalLinePlotting::plotLineHigh(x1, y1, x2, y2, color);
        }
    }
}

void clear() { memset(VIDEO::matrix, 0, sizeof(VIDEO::matrix)); }
void drawTrig(int x1, int y1, int x2, int y2, int x3, int y3, uint8_t color) {
    drawLine(x1, y1, x2, y2, color);
    drawLine(x1, y1, x3, y3, color);
    drawLine(x2, y2, x3 + 1, y3, color);
}
void drawCircle(int x, int y, int radius, uint8_t color) {
    for (float a = 0; a < 360; a++) {
        putPixel(sin(a * 0.0174532925) * radius + x,
                 cos(a * 0.0174532925) * radius + y, color);
    }
}

void drawBMP(int x, int y, int width, int height, const uint8_t* image) {
    for (int i = 0; i < width * height; i++) {
        VIDEO::putPixel(x + (i % width), y + floor(i / width), pgm_read_byte_near(image + i));
    }
}
void setCursor(int x, int y) {
    cursorPosition.x = x;
    cursorPosition.y = y;
}
void drawChar(char character) {
    for (int i = 0; i < 8 * 6; i++) {
        putPixel(cursorPosition.x + floor(i / 8), cursorPosition.y + (i % 8), (pgm_read_byte_near(font6x8[character-0x20] + (int)(i/8)) >> i%8) & 1);
    }
    cursorPosition.x += 6;
    if (cursorPosition.x + 8 > width) {
        cursorPosition.x = 0;
        cursorPosition.y+=9;
    }
}
void print(String string) {
    for (int i = 0; i < string.length(); i++) {
        drawChar(string.charAt(i));
    }
}
void print(float number) {
    print(String(number));
}
namespace internalRendering {
void hSync() {
    signalOff;
    delayMicroseconds(1);  // Front porch
    syncOff;
    delayMicroseconds(4);  // Horizontal Sync
    syncOn;
    delayMicroseconds(7);  // Back porch
}

void vSync() {  //! THIS IS A FAKE PROGRESSIVE SCAN FOR PAL. TESTING SHOWS THIS
                //! DOES NOT REALLY WORK FOR NTSC. THIS MAY CAUSE DAMAGE TO AN
                //! OLD STYLE CRT BUT THAT MIGHT BE CONJECTURE.
                // TODO: Add support for NTSC.
                //* There are some strange timing issues with this and I'm not
                // sure as to why
    if (lines < 3) {
        signalOff;
        syncOff;
        delayMicroseconds(28);
        syncOn;
        delayMicroseconds(4);
        syncOff;
        delayMicroseconds(28);
        syncOn;
        lines++;
        return;
    } else if (lines == 3) {
        signalOff;
        syncOff;
        delayMicroseconds(27);
        syncOn;
        delayMicroseconds(4);

        syncOff;
        delayMicroseconds(2);
        syncOn;
        lines = 4;
        return;
    } else if (lines < 6) {
        signalOff;
        syncOff;
        delayMicroseconds(2);
        syncOn;
        delayMicroseconds(29);
        syncOff;
        delayMicroseconds(2);
        syncOn;
        lines++;
        return;
    } else if (lines > 309) {
        signalOff;
        syncOff;
        delayMicroseconds(2);
        syncOn;
        delayMicroseconds(29);
        syncOff;
        delayMicroseconds(2);
        syncOn;
        lines++;
        if (lines >= 313) {
            lines = 0;
        }
        return;
    }
}
void pulse(uint8_t white) {  // Either sends a pulse or turns it off based on the
                             // color of the pixel
    if (white > 0) {
        signalOn;
    } else {
        signalOff;
    }
}

void drawRow(uint8_t arr[]) {  // Draws a row from the matrix to the screen
    for (int i = 0; i < width/2; i++) {
        pulse(arr[i] >> 4);
//* These NOPs are to create a bit of delay because otherwise the pixels
//* are too small and are a little fuzzy because the signal did not have
//* time to rise and fall.
#ifndef SLOW_MODE
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
#endif
        pulse(arr[i] & 0xF);
#ifndef SLOW_MODE
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
#endif
    }
    signalOff;
}

#ifndef SLOW_MODE
const byte pixelHeight = 2;
#endif
#ifdef SLOW_MODE
const byte pixelHeight = 7;
#endif

void line() {
    vSync();
    hSync();
    if (lines > 33) {
        if ((lines - 33) / pixelHeight <= height - 2) {
            drawRow(matrix[min(height - 1, (lines - 33) / pixelHeight)]);
        }
    }

    lines++;
}
}  // namespace internalRendering
void begin() {
    pinMode(SYNC, OUTPUT);
    pinMode(SIGNAL, OUTPUT);
    pinMode(PB12, OUTPUT);
    HardwareTimer timer(1);  // Uses hardware timer 1.
                             //! THIS MAY AFFECT ALL PINS WHICH USE THIS TIMER
                             //! IF YOU TRY TO USE PWM.

    // This code adds an precise 64µS interrupt which calls line(), this is done
    // to ensure that the lines all take exactly 64µS like they should.
    timer.pause();
    timer.setPeriod(64);
    timer.setChannel1Mode(TIMER_OUTPUT_COMPARE);
    timer.setCompare(TIMER_CH1, 1);
    timer.attachCompare1Interrupt(internalRendering::line);
    timer.refresh();
    timer.resume();
}

}  // namespace VIDEO