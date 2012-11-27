#include "Ultrasonic.h"

int pingPin = 13;
int inPin = 12;
int led = 8;

void setup() {
Serial.begin( 9600 );
pinMode(led, OUTPUT); 
}

void loop()
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
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1);
  
  if (cm<30) {
    zapal();
  }
  
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
