int relojPin = 13;
int almacenamientoPin = 8;
int dataPin = 12;
byte myByte;
//79 (3) 91 (2) 40 (7) 102 (4) 111 (9) 125 (6) 127 (8)
byte numeros[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relojPin, OUTPUT);
  pinMode(almacenamientoPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //  myByte++;
  for (int i = 0; i < 10; i++) {
    digitalWrite(almacenamientoPin, LOW);
    shiftOut(dataPin, relojPin, MSBFIRST, numeros[i]);
    digitalWrite(almacenamientoPin, HIGH);
    delay(1000);
  }
  //digitalWrite(almacenamientoPin,LOW);
  //shiftOut(dataPin,relojPin,MSBFIRST,myByte);
  //digitalWrite(almacenamientoPin,HIGH);
  //Serial.println(myByte);
  //delay(100);
}
