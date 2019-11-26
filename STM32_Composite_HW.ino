//Cheatsheet: http://www.batsocks.co.uk/readme/video_timing.htm

#include <SPI.h>

#define NOP __asm__ __volatile__ ("nop\n\t") //Wait a single clock cycle, this may be pretty useless.

#define SYNC PB8
#define SIGNAL PB9

HardwareTimer timer(1); //Uses hardware timer 1.
                        //! THIS MAY AFFECT ALL PINS WHICH USE THIS TIMER IF YOU TRY TO USE PWM.

volatile int lines = 1;

uint16_t draw = 0xAAAA;
uint16_t draw2 = 0x5555;
uint16_t draw3 = 0xAAAA;
uint16_t draw4 = 0x5555;

void setup() {
    pinMode(SYNC, OUTPUT);
    pinMode(SIGNAL, OUTPUT);
    pinMode(PB12, OUTPUT);

    SPI.begin();


    Serial.begin(9600);

    //This code adds an precise 64µS interrupt which calls line(), this is done to ensure that the lines all take exactly 64µS like they should.
    timer.pause();
    timer.setPeriod(64);
    timer.setChannel1Mode(TIMER_OUTPUT_COMPARE);
    timer.setCompare(TIMER_CH1,1);
    timer.attachCompare1Interrupt(line);
    timer.refresh();
    timer.resume();
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
}

void loop() {
    //draw = millis()/50;
}

void line() {
    vSync();
    hSync();
    if (lines > 33) {
        if (lines > 33 && lines - 33 < 12) {
            draw >>= 1;
            draw <<= 1;
            SPI.transfer(draw >> 8 & 0xFF);
            SPI.transfer(draw & 0xFF);
        } else if (lines - 33 < 24) {
            draw2 >>= 1;
            draw2 <<= 1;
            SPI.transfer(draw2 >> 8 & 0xFF);
            SPI.transfer(draw2 & 0xFF);
        }
        else if (lines - 33 < 24+12) {
            draw3 >>= 1;
            draw3 <<= 1;
            SPI.transfer(draw3 >> 8 & 0xFF);
            SPI.transfer(draw3 & 0xFF);
        }
        else if (lines - 33 < 24+24) {
            draw4 >>= 1;
            draw4 <<= 1;
            SPI.transfer(draw4 >> 8 & 0xFF);
            SPI.transfer(draw4 & 0xFF);
        }
    }

    
    lines++;
}

void hSync() {
    //digitalWrite(SIGNAL, LOW);
    delayMicroseconds(1);  // Front portch
    digitalWrite(SYNC, LOW);
    delayMicroseconds(4);  // Horizontal Sync
    digitalWrite(SYNC, HIGH);
    delayMicroseconds(6);  // Back porch
}
void vSync() { //! THIS IS A FAKE PROGRESSIVE SCAN FOR PAL. TESTING SHOWS THIS DOES NOT REALLY WORK FOR NTSC. THIS MAY CAUSE DAMAGE TO AN OLD STYLE CRT BUT THAT MIGHT BE CONJECTURE.
               //TODO: Add support for NTSC.
               //* There are some strange timing issues with this and I'm not sure as to why
    if (lines < 3) {
        //digitalWrite(SIGNAL, LOW);
        digitalWrite(SYNC, LOW);
        delayMicroseconds(27);
        digitalWrite(SYNC, HIGH);
        delayMicroseconds(4);
        digitalWrite(SYNC, LOW);
        delayMicroseconds(27);
        digitalWrite(SYNC, HIGH);
        lines++;
        return;
    } 
    else if (lines == 3) {
        //digitalWrite(SIGNAL, LOW);
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
        //digitalWrite(SIGNAL, LOW);
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
        //digitalWrite(SIGNAL, LOW);
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