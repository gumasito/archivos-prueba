int agua = A0;
int valor;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(agua, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  valor = analogRead(agua);
  Serial.println(valor);
  delay(1
  
  00);
}
