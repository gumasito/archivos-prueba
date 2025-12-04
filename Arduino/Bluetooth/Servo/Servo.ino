#include <SoftwareSerial.h>
#include <Servo.h>
Servo motor;
SoftwareSerial BT(10, 11);
String entrada = "";
void setup() {
  // put your setup code here, to run once:
  BT.begin(9600);
  motor.attach(6);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BT.available()) {
    char data = BT.read();
    if (data != '\n') {
      entrada += data;
    } else {
      int angulo = entrada.toInt();
      angulo = constrain(angulo, 0, 180);
      motor.write(angulo);
      entrada = "";
    }

  }
}
