#define TOUCH_PIN 4
#define TOUCH_THRE 500

int touchvalue;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  touchvalue = touchRead(TOUCH_PIN);
  if(touchvalue < TOUCH_THRE)
  {
    Serial.print("Touched: ");Serial.println(touchvalue);
  }
  else
  {
    Serial.println("Not Touched");
  }
  delay(500);

}
