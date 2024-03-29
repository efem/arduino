#include <SoftwareSerial.h>
#include <Ultrasonic.h>

#define rxPin 2
#define txPin 3
SoftwareSerial RFID(rxPin, txPin);


int led = 8;
int buttonPin = 4; 
int pingPin = 13;
int inPin = 12;
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
  buttonState = digitalRead(buttonPin); //ZMIENNA DO PRZYCISKU Z WEWNATRZ
  long duration, inches, cm; //ZMIENNE DO CZUJNIKA
  //
  
  //**************************************************************************URUCHOMIENIE CZUJNIKA
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
  delay(500); //ODCZYT CO 1/2 SEKUNDY
  if (cm < 20)//**************************************************************************SPRAWDZENIE ODLEGLOSCI OD CZUJNIKA
  {  
    
    while(RFID.available()>0)
    {
      
      c=RFID.read(); 
      msg += c;
   
      Serial.println(msg);  //przyrastajacy TAG
      Serial.println(msg.length()); //
      //Serial.println("a");
    }
    
    if(msg.length()>10) // DLUGOSVC WIADOMOSCI
    {
      wypisz();
    }
    
    
    if (Serial.available() > 0)
    {
    incomingByte = Serial.read(); // SPRAWDZAMY BAJT
    Serial.print (incomingByte);
    if (incomingByte==49) // JESLI 1 = 49 ASCII LUB PRZYCISK WCISNIETY TO OTWORZ DRZWI
      {
      odpal();
      } 
  
    msg="";
    }
  if (buttonState == HIGH) //************ SPRAWDZ CZY WCISNIETY PRZYCISK
  {
    odpal();
  }

}
}

void wypisz(){
    msg=msg.substring(1,13);
    Serial.print("TAG:" );
    Serial.println(msg);
    //digitalWrite(txPin, LOW); //wylaczam pin, zeby nie czytao ciagle
    //digitalWrite(255, HIGH);
    //delay(5000); //czas na otwarcie zamka - zakomentowane zeby nie bylo w tym miejscu LAGa
    RFID.flush(); //czyszcze bufor
    //digitalWrite(txPin, HIGH); //odpalam pin
    //digitalWrite(255, LOW);
}

long microsecondsToCentimeters(long microseconds) //ZAMIANA MIKROSEKUND ODPOWIEDZI NA CENTRYMETRY ODLEGLOSCI
{
  return microseconds / 29 / 2;
}
void odpal()
{
Serial.print("ODPAL!");  
 
      
        Serial.println("AUA!");
        digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(3000);               // wait for a second
        digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
        delay(1);   
        RFID.flush();
                  // say what you got:
      //Serial.print("I received: ");
      //Serial.println(incomingByte, DEC);
      // dac odczekanie 5 sekund
  
}
