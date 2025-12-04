float vout;
float vread = A0;
float analog;
int piverde = 5;
int pinama = 6;
int pinluz = 3; //rojo
void setup(){
  Serial.begin(9600);
  pinMode(vread,INPUT);
  pinMode(pinluz,OUTPUT);
  pinMode(pinama,OUTPUT);
  pinMode(piverde,OUTPUT);
}
void loop(){
  vout = analogRead(vread);
  analog = (vout/4.01);
  Serial.println(analog);
  if (analog <= 85){
    analogWrite(pinluz,analog);
    analogWrite(pinama,LOW);
  }else if (analog <=170){
    analogWrite(pinama,analog);
    analogWrite(piverde,LOW);   
  }else{
    analogWrite(piverde,analog);
  }
}
