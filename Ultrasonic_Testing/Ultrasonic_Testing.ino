#include <Ultrasonic.h>
#include <SoftwareSerial.h>
#include <Servo.h> 
 

#define rxPin 2
#define txPin 3

SoftwareSerial RFID = SoftwareSerial(rxPin, txPin);
Servo myservo; 

const int buzzer = 11; //buzzer
const int pingPin = 13; //do czujnika
const int inPin = 12; //do czujnika
const int led = 8; //niebieska dioda
const int ledCZ = 7; //czerwona dioda
const int buttonPin = 4; //przycisk z wewnatrz
const int odleglosc = 30; //odglosc jaka wzbudza uklad rfid (w cm)
const int serwoPin = 10; //pin serwa

int buttonState = 0; //stan przycisku wew.
int ileCM; //odczyt zujnika
int przychodzacyBajt = 0; //przychodzacy bajt
int poyzcja = 0; //pocztakowa pozycja serwa

String msg; //TAG

char c; //zbiera znaki do TAGa



void setup() {
  Serial.begin( 9600 );
  pinMode(led, OUTPUT);
  pinMode(ledCZ, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buzzer, OUTPUT);
  myservo.attach(serwoPin);
  RFID.begin(9600);
  Serial.println("RFID Ready");
  

}

void loop()
{
  buttonState = digitalRead(buttonPin);
  //odpalCzujnik();
  //ileCM = odpalCzujnik();
  RFID.flush();
  wlaczRFID(false); //domylsnym stanem jest wylaczenie odczytu z RFID
  if (odpalCzujnik() < odleglosc)
  {
    wlaczRFID(true); //*********************************************UAKTYWNIKJ PIN OD RFID
    //RFID.flush();
    czytajRFID();  //*********************************************************CZYTAJ RFID
    sprawdzBajt();
  }
  //else if (odpalCzujnik() >= odleglosc)
  //{
  // wlaczRFID(false); //***********************************************WYGAS PIN OD RFID (albo tutaj albo przed ifem na odpalCzujnij, ale testy mowia, ze tutaj lepiej)
  //}

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
  delay(1000);
}
void zgas()
{
  digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1);
}
void wlaczRFID(boolean wlacz) {
  if (wlacz == true) { 
    digitalWrite(txPin, LOW); //enables the RDIF reader and turns on the diode on the arduino
  } 
  else {                               //disables the RDIF reader and turns off the diode on the arduino
    digitalWrite(txPin, HIGH);   
  }
}
void odmowaDostepu()
{
  digitalWrite(ledCZ, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);
  digitalWrite(ledCZ, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1);
  
}

int x=0;
void czytajRFID()
{
x++;
  while(RFID.available()>0)
  {
    c=RFID.read(); 
    msg += c;

    Serial.println(msg);  //przyrastajacy TAG
    Serial.println(msg.length()); //  
    
  }
    Serial.print("X: ");
    Serial.println(x);
  if(msg.length()>10) // DLUGOSVC WIADOMOSCI
  {
    wypisz();
  }
x=0;
}
int z=0;
void wypisz(){ //odpala 3 razy ta funkcje - CZEMU??
  z++;
  msg=msg.substring(1,13);
  Serial.print("TAG:" );
  Serial.println(msg);
  
  Serial.print("Z: ");
  Serial.println(z);
  msg="";
 
  RFID.flush(); //czyszcze bufor
  

}
void sprawdzBajt()
{
  przychodzacyBajt = Serial.read();
  Serial.print("Przychodzacy: ");
  Serial.print(przychodzacyBajt);
  if (przychodzacyBajt == 49)
  {
    Serial.println("########################SEZAMIE OTWORZ SIE!!!#################################");
    zapal();
    buzzAKCEPTACJA();
    otworz();
    RFID.flush(); //czyszcze bufor
  }
  else if (przychodzacyBajt == 48)
  {
    odmowaDostepu();
    buzzODMOWA();
    RFID.flush(); //czyszcze bufor
  }
}
void buzzODMOWA()
{
   for (int i=0; i<=2;i++){
   tone(11, 500, 100);
   delay(200);
   }
   noTone(11);
}
void buzzAKCEPTACJA()
{
   tone(11, 1000, 1000);
   delay(1000);
   noTone(11);
}
void otworz()
{
  myservo.write(pos);              // tell servo to go to position in variable 'pos' 
  delay(5000);
}
