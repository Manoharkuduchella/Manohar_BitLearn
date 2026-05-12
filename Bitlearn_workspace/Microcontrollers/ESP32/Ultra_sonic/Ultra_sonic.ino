#include<HCSR04.h>
const byte triggerPin = 13;
const byte echoPin = 12;

UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float distance = distanceSensor.measureDistanceCm();
  Serial.println(distance);
  delay(500);
}
