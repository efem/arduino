#include <Ultrasonic.h>
#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3

SoftwareSerial rfid = SoftwareSerial(rxPin, txPin);


int pingPin = 13;
int inPin = 12;
int led = 8;
int buttonPin = 4;
int buttonState = 0;
int ileCM;
const int odleglosc = 30;


void setup() {
    Serial.begin( 9600 );
    pinMode(led, OUTPUT);
    pinMode(buttonPin, INPUT);
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  //odpalCzujnik();
  //ileCM = odpalCzujnik();
  
  if (odpalCzujnik() < odleglosc || buttonState == HIGH) {
    zapal();
  }
  else if (odpalCzujnik() >= odleglosc || buttonState == LOW) 
  {
    zgas();
  }
  
}
int odpalCzujnik()
{
    long duration, inches, cm;
  
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);

  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);

  cm = microsecondsToCentimeters(duration);
  //Serial.print(cm);
  //Serial.print("cm");
  //Serial.println();
  delay(300);
  
  return cm;
}
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
void zapal()
{
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1);
}
void zgas()
{
  digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1);
}
