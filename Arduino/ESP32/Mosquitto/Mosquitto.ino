#include <WiFi.h>
#include <PubSubClient.h>

#define LED_PIN 23
#define LED2_PIN 22
const char* ssid = "******";
const char* pass = "******";

const char* mqtt_server = "********"; //192.168.100.149 Home Assistant 192.168.100.85 PC
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  Serial.print("Conectando WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("IP ESP32: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) msg += (char)payload[i];

  Serial.print("Topic: ");
  Serial.print(topic);
  Serial.print(" | Msg: ");
  Serial.println(msg);

  if (String(topic) == "prueba/led/cmd") {
    if (msg == "ON") {
      digitalWrite(LED_PIN, HIGH);
      client.publish("prueba/led/state", "ON", true);
    }
    if (msg == "OFF") {
      digitalWrite(LED_PIN, LOW);
      client.publish("prueba/led/state", "OFF", true);
    }
  } else if (String(topic) == "prueba/led2/cmd") {
    if (msg == "ON") {
      digitalWrite(LED2_PIN, HIGH);
      client.publish("prueba/led2/state", "ON", true);
    }
    if (msg == "OFF") {
      digitalWrite(LED2_PIN, LOW);
      client.publish("prueba/led2/state", "OFF", true);
    }
  } else if (String(topic) == "prueba/todo/cmd") {
    if (msg == "ON") {
      digitalWrite(LED2_PIN, HIGH);
      digitalWrite(LED_PIN, HIGH);
      client.publish("prueba/todo/state", "ON", true);
    } else if (msg == "OFF") {
      digitalWrite(LED2_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
      client.publish("prueba/todo/state", "OFF", true);
    }
  }
}

void connectMQTT() {
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.print("Conectando MQTT...");
    if (client.connect("ESP32_LED","gumasito","Lauralp21.love/22")) {
      Serial.println("OK");
      client.subscribe("prueba/led/cmd");
      client.subscribe("prueba/led2/cmd");
      client.subscribe("prueba/todo/cmd");
    } else {
      Serial.print("Fallo rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  connectWiFi();
  connectMQTT();
  client.publish("prueba/led/state", "OFF", true);
  client.publish("prueba/led2/state", "OFF", true);
  client.publish("prueba/todo/state", "OFF", true);
}

void loop() {
  if (!client.connected()) {
    connectMQTT();
  }
  client.loop();
}
