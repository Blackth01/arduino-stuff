int ledPin = 11; // Pin where the LED is connected
int ldrSensorPin = A0; // Pin where the LDR sensor is connected  
int divisorValue = 1000; // If the LDR value is higher than that value, it sends one signal through serial, otherwise, sends another

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); // Defines the LED pin as output
}  

void loop()  
{  
  int sensorValue = analogRead(ldrSensorPin);  // Reads the value from the LDR sensor  

  if (sensorValue > divisorValue)    
  {
    digitalWrite(ledPin, HIGH);
    Serial.print("S");
  }  
  else  
  {
    digitalWrite(ledPin, LOW);
    Serial.print("N");  
  }
  delay(500);
}