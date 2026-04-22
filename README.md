# Mosquitto MQTT con Raspberry Pi y ESP32

Actividad de IoT para instalar y configurar un broker MQTT Mosquitto en Raspberry Pi y registrar una ESP32 como publisher.

## Objetivo

Demostrar una arquitectura MQTT sencilla:

- Raspberry Pi: broker Mosquitto y subscriber de prueba.
- ESP32: publisher que envia mensajes periodicos.
- Topico usado: `iot/esp32/mosquito`.

## Material

- Raspberry Pi con Raspberry Pi OS.
- ESP32.
- Arduino IDE.
- Red WiFi local compartida entre Raspberry Pi y ESP32.
- Libreria Arduino `PubSubClient`.

## 1. Instalacion de Mosquitto en Raspberry Pi

Actualizar paquetes:

```bash
sudo apt update
sudo apt upgrade -y
```

Instalar Mosquitto y clientes de prueba:

```bash
sudo apt install -y mosquitto mosquitto-clients
```

Habilitar Mosquitto como servicio al inicio:

```bash
sudo systemctl enable mosquitto
sudo systemctl start mosquitto
sudo systemctl status mosquitto
```

Obtener la IP de la Raspberry Pi:

```bash
hostname -I
```

Guarda esa IP porque se usa en el codigo de la ESP32.

## 2. Configuracion del broker

Para una practica dentro de red local se puede permitir conexion anonima en el puerto `1883`.

Crear el archivo:

```bash
sudo nano /etc/mosquitto/conf.d/iot-local.conf
```

Contenido:

```conf
listener 1883 0.0.0.0
allow_anonymous true
```

Reiniciar el servicio:

```bash
sudo systemctl restart mosquitto
sudo systemctl status mosquitto
```

> Nota: `allow_anonymous true` solo se recomienda para laboratorio en red local. Para produccion se deben usar usuarios, contrasenas y TLS.

## 3. Prueba basica del broker

Terminal 1 en Raspberry Pi, ejecutar un subscriber:

```bash
mosquitto_sub -h localhost -t iot/esp32/mosquito -v
```

Terminal 2 en Raspberry Pi, publicar un mensaje:

```bash
mosquitto_pub -h localhost -t iot/esp32/mosquito -m "Prueba local desde Raspberry Pi"
```

Salida esperada en Terminal 1:

```text
iot/esp32/mosquito Prueba local desde Raspberry Pi
```

## 4. Publisher ESP32

### Librerias requeridas

En Arduino IDE instalar:

- `PubSubClient` de Nick O'Leary.

Tambien debe estar instalado el soporte de tarjetas ESP32 en Arduino IDE.

### Configuracion

1. Abrir la carpeta `esp32_mqtt_publisher` en Arduino IDE.
2. Copiar `config.example.h` como `config.h`.
3. Editar `config.h` con:
   - SSID de WiFi.
   - Contrasena de WiFi.
   - IP de la Raspberry Pi.
4. Seleccionar la tarjeta ESP32 correspondiente.
5. Cargar el programa.
6. Abrir el Monitor Serial a `115200`.

El programa publica cada 5 segundos en:

```text
iot/esp32/mosquito
```

Ejemplo de mensaje:

```json
{"device":"esp32-publisher","uptime_ms":15000,"counter":3,"rssi":-51}
```

## 5. Verificacion con ESP32

En la Raspberry Pi ejecutar:

```bash
mosquitto_sub -h localhost -t iot/esp32/mosquito -v
```

Si la ESP32 esta conectada correctamente, se recibiran mensajes similares a:

```text
iot/esp32/mosquito {"device":"esp32-publisher","uptime_ms":5000,"counter":1,"rssi":-50}
iot/esp32/mosquito {"device":"esp32-publisher","uptime_ms":10000,"counter":2,"rssi":-51}
```

## 6. Evidencias

Agregar capturas o logs en la carpeta `evidencias/`:

- Instalacion correcta de Mosquitto.
- Estado del servicio `mosquitto`.
- Prueba local con `mosquitto_sub` y `mosquitto_pub`.
- Monitor Serial de Arduino IDE mostrando conexion WiFi/MQTT.
- Raspberry Pi recibiendo mensajes publicados por la ESP32.

La carpeta incluye un archivo `evidencias/README.md` con una lista sugerida.

## Estructura del repositorio

```text
.
├── README.md
├── .gitignore
├── esp32_mqtt_publisher/
│   ├── esp32_mqtt_publisher.ino
│   └── config.example.h
├── raspberry-pi/
│   └── iot-local.conf
└── evidencias/
    └── README.md
```

## Subir a GitHub

Inicializar y subir el repositorio:

```bash
git init
git add .
git commit -m "Documenta practica Mosquitto MQTT con ESP32"
git branch -M main
git remote add origin https://github.com/TU_USUARIO/TU_REPOSITORIO.git
git push -u origin main
```

Reemplaza `TU_USUARIO` y `TU_REPOSITORIO` por los datos de tu repositorio en GitHub.
