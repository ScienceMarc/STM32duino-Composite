//#define WIDTH 10
//#define HEIGHT 10

#include "STM32Composite.h"

void setup() {
    VIDEO::begin();  // Sets up the interrupt, must be called first.
}

void loop() {
    VIDEO::clear();
    VIDEO::drawLine(0,0,millis()/100 % VIDEO::width,VIDEO::height,1);
    delay(33);
}