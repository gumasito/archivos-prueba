int bot = 2;
int luz = 6;
int viejo = 0;
int nuevo;
int state = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(luz, OUTPUT);
  pinMode(bot, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  nuevo = digitalRead(bot);
  delay(100);
  if (nuevo == 0 && viejo == 1) {
    if (state == 0) {
      digitalWrite(luz, HIGH);
      state = 1;
    } else {
      digitalWrite(luz, LOW);
      state = 0;
    }
  }
  viejo = nuevo;
}
