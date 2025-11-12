#include <Stepper.h>
const int pasos = 2048;
Stepper motor(pasos,8,10,9,11);
void setup() {
  // put your setup code here, to run once:
motor.setSpeed(15);
}

void loop() {
  // put your main code here, to run repeatedly:
motor.step(1);
}
