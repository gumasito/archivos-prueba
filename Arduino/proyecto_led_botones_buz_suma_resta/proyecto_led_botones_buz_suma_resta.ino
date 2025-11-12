int pin = 9;
int suma = 2;
int resta = 4;
int buzz = 6;
int brillo = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pin, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(suma, INPUT_PULLUP);
  pinMode(resta, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(suma) == LOW) {
    brillo += 10;
    if (brillo > 255) brillo = 255;
    analogWrite(pin,brillo);
    delay(200);
  }
  if (brillo >= 255 || brillo == 0){
    digitalWrite(buzz,HIGH);
  }else{
    digitalWrite(buzz,LOW);
  }
  if (digitalRead(resta) == LOW){
    brillo-=10;
    if (brillo < 0) brillo = 0;
    analogWrite(pin,brillo);
    delay(200);
  }
}
//void suma(){
//  int viejo = 1;
//  int nuevo;
//  int estado = 0;
//  nuevo = digitalRead(suma);
//  if (nuevo == 0 && viejo == 1){
//    if (estado == 0){
//      digitalWrite(pin,HIGH);
//      estado = 1;
//    }else{
//      digitalWrite(pin,LOW);
//      estado = 0;
//    }
//
//  }
//  viejo = nuevo;
//}
