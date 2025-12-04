int trig = 9;
int eco = 8;
int data;
int dur;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(eco, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  dur = pulseIn(eco, HIGH);

  // Calcular distancia en cm
  data = dur * 0.034 / 2;
  Serial.println(data);
  delay(100);
}
