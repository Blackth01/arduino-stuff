#include <Ultrasonic.h>

int triggerPin = 3;
int echoPin = 5;

int ledPin = 10;

int ldrSensorPin = A0; // Pin where the LDR sensor is connected  
int ldrDivisorValue = 900; // If the LDR value is higher than that value, it sends one signal through 
int ultrasonicDivisorValue = 100; // If the distance is higher than that value, it sends one signal through serial, otherwise, sends another

float centimeters_distance;
char current_mode;

Ultrasonic ultrasonic(triggerPin, echoPin);
 
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  current_mode = get_current_mode();

  if (current_mode == 'S')
  {
    digitalWrite(ledPin, HIGH);
  }
  else{
    digitalWrite(ledPin, LOW);
  }
  Serial.print(current_mode);  
  delay(500);
}

char get_current_mode(){
  int sensorValue = analogRead(ldrSensorPin);  // Reads the value from the LDR sensor  
  //Serial.println(sensorValue);
  if (sensorValue > ldrDivisorValue)    
  {
    return 'S';
  }

  centimeters_distance = ultrasonic.read();

  if (centimeters_distance > ultrasonicDivisorValue)
  {
    return 'N';
  }
  else
  {
    return 'S';
  }
}
