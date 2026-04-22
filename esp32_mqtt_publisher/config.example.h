#ifndef CONFIG_EXAMPLE_H
#define CONFIG_EXAMPLE_H

// Copia este archivo como config.h y edita los valores.

const char* WIFI_SSID = "TU_RED_WIFI";
const char* WIFI_PASSWORD = "TU_PASSWORD_WIFI";

// Cambia esta IP por la IP de la Raspberry Pi.
const char* MQTT_SERVER = "192.168.1.100";
const int MQTT_PORT = 1883;

const char* MQTT_CLIENT_ID = "esp32-publisher";
const char* MQTT_TOPIC = "iot/esp32/mosquito";

#endif
