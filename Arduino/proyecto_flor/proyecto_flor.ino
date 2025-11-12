#include <Servo.h>
Servo motor;
int motorPin = 7;
int luz = 6;
int Xpin = A0;
int Ypin = A5;
int xVal;
int valorpin;
int datosmotor;
int datosviejos;
int estado = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(Xpin, INPUT);
  pinMode(luz, OUTPUT);
  motor.attach(motorPin);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  xVal = analogRead(Xpin);
  datosmotor = map(xVal, 0, 1023, 0, 180);
  Serial.println(datosmotor);
  //  if (datosmotor < 91) datosmotor = 91; Para que no baje
  if (datosmotor == 180 && datosviejos == 180) {
    if (estado == 0) {
      motor.write(180);
      estado = 1;
      if (true){
        for (int i = 0; i <256; i++){
          analogWrite(luz,i);
          delay(20); 
        }
      }
    }
  }
  else if (datosmotor == 0 && datosviejos == 0) {
    if (estado == 1) {
      motor.write(0);
      estado = 0;
      if(true){
        for (int i = 255; i > 0; i--){
          analogWrite(luz,i);
          delay(20);
        }
      }
    }
  }
  datosviejos = datosmotor;
  delay(200);
}
