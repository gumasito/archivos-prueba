#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoOTA.h>
#include <DHT.h>

const char* ssid = "Sobrero Wifi";
const char* passw = "mis03hijos";
const char* botToken = "7579691226:AAEq-6KBvV-_2bwQVhWmM-yC7NLBr0NxaME";
const String chat_id = "7848546381";

int pin1 = 33;
int pin2 = 32;
int buzz = 27;
int trig = 25;
int echo = 26;
int dur;

#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
unsigned long lastCheck = 0;
unsigned long tiempoSensor = 0;
int intervaloSensor = 200;

bool puertaAbierta = false;
int data;
WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);
void setup() {
  dht.begin();
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(buzz, OUTPUT);
  Serial.begin(115200);
  client.setInsecure();
  WiFi.begin(ssid, passw);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conexion Exitosa");
  bot.sendMessage(chat_id, "Intento 2", "");
  ArduinoOTA.setHostname("ESP32-Telegram");
  ArduinoOTA.begin();
}

void loop() {
  Serial.println("Loop");
  ArduinoOTA.handle();
  if (millis() - tiempoSensor > intervaloSensor) {
    tiempoSensor = millis();
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    dur = pulseIn(echo, HIGH, 5000);
    data = dur * 0.034 / 2;
    Serial.println(data);
    if (data > 0 && data <= 10 && !puertaAbierta) {
      bot.sendMessage(chat_id, "Puerta Abierta!!", "");
      digitalWrite(pin1, HIGH);
      digitalWrite(buzz, HIGH);
      digitalWrite(pin2, LOW);
      puertaAbierta = true;
    } else if (data > 10 && puertaAbierta) {
      bot.sendMessage(chat_id, "Puerta Cerrada", "");
      puertaAbierta = false;
      digitalWrite(pin2, HIGH);
      digitalWrite(buzz, LOW);
      digitalWrite(pin1, LOW);
    }
  }
  if (millis() - lastCheck > 1000)
  {
    int newMsg = bot.getUpdates(bot.last_message_received + 1);
    while (newMsg) {
      for (int i = 0; i < newMsg; i++) {
        String msg = bot.messages[i].text;
        Serial.println("Mensaje Recibido" + msg);
        if (msg == "/tem") {
          float temp = dht.readTemperature();
          if (isnan(temp)) {
            bot.sendMessage(chat_id, "Error al leer la temperatura", "");
          } else {
            String temperatura_res = "La temperatura en la habitacion es de " + String(temp);
            bot.sendMessage(chat_id, temperatura_res, "");
          }
        } else if (msg == "/hum") {
          float hum = dht.readHumidity();
          if (isnan(hum)) {
            bot.sendMessage(chat_id, "Error al leer la humedad", "");
          } else {
            String humedad_res = "La humedad en la habitacion es de " + String(hum);
            bot.sendMessage(chat_id, humedad_res, "");
          }
        }
        else if (msg == "/help") {
          bot.sendMessage(chat_id, "Lista de comandos '/tem'-'/hum'", "");
        }
        else {
          bot.sendMessage(chat_id, "Sure??", "");
        }
      }
      newMsg = bot.getUpdates(bot.last_message_received + 1);
      lastCheck = millis();
    } 
  }
}
