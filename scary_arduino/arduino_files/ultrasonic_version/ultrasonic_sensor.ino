#include <Ultrasonic.h>

int triggerPin = 3;
int echoPin = 5;
int ledPin = 10;
int divisorValue = 100; // If the distance is higher than that value, it sends one signal through serial, otherwise, sends another
float centimeters_distance;

Ultrasonic ultrasonic(triggerPin, echoPin);
 
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  centimeters_distance = ultrasonic.read();
  //Serial.print("Distance in centimeters: ");
  //Serial.println(centimeters_distance);
  if (centimeters_distance > divisorValue)
  {
    digitalWrite(ledPin, LOW);
    Serial.print("N");
  }
  else
  {
    digitalWrite(ledPin, HIGH);
    Serial.print("S");
  }
  delay(500);
}