#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient client;
PubSubClient mqttClient(client);

const char* ssid = "";
const chat* pass = "";

char* server = "";
int port = "";

int ledPin = ;
int sensor = ;

int var = ;
int ledVal = ;
int sensorVal = ;
char datos[40];
String resultados = "";


void Wifi() {
  WiFi.begin(ssid, passw);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("Conexion Exitosa");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
}

void callback(char* topic,byte* payload,unsigned int length){
  Serial.println("Mensaje Recibido: [");
  Serial.print(topic);
  Serial.print("] ");
  char payload_string [length + 1];
  int resultado;
  memcpy(payload_string, payload, length);
  payload_string[length] = '\0';
  resultado = atoi(payload_string);

  var = resultado;

  resultados = "";
  for (int i = 0; i<length;i++){
    resultados = resultados + char(payload[i]);
  }
  Serial.println();
  
}

void reconnect() {
  while (!mqttClient.connected()) {
    Serial.println("Intentando conectarse a mqtt");
    if (mqttClient.connect("arduinoClient")) {
      Serial.println("Conectado");
      mqttClient.subscribe("Entrada/01");
    } else {
      Serial.print("Falló, rc=");
      Serial.print(mqttClient.state());
      Serial.println("Intentar de nuevo en un momento");
      delay(1000);
    }
  }
}
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(sensor, INPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(115200);
  Wifi();
  mqttClient.setServer(server, port)
  mqttClient.setCallback(callback);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
  Serial.print("String: ");
  Serial.println(resultados);

  if (var == 0) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
  }
  sensorVal = analogRead(sensor);
  Serial.println(sensorVal);
}
