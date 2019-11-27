//Cheatsheet: http://www.batsocks.co.uk/readme/video_timing.htm

#define NOP __asm__ __volatile__ ("nop\n\t")

#define signalOn GPIOB->regs->BSRR = 0b0000001000000000
#define signalOff GPIOB->regs->BRR = 0b0000001000000000

#define syncOn GPIOB->regs->BSRR =   0b0000000100000000
#define syncOff GPIOB->regs->BRR =   0b0000000100000000

#define SYNC PB8
#define SIGNAL PB9

HardwareTimer timer(1); //Uses hardware timer 1.
                        //! THIS MAY AFFECT ALL PINS WHICH USE THIS TIMER IF YOU TRY TO USE PWM.

volatile int lines = 1;

const int HEIGHT = 64;
const int WIDTH = 64;
bool matrix[HEIGHT][WIDTH];

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

    for (int i = 0; i < WIDTH; i++) {
        putPixel(i,i,1);
    }
    
}

void loop() {
    
}

void line() {
    vSync();
    hSync();
    if (lines > 33) {
        drawRow(matrix[min(HEIGHT-1,(lines-33)/3)]);
    }

    
    lines++;
}

void pulse(bool white) { //Either sends a pulse or turns it off based on the color of the pixel
    if (white) {
        signalOn;
    }
    else {
        signalOff;
    }
}
void drawRow(bool arr[]) { //Draws a row from the matrix to the screen
    for (int i = 0; i < WIDTH; i++) {
        pulse(arr[i]);
        //* These NOPs are to create a bit of delay because otherwise the pixels are too small and are a little fuzzy because the signal did not have time to rise.
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
void putPixel(uint16_t x, uint16_t y, bool on) { //TODO: come up with a better name for the "on" parameter
    matrix[x][y] = on;
}


void hSync() {
    signalOff;
    delayMicroseconds(1);  // Front porch
    syncOff;
    delayMicroseconds(4);  // Horizontal Sync
    syncOn;
    delayMicroseconds(7);  // Back porch
}
void vSync() { //! THIS IS A FAKE PROGRESSIVE SCAN FOR PAL. TESTING SHOWS THIS DOES NOT REALLY WORK FOR NTSC. THIS MAY CAUSE DAMAGE TO AN OLD STYLE CRT BUT THAT MIGHT BE CONJECTURE.
               //TODO: Add support for NTSC.
               //* There are some strange timing issues with this and I'm not sure as to why
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
    } 
    else if (lines == 3) {
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
    } 
    else if (lines < 6) {
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
    } 
    else if (lines > 309) {
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