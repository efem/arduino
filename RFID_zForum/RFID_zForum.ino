SoftwareSerial mySerial= SoftwareSerial(rxPin, txPin);

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  }
  
  void loop()
  {
    for (int i=0;i<=13;i++){
      Serial.print(mySerial.read(),BYTE);
      }
      Serial.println("   <<Card ID");
      delay(1000);
      }

