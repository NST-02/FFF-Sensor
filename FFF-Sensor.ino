#include "DHT.h"

#define dhtPin 2
#define flamePin 5
#define ledPin 11
#define buzzerPin 12

#define dhtType DHT11 

unsigned long flameStart, flameFinish, flameDuration, flameDurationS;
int criticPoint = 5000, flameData;

DHT dht(dhtPin, dhtType);

void setup() 
{   
  Serial.begin(9600);
  dht.begin();

  pinMode(flamePin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void sendData (long data)
{
    Serial.print("Duration = ");
    Serial.print(data);
    Serial.print(" - ");
    Serial.print("Temperature = ");
    Serial.print(dht.readTemperature());
    Serial.print("C");
    Serial.println(" ");
}

void Alarm()
{
  for(int i; i < 11; i++)
  {
      digitalWrite(ledPin, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);
      delay(100);
  }
}

void loop() 
{
    flameData = digitalRead(flamePin);

    if(flameData == LOW)
    {
        flameStart = millis();
        delay(criticPoint); 

        repeat:
        
        if(flameData == LOW)
        {
          flameFinish = millis();
          flameDuration = flameFinish - flameStart; 
          flameDurationS = flameDuration / 1000;
          sendData(flameDurationS);
          delay(1000);
          
          Alarm(); 
          
          goto repeat;
       } 
    }
}
