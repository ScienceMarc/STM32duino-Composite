#pragma once

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

namespace VIDEO {

// You can define your own width and height if the defaults do not suite you for
// some reason (like you neeed more ram but don't want to use slow mode or
// something)
#if !defined(WIDTH) && !defined(HEIGHT)
#ifdef SLOW_MODE
const int height = 64;
const int width = 32;
#endif
#ifndef SLOW_MODE
const int height = 128;
const int width = 128;
#endif
#else
const int height = HEIGHT;
const int width = WIDTH;
#endif

bool matrix[height][width];
volatile int lines = 1;

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

void putPixel(int x, int y, bool color) { matrix[y + 1][x + 1] = color; }
void drawFastHLine(int x, int y, int length, bool color) {
    for (int i = 0; i < length; i++) {
        putPixel(i + x, y, color);
    }
}
void drawFastVLine(int x, int y, int length, bool color) {
    for (int i = 0; i < length; i++) {
        putPixel(x, i + y, color);
    }
}
void drawFullRect(int x1, int y1, int x2, int y2, bool color) {
    for (int i = 0; i < y2-y1; i++) {
        drawFastHLine(x1,y1 + i, x2 - x1, color);
    }
}
void drawRect(int x1, int y1, int x2, int y2, bool color) {
    drawFastHLine(x1, y1, x2 - x1, color);
    drawFastVLine(x1, y1, y2 - y1, color);
    drawFastVLine(x2, y1, y2 - y1, color);
    drawFastHLine(x1, y2, x2 - x1 + 1, color);
}

void pulse(bool white) {  // Either sends a pulse or turns it off based on the
                          // color of the pixel
    if (white) {
        signalOn;
    } else {
        signalOff;
    }
}

void drawRow(bool arr[]) {  // Draws a row from the matrix to the screen
    for (int i = 0; i < width; i++) {
        pulse(arr[i]);
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
        NOP;/*
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;
        NOP;*/
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
        if ((lines - 33) / pixelHeight <= height - 1) {
            drawRow(matrix[min(height - 1, (lines - 33) / pixelHeight)]);
        }
    }

    lines++;
}

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
    timer.attachCompare1Interrupt(line);
    timer.refresh();
    timer.resume();
}

}  // namespace VIDEO