#include <SoftwareSerial.h>
#define rxPin 2
#define txPin 3
SoftwareSerial RFID(rxPin, txPin);
String msg="";
void setup()  
{
  Serial.begin(9600);
  Serial.println("Serial OK");
  RFID.begin(9600);
  Serial.println("RFID OK");
}
char c;
void loop(){
  //msg="";
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
  msg="";
}
void wypisz(){
    msg=msg.substring(1,13);
    Serial.print("TAG:" );
    Serial.println(msg);
    digitalWrite(txPin, LOW); //wylaczam pin, zeby nie czytao ciagle
    //digitalWrite(255, HIGH);
    delay(5000); //czas na otwarcie zamka
    RFID.flush(); //czyszcze bufor, czy co bo kurwa dokumentacji brak do tego, albo ja ulomny
    digitalWrite(txPin, HIGH); //odpalam pin
    //digitalWrite(255, LOW);
}
