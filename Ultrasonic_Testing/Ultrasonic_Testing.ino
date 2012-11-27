#include <Ultrasonic.h>
#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3

SoftwareSerial RFID = SoftwareSerial(rxPin, txPin);


const int pingPin = 13; //do czujnika
const int inPin = 12; //do czujnika
const int led = 8; //niebieska dioda
const int buttonPin = 4; //przycisk z wewnatrz
const int odleglosc = 30; //odglosc jaka wzbudza uklad rfid (w cm)
int buttonState = 0; //stan przycisku wew.
int ileCM; //odczyt zujnika

String msg; //TAG

char c; //zbiera znaki do TAGa



void setup() {
    Serial.begin( 9600 );
    pinMode(led, OUTPUT);
    pinMode(buttonPin, INPUT);
    RFID.begin(9600);
    Serial.println("RFID Ready");
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  //odpalCzujnik();
  //ileCM = odpalCzujnik();
  
  if (odpalCzujnik() < odleglosc)
  {
     wlaczRFID(true); //*********************************************UAKTYWNIKJ PIN OD RFID
     RFID.flush();
     czytajRFID();  //*********************************************************CZYTAJ RFID
  }
  else if (odpalCzujnik() >= odleglosc)
  {
      wlaczRFID(false); //***********************************************WYGAS PIN OD RFID
  }
  
  if (buttonState == HIGH)
  {
      zapal();
  } 
  else if (buttonState == LOW)
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
  //Serial.print("cm");
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
void wlaczRFID(boolean wlacz) {
  if (wlacz == true) { 
    digitalWrite(txPin, LOW); //enables the RDIF reader and turns on the diode on the arduino
  } else {                               //disables the RDIF reader and turns off the diode on the arduino
    digitalWrite(txPin, HIGH);   
  }
}
void czytajRFID()
{
  
  while(RFID.available()>0)
         {
            c=RFID.read(); 
            msg += c;
   
            Serial.println(msg);  //przyrastajacy TAG
            Serial.println(msg.length()); //      
          }
    
    if(msg.length()>10) // DLUGOSVC WIADOMOSCI
    {
      wypisz();
    }
}
void wypisz(){
    msg=msg.substring(1,13);
    Serial.print("TAG:" );
    Serial.println(msg);
    RFID.flush(); //czyszcze bufor

}
  
  
