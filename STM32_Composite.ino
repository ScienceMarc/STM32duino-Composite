void setup() {
    

    Serial.begin(9600);

    VIDEO::begin();
    

    for (int i = 0; i < VIDEO::WIDTH; i++) {
        VIDEO::putPixel(i,i,1);
    }
    
}

void loop() {
    
}