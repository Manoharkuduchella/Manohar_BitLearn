#include<Wire.h>
#define SLAVE_ADDRESS 0x40
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Wire1.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  Wire1.beginTransmission(SLAVE_ADDRESS);
  uint8_t error = Wire1.endTransmission(true);
  Serial.printf("endTransission: %u\n",error);


}
