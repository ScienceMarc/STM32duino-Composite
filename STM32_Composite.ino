void setup() {    
    VIDEO::begin(); //Sets up the interrupt, must be called first.

    for (int i = 0; i < VIDEO::WIDTH; i++) {
        VIDEO::putPixel(i,i,1);
    }
    
}

void loop() {
    
}