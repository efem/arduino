void setup() {
    pinMode(11, OUTPUT);
      for (int i=0; i<=2;i++){
      tone(11, 1000, 100);
      
      delay(200);
    }
    noTone(11);
}

void loop() {

}
