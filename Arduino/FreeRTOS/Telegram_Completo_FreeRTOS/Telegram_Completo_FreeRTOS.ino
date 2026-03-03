//=================== AVISO ===================
//=================== ESTE CODIGO NO ES %100 OPTIMO ===================
//=================== PERO ES UTIL PARA PRACTICAR ===================
#include <WiFi.h>
#include <WebServer.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "SPIFFS.h"

// =================== CONFIG ===================
#define LED1 23
#define MAX_USERS 10

// =================== FREERTOS =================
TaskHandle_t LogicTaskHandle;

// =================== FLAGS ====================
volatile bool activarLed1 = false;
volatile bool enviarMsgLed1 = false;

// =================== ESTADO ===================
bool estadoLed1 = false;

// =================== TELEGRAM =================
String telegramToken;
String msg = "";
String sender_id = "";
String chat_ids[MAX_USERS];
int current_users = 0;
unsigned long lastCheck = 0;

// =================== WIFI =====================
String ssid1, pass1, ssid2, pass2;

// =================== OBJETOS ==================
WiFiClientSecure client;
UniversalTelegramBot* bot = nullptr;
WebServer server(80);

// =================================================
// =================== CONFIG ======================
// =================================================
bool LoadConfig() {
  File file = SPIFFS.open("/config.json", "r");
  if (!file) return false;

  StaticJsonDocument<2048> doc;
  if (deserializeJson(doc, file)) {
    file.close();
    return false;
  }
  file.close();

  telegramToken = doc["telegram"]["token"].as<String>();
  JsonArray ids = doc["telegram"]["chat_ids"];
  current_users = 0;
  for (JsonVariant id : ids) {
    chat_ids[current_users++] = id.as<String>();
  }

  ssid1 = doc["wifi"]["ssid"].as<String>();
  pass1 = doc["wifi"]["pass"].as<String>();
  ssid2 = doc["wifi"]["ssid2"].as<String>();
  pass2 = doc["wifi"]["pass2"].as<String>();
  return true;
}

// =================================================
// =================== WIFI ========================
// =================================================
void conectarWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Conexion Exitosa");
    return;
  }
  WiFi.begin(ssid1.c_str(), pass1.c_str());
  uint32_t t0 = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t0 < 15000) {
    delay(300);
    Serial.println("Intentando conectar a Red 1");
  }

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid2.c_str(), pass2.c_str());
    t0 = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - t0 < 15000) {
      delay(300);
      Serial.println("Intentando conectar a Red 2");
    }
    WiFi.reconnect();
  }
}

// =================================================
// ================= TELEGRAM ======================
// =================================================
void initTelegram() {
  if (bot != nullptr) return;
  if (WiFi.status() != WL_CONNECTED) return;
  if (!telegramToken.length()) return;

  client.setInsecure();
  bot = new UniversalTelegramBot(telegramToken, client);
  bot->longPoll = 3;
}

void manejarTelegram() {
  if (!bot) return;
  if (millis() - lastCheck < 3000) return;

  lastCheck = millis();
  int n = bot->getUpdates(bot->last_message_received + 1);

  while (n) {
    for (int i = 0; i < n; i++) {
      msg = bot->messages[i].text;
      sender_id = bot->messages[i].chat_id;
      Serial.println(msg + "\n");
      Serial.print("de ");
      Serial.println(sender_id);
      if (msg == "/led1") {
        activarLed1 = true;
      }

      if (enviarMsgLed1) {
        bot->sendMessage(sender_id, estadoLed1 ? "Luz encendida" : "Luz apagada");
      }
      enviarMsgLed1 = false;
    }
    n = bot->getUpdates(bot->last_message_received + 1);
  }
}

// =================================================
// ================== LOGICA =======================
// =================================================
void TaskLogic(void* parameter) {
  for (;;) {
    if (activarLed1) {
      estadoLed1 = !estadoLed1;
      digitalWrite(LED1, estadoLed1 ? HIGH : LOW);
      enviarMsgLed1 = true;
      activarLed1 = false;
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
void ManejarRoot() {
  File file = SPIFFS.open("/index.html", "r");
  if (!file) {
    server.send(404, "text/plain", "Error abriendo index.html");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}
void ManejarEstado(){
  StaticJsonDocument<200> doc;
  //doc["general"] = estadoGeneral() ? "Estan todas encendidas" : "Estan todas apagadas";
  doc["uno"] = estadoLed1 ? "Led 1 ON": "Led 1 OFF";
  String output;
  serializeJson(doc,output);
  server.send(200,"application/json",output);
}
void ManejarLed(int num) {
  if (num == 1) {
    estadoLed1 = !estadoLed1;
    digitalWrite(LED1, estadoLed1 ? HIGH : LOW);
    server.send(200,"text/plain",estadoLed1 ? "Led 1 ON" : "Led 1 OFF");
  }
}
void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW);

  if (!SPIFFS.begin(true)) {
    Serial.println("Error al cargar SPIFFS");
  }
  if (!LoadConfig()) {
    Serial.println("Error al parsear JSON");
  }
  WiFi.mode(WIFI_STA);
  server.on("/", ManejarRoot);
  server.on("/uno",[](){
    ManejarLed(1);
  });
  server.on("/estado",ManejarEstado);
  server.begin();

  xTaskCreatePinnedToCore(
    TaskLogic,
    "Logic",
    4096,
    NULL,
    1,
    &LogicTaskHandle,
    1
  );
}

// =================================================
// ================== LOOP =========================
// =================================================
void loop() {
  conectarWiFi();
  initTelegram();
  manejarTelegram();
  server.handleClient();
  delay(10);
}
