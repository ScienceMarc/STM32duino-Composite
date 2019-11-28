//#define WIDTH 10
//#define HEIGHT 10

#include "STM32Composite.h"

void setup() {
    VIDEO::begin();  // Sets up the interrupt, must be called first.
    VIDEO::drawTrig(10,0,0,10,20,10,WHITE);
    //VIDEO::drawLine(10,0,0,10,WHITE);
}

void loop() {/*
    VIDEO::clear();
    VIDEO::drawLine(50, 0, millis() / 100 % VIDEO::width, VIDEO::height, WHITE);
    delay(16);*/
}