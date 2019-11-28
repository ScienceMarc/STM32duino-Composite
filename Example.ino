//#define WIDTH 10
//#define HEIGHT 10

#include "STM32Composite.h"

void setup() {
    VIDEO::begin();  // Sets up the interrupt, must be called first.
    
    for (int i = 0; i < VIDEO::width; i++) {
        VIDEO::putPixel(i,i,1);
    }
    
    VIDEO::drawFastHLine(0,0,50,1);
    VIDEO::drawFastVLine(0,0,50,1);
}

void loop() {}