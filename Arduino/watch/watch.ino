#include <WiFi.h>
#include "UniversalTelegramBot.h"
#include <WiFiClientSecure.h>
#include "SPIFFS.h"
#include "esp_task_wdt.h"


#define LED1 23
#define WIFI_OK (1<<0)
#define CFG_OK (1<<1)

WiFiClientSecure client;

EventGroupHandle_t events;
TaskHandle_t TareaWifi;
TaskHandle_t TareaTelegram;

UniversalTelegramBot* bot = nullptr;

String telegramToken;
String pass1, ssid1, pass2, ssid2;
String chat_ids[10];
int current_users = 0;

void ConectarWifi(void*pv) {
  xEventGroupWaitBits(
    events,
    CFG_OK,
    false,
    true,
    portMAX_DELAY);
  for (;;) {
    if (WiFi.status() == WL_CONNECTED) {
      xEventGroupSetBits(events, WIFI_OK);
    } else {
      xEventGroupClearBits(events, WIFI_OK);
      ensureWifi();
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
void ConectarTelegram(void* pv) {
  xEventGroupWaitBits(
    events,
    WIFI_OK,
    false,
    true,
    portMAX_DELAY);
  client.setInsecure();
  bot = new UniversalTelegramBot(telegramToken, client);
  bot -> longPoll = 3;
  for (;;) {
    int new_msg = bot->getUpdates(bot->last_message_received + 1);
    while (new_msg) {
      for (int i = 0; i < new_msg; i++) {
        String msg = bot->messages[i].text;
        String sender_id = bot->messages[i].chat_id;
      }
    }
    vTaskDelay(pdMS_TO_TICKS(300));

  }
}
void ensureWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid1.c_str(), pass1.c_str());
    while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(LED1, !digitalRead(LED1));
      vTaskDelay(pdMS_TO_TICKS(500));
    }
    if (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid2.c_str(), pass2.c_str());
      while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(LED1, !digitalRead(LED1));
        vTaskDelay(pdMS_TO_TICKS(500));
      }
    }
  } else {
    return;
  }
}

bool LoadConfig() {
  File file = SPIFFS.open("/config.json", "r");
  if (!file) {
    Serial.println("Error abriendo config.json");
    return false;
  }
  StaticJsonDocument<2048> doc;
  DeserializationError error = deserializeJson(doc, file);
  file.close();
  if (error) {
    Serial.println("Error parseando JSON");
    return false;
  }
  telegramToken = doc["telegram"]["token"].as<String>();
  JsonArray ids = doc["telegram"]["chat_ids"];
  current_users = 0;
  for (String id : ids) {
    chat_ids[current_users++] = id;
  }
  ssid1 = doc["wifi"]["ssid"].as<String>();
  pass1 = doc["wifi"]["pass"].as<String>();
  ssid2 = doc["wifi"]["ssid2"].as<String>();
  pass2 = doc["wifi"]["pass2"].as<String>();
  xEventGroupSetBits(events, CFG_OK);
  return true;
}
void setup() {
  pinMode(LED1, OUTPUT);
  events = xEventGroupCreate();
  if (!SPIFFS.begin(true)) {
    Serial.println("Error al iniciar SPIFFS");
  }
  if (!LoadConfig()) {
    Serial.println("Error cargando LOADCONFIG");
  }
  xTaskCreatePinnedToCore(
    ConectarWifi,
    "Wifi",
    4096,
    NULL,
    1,
    &TareaWifi,
    1);
  xTaskCreatePinnedToCore(
    ConectarTelegram,
    "Telegram",
    10000,
    NULL,
    1,
    &TareaTelegram,
    1);
}

void loop() {
}
