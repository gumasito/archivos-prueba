int quest;
int pin1 = 8;
int pin2 = 9;
int pin3 = 10;
int dt = 1000;
void setup() {
  // put your setup code here, to run once:
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Elija un valor (8-10)");
  quest = Serial.parseInt();
  while (Serial.available() == 0){
    
  }
  if (quest == 8){
    digitalWrite(pin1,HIGH);
    delay(dt);
    digitalWrite(pin1,LOW);
  }else if (quest == 9){
    digitalWrite(pin2,HIGH);
    delay(dt);
    digitalWrite(pin2,LOW);    
  }else if (quest == 10){
    digitalWrite(pin3,HIGH);
    delay(dt);
    digitalWrite(pin3,LOW);
  }else{
    Serial.println("Elija un pin valido");
  }
}
