int latchPin = 8;
int clockPin = 13;
int dataPin = 12;
byte myByte = 0b10000000;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  myByte = (myByte >> 1)| (myByte << 7);
  digitalWrite(latchPin, LOW);            // preparar para enviar datos
  shiftOut(dataPin, clockPin, MSBFIRST, myByte); // enviar los bits
  digitalWrite(latchPin, HIGH);           // mostrar en salidas
  Serial.println(myByte);
  delay(600);
  }
