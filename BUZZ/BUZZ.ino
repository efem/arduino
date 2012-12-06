int piezoPin = 9;

void setup() {
pinMode(piezoPin, OUTPUT);
}

void loop() {

digitalWrite(piezoPin, HIGH);
delayMicroseconds(600);
digitalWrite(piezoPin, LOW);
delayMicroseconds(600);
}
