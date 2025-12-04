int but = 2;
int val;
int pin = 6;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
  pinMode(but, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(but);
  Serial.println(val);
  delay(10);
  if (val == 0) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
}
