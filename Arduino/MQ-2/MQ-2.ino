int buzz = #pin;
int Pinsensor = #pinSensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzz,OUTPUT);
  pinMode(Pinsensor,INPUT);
  digitalWrite(buzz,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensor = analogRead(Pinsensor);
  if (sensor >= 500){
    digitalWrite(buzz,HIGH);
  }else{
    digitalWrite(buzz,LOW);
  }
}
