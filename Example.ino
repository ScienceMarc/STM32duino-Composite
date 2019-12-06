#include "STM32Composite.h"

const uint8_t PROGMEM bmp[] = {0,0,0,0,0,0,0,0,
                               0,0,0,0,0,0,0,0,
                               0,0,1,0,0,1,0,0,
                               0,0,0,0,0,0,0,0,
                               0,1,0,0,0,0,1,0,
                               0,0,1,1,1,1,0,0,
                               0,0,0,0,0,0,0,0,
                               0,0,0,0,0,0,0,0};

void setup() {
    VIDEO::begin();  // Sets up the interrupt, must be called first.
    VIDEO::drawBMP(0,10,8,8,bmp);
    VIDEO::setCursor(0,50);
    VIDEO::print("Hello, World!");
}
void loop() { }