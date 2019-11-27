//Cheatsheet: http://www.batsocks.co.uk/readme/video_timing.htm

//#include <SPI.h>

#define NOP __asm__ __volatile__ ("nop\n\t")

#define signalOn GPIOB->regs->BSRR = 0b0000001000000000
#define signalOff GPIOB->regs->BRR = 0b0000001000000000

#define syncOn GPIOB->regs->BSRR  =  0b0000000100000000
#define syncOff GPIOB->regs->BSRR =  0b0000000100000000

#define SYNC PB8
#define SIGNAL PB9

HardwareTimer timer(1); //Uses hardware timer 1.
                        //! THIS MAY AFFECT ALL PINS WHICH USE THIS TIMER IF YOU TRY TO USE PWM.

volatile int lines = 1;

void setup() {
    pinMode(SYNC, OUTPUT);
    pinMode(SIGNAL, OUTPUT);
    pinMode(PB12, OUTPUT);

    Serial.begin(9600);

    //This code adds an precise 64µS interrupt which calls line(), this is done to ensure that the lines all take exactly 64µS like they should.
    timer.pause();
    timer.setPeriod(64);
    timer.setChannel1Mode(TIMER_OUTPUT_COMPARE);
    timer.setCompare(TIMER_CH1,1);
    timer.attachCompare1Interrupt(line);
    timer.refresh();
    timer.resume();
}

void loop() {
    
}

bool row1[] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,};
bool row2[] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,};
bool row3[] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,};
bool row4[] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,};
bool row5[] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,};
bool row6[] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,};
bool row7[] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,};
bool row8[] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,};

void line() {
    vSync();
    hSync();
    if (lines > 33) {
        if (lines - 33 < 4) {
            drawRow(row1);
        }
        else if (lines - 33 < 4+4*1) {
            drawRow(row2);
        }
        else if (lines - 33 < 4+4*2) {
            drawRow(row3);
        }
        else if (lines - 33 < 4+4*3) {
            drawRow(row4);
        }
        else if (lines - 33 < 4+4*4) {
            drawRow(row5);
        }
        else if (lines - 33 < 4+4*5) {
            drawRow(row6);
        }
        else if (lines - 33 < 4+4*6) {
            drawRow(row7);
        }
        else if (lines - 33 < 4+4*7) {
            drawRow(row8);
        }
    }

    
    lines++;
}

void pulse(bool white) {
    if (white) {
        signalOn;
    }
    else {
        signalOff;
    }
}
void drawRow(bool arr[]) {
    for (int i = 0; i < 16; i++) {
        pulse(arr[i]);
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
        NOP;
    }
    signalOff;
}

void hSync() {
    signalOff;
    delayMicroseconds(1);  // Front porch
    digitalWrite(SYNC, LOW);
    delayMicroseconds(4);  // Horizontal Sync
    digitalWrite(SYNC, HIGH);
    delayMicroseconds(7);  // Back porch
}
void vSync() { //! THIS IS A FAKE PROGRESSIVE SCAN FOR PAL. TESTING SHOWS THIS DOES NOT REALLY WORK FOR NTSC. THIS MAY CAUSE DAMAGE TO AN OLD STYLE CRT BUT THAT MIGHT BE CONJECTURE.
               //TODO: Add support for NTSC.
               //* There are some strange timing issues with this and I'm not sure as to why
    if (lines < 3) {
        signalOff;
        digitalWrite(SYNC, LOW);
        delayMicroseconds(28);
        digitalWrite(SYNC, HIGH);
        delayMicroseconds(4);
        digitalWrite(SYNC, LOW);
        delayMicroseconds(28);
        digitalWrite(SYNC, HIGH);
        lines++;
        return;
    } 
    else if (lines == 3) {
        signalOff;
        digitalWrite(SYNC, LOW);
        delayMicroseconds(27);
        digitalWrite(SYNC, HIGH);
        delayMicroseconds(4);

        digitalWrite(SYNC, LOW);
        delayMicroseconds(2);
        digitalWrite(SYNC, HIGH);
        lines = 4;
        return;
    } 
    else if (lines < 6) {
        signalOff;
        digitalWrite(SYNC, LOW);
        delayMicroseconds(2);
        digitalWrite(SYNC, HIGH);
        delayMicroseconds(29);
        digitalWrite(SYNC, LOW);
        delayMicroseconds(2);
        digitalWrite(SYNC, HIGH);
        lines++;
        return;
    } 
    else if (lines > 309) {
        signalOff;
        digitalWrite(SYNC, LOW);
        delayMicroseconds(2);
        digitalWrite(SYNC, HIGH);
        delayMicroseconds(29);
        digitalWrite(SYNC, LOW);
        delayMicroseconds(2);
        digitalWrite(SYNC, HIGH);
        lines++;
        if (lines >= 313) {
            lines = 0;
        }
        return;
    }
}