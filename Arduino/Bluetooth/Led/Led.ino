#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BT.available()) {
    char dato = BT.read();
    Serial.println(dato);
    if (dato == '0') {
      digitalWrite(2, LOW);
    }
    else if (dato == '1') {
      digitalWrite(2, HIGH);
    }
  }
}
