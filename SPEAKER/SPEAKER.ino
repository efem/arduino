int SPEAKER = 8; // Piezo Speaker Pin


void setup() {
 
  Serial.begin(9600); 
 
}

void loop() {
  
  AlarmOn();
}

void AlarmOn(){
  
  tone(SPEAKER, 1000);
  delay(100);
  
  noTone(SPEAKER); 

  delay(100);
  
  
}

