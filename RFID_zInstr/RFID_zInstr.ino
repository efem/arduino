#include <SoftwareSerial.h>
#define rxPin 2
#define txPin 3
SoftwareSerial RFID(rxPin, txPin);
int led = 8;
int buttonPin = 4; 
String msg="";
void setup()  
{
  Serial.begin(9600);
  Serial.println("Serial OK");
  RFID.begin(9600);
  Serial.println("RFID OK");
  pinMode(led, OUTPUT);
  pinMode(buttonPin, INPUT);
}
char c;
int incomingByte = 0;
int buttonState = 0;
void loop(){
  //msg="";
  buttonState = digitalRead(buttonPin);
  while(RFID.available()>0)
  {
    c=RFID.read(); 
    msg += c;
 
    Serial.println(msg);  //przyrastajacy TAG
    Serial.println(msg.length()); //
    //Serial.println("a");
  }
  if(msg.length()>10)
  {
    wypisz();
  }
 if (Serial.available() > 0 || buttonState == HIGH) 
   {
             // read the incoming byte:
    incomingByte = Serial.read();
    if (incomingByte==49 || buttonState == HIGH)
    {
      Serial.print("AUA!");
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(3000);               // wait for a second
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
      delay(1);   
    }
                // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  // dac odczekanie 5 sekund
   }
  msg="";
}
void wypisz(){
    msg=msg.substring(1,13);
    Serial.print("TAG:" );
    Serial.println(msg);
    //digitalWrite(txPin, LOW); //wylaczam pin, zeby nie czytao ciagle
    //digitalWrite(255, HIGH);
    //delay(5000); //czas na otwarcie zamka - zakomentowane zeby nie bylo w tym miejscu LAGa
    RFID.flush(); //czyszcze bufor, czy co bo kurwa dokumentacji brak do tego, albo ja ulomny
    //digitalWrite(txPin, HIGH); //odpalam pin
    //digitalWrite(255, LOW);
}
