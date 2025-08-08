#include <Stepper.h>

const int steps = 2048;

Stepper myStepper(steps,11,9,10,8);

void setup() 
{
  myStepper.setSpeed(15);
  Serial.begin(115200);
}

void loop() 
{
  Serial.println("시계방향");
  myStepper.step(steps);
  delay(500);
  Serial.println("시계반대방향");
  myStepper.step(-steps);
  delay(500);
}