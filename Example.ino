//#define WIDTH 10
//#define HEIGHT 10

#include "STM32Composite.h"

void setup() {
    VIDEO::begin();  // Sets up the interrupt, must be called first.
    
}

void loop() {
    VIDEO::clear();
    VIDEO::drawCircle(VIDEO::width/2, VIDEO::height/2, (millis()/1000)%VIDEO::width/2, WHITE);
    delay(33);
}