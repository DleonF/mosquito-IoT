#include <WiFi.h>
#include <PubSubClient.h>

#include "config.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

const unsigned long publishIntervalMs = 5000;
unsigned long lastPublishMs = 0;
unsigned long messageCounter = 0;

void connectToWifi() {
  Serial.print("Conectando a WiFi: ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi conectado. IP ESP32: ");
  Serial.println(WiFi.localIP());
}

void connectToMqtt() {
  while (!mqttClient.connected()) {
    Serial.print("Conectando a MQTT en ");
    Serial.print(MQTT_SERVER);
    Serial.print(":");
    Serial.println(MQTT_PORT);

    if (mqttClient.connect(MQTT_CLIENT_ID)) {
      Serial.println("MQTT conectado");
    } else {
      Serial.print("Error MQTT, rc=");
      Serial.print(mqttClient.state());
      Serial.println(". Reintentando en 3 segundos");
      delay(3000);
    }
  }
}

void publishMessage() {
  messageCounter++;

  char payload[160];
  snprintf(
    payload,
    sizeof(payload),
    "{\"device\":\"%s\",\"uptime_ms\":%lu,\"counter\":%lu,\"rssi\":%d}",
    MQTT_CLIENT_ID,
    millis(),
    messageCounter,
    WiFi.RSSI()
  );

  bool sent = mqttClient.publish(MQTT_TOPIC, payload);

  Serial.print("Publicando en ");
  Serial.print(MQTT_TOPIC);
  Serial.print(": ");
  Serial.println(payload);

  if (!sent) {
    Serial.println("No se pudo publicar el mensaje");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  connectToWifi();
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectToWifi();
  }

  if (!mqttClient.connected()) {
    connectToMqtt();
  }

  mqttClient.loop();

  unsigned long now = millis();
  if (now - lastPublishMs >= publishIntervalMs) {
    lastPublishMs = now;
    publishMessage();
  }
}
