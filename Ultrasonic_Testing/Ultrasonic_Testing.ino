#include "Ultrasonic.h"

int pingPin = 13;
int inPin = 12;
int led = 8;
int buttonPin = 4;
int buttonState = 0;
int ileCM;
void setup() {
    Serial.begin( 9600 );
    pinMode(led, OUTPUT);
    pinMode(buttonPin, INPUT);
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  //odpalCzujnik();
  ileCM = odpalCzujnik();
  
  if (ileCM < 30 || buttonState == HIGH) {
    zapal();
  }
  else if (ileCM >= 30 || buttonState == LOW) 
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
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
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
