#include <Servo.h>
int servo = 6;
int data;
Servo myServo;
void setup() {
  // put your setup code here, to run once:
  myServo.attach(servo);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Ingrese el valor de movimiento (0-180)");
  while (Serial.available() == 0) {
  }
  data = Serial.parseInt();
  if (data > 180)data = 180;
    Serial.println("WRONGGGG");
  myServo.write(data);
  while (Serial.available() > 0){
    Serial.read();
  }
}
