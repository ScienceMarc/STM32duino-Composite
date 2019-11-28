//#define WIDTH 10
//#define HEIGHT 10

#include "STM32Composite.h"

void setup() {
    VIDEO::begin();  // Sets up the interrupt, must be called first.

    VIDEO::drawRect(0,0,10,10,1);
}

void loop() {/*
    for (int i = 0; i < VIDEO::width; i++) {
        VIDEO::putPixel(i,i,1);
        delay(50);
    }
    for (int i = 0; i < VIDEO::width; i++) {
        VIDEO::putPixel(i,i,0);
        delay(50);
    }*/
}