# Reporte de configuracion ESP32 MQTT

## Datos generales

- Proyecto: Mosquitto MQTT con Raspberry Pi y ESP32.
- Componente revisado: `esp32_mqtt_publisher/esp32_mqtt_publisher.ino`.
- Objetivo: preparar el entorno Arduino/VS Code para compilar y cargar un publisher MQTT en ESP32.

## Problema detectado

VS Code mostro el siguiente error de IntelliSense:

```text
no se pudo abrir el archivo de codigo fuente "WiFi.h"
```

El archivo `WiFi.h` no pertenece a GCC ni a C++ de escritorio. Es parte del core Arduino para ESP32. Por eso, si el soporte de tarjetas ESP32 no esta instalado o VS Code no conoce sus rutas, IntelliSense no puede resolver el `#include`.

## Librerias y paquetes requeridos

En Arduino IDE se deben instalar:

1. `esp32 by Espressif Systems`
   - Se instala desde Boards Manager.
   - Proporciona el core ESP32 y headers como `WiFi.h`.
   - Se recomienda usar la version mas reciente disponible.

2. `PubSubClient by Nick O'Leary`
   - Se instala desde Library Manager.
   - Proporciona `PubSubClient.h`.
   - Es la libreria MQTT usada por el sketch.

## Configuracion local del proyecto

Se ajusto la configuracion de VS Code en:

```text
.vscode/c_cpp_properties.json
```

Se agregaron rutas tipicas de Arduino y ESP32:

```text
${env:LOCALAPPDATA}/Arduino15/packages/esp32/hardware/esp32/**
${env:LOCALAPPDATA}/Arduino15/packages/esp32/tools/**
${env:USERPROFILE}/Documents/Arduino/libraries/**
${env:USERPROFILE}/OneDrive/Documents/Arduino/libraries/**
```

Tambien se configuraron defines basicos para ESP32:

```text
ARDUINO=10819
ARDUINO_ARCH_ESP32
ESP32
```

Adicionalmente, en:

```text
.vscode/settings.json
```

se asocio la extension `.ino` con C++ para mejorar el analisis de IntelliSense.

## Archivo de credenciales

El sketch incluye:

```cpp
#include "config.h"
```

Por seguridad, `config.h` no debe subirse al repositorio. Debe crearse localmente copiando:

```text
esp32_mqtt_publisher/config.example.h
```

como:

```text
esp32_mqtt_publisher/config.h
```

Luego se editan los valores:

```cpp
const char* WIFI_SSID = "TU_RED_WIFI";
const char* WIFI_PASSWORD = "TU_PASSWORD_WIFI";
const char* MQTT_SERVER = "192.168.1.100";
```

`MQTT_SERVER` debe ser la IP de la Raspberry Pi donde corre Mosquitto.

## Funcionamiento esperado

Cuando la ESP32 se conecta correctamente:

1. Se conecta a la red WiFi configurada.
2. Se conecta al broker MQTT en la Raspberry Pi.
3. Publica cada 5 segundos en el topico:

```text
iot/esp32/mosquito
```

El mensaje publicado tiene formato JSON:

```json
{"device":"esp32-publisher","uptime_ms":15000,"counter":3,"rssi":-51}
```

## Verificacion

En la Raspberry Pi se puede comprobar la recepcion con:

```bash
mosquitto_sub -h localhost -t iot/esp32/mosquito -v
```

La salida esperada es similar a:

```text
iot/esp32/mosquito {"device":"esp32-publisher","uptime_ms":5000,"counter":1,"rssi":-50}
iot/esp32/mosquito {"device":"esp32-publisher","uptime_ms":10000,"counter":2,"rssi":-51}
```

## Conclusiones

El error de `WiFi.h` se debe a una configuracion incompleta del entorno, no necesariamente a un error del codigo. Para resolverlo se debe instalar el paquete `esp32 by Espressif Systems`, instalar `PubSubClient by Nick O'Leary`, crear el archivo local `config.h` y reiniciar o refrescar IntelliSense en VS Code.
