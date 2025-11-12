int latchPin = 8;
int clockPin = 13;
int dataPin = 12;
byte myByte;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  myByte++;

  digitalWrite(latchPin, LOW);            // preparar para enviar datos
  shiftOut(dataPin, clockPin, MSBFIRST, myByte); // enviar los bits
  digitalWrite(latchPin, HIGH);           // mostrar en salidas
  Serial.println(myByte);
  delay(1400);
  }
