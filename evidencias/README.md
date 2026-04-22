# Evidencias

Coloca aqui las capturas de pantalla o logs de la practica.

## Lista sugerida

1. `01-instalacion-mosquitto.png`: instalacion de `mosquitto` y `mosquitto-clients`.
2. `02-servicio-mosquitto.png`: salida de `sudo systemctl status mosquitto`.
3. `03-prueba-local.png`: prueba con `mosquitto_sub` y `mosquitto_pub` en Raspberry Pi.
4. `04-monitor-serial-esp32.png`: Monitor Serial mostrando conexion WiFi y MQTT.
5. `05-subscriber-raspberry-esp32.png`: Raspberry Pi recibiendo mensajes de la ESP32.

Tambien puedes guardar logs de texto, por ejemplo:

```bash
sudo systemctl status mosquitto > evidencias/02-servicio-mosquitto.txt
mosquitto_sub -h localhost -t iot/esp32/mosquito -v > evidencias/05-subscriber-raspberry-esp32.txt
```
