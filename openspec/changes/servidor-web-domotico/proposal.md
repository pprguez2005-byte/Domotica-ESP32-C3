# Propuesta: Servidor Web Domótico en ESP32-C3

## Motivación (Why)
Actualmente el ESP32-C3 Super Mini se conecta a la red Wi-Fi doméstica (`MIWIFI_B07C`), pero no ofrece ninguna interfaz interactiva ni servicio para recibir comandos. Este cambio implementa un servidor web HTTP embebido ligero y seguro que permite al usuario controlar y monitorizar dispositivos desde cualquier navegador (teléfono móvil o PC en la red local) accediendo a `http://192.168.1.38`.

## Qué Cambia (What Changes)
- Se crea un sketch autónomo en `supermini_webserver/` con conexión Wi-Fi persistente y servidor HTTP en el puerto 80 (`WebServer`).
- Se sirve una interfaz web visual, minimalista, moderna y táctil (HTML5 + CSS responsivo embebido) accesible desde el móvil.
- Se implementan botones virtuales interactivos para controlar dispositivos del hogar:
  - Dispositivo 1: "Luz de Prueba / LED de Placa" (GPIO 8 / testigo virtual).
  - Dispositivo 2: "Simulador de Relé / Enchufe" (estado seguro Fail-Safe).
- Se aplica el principio de ciberseguridad establecido en `SECURITY.md`:
  - Lectura de estado mediante peticiones `GET`.
  - Conmutación y cambios de estado exclusivamente mediante peticiones `POST` a `/api/toggle`.
- Se añade telemetría básica visible en la web: estado Wi-Fi, IP local, potencia de señal (RSSI) y tiempo de actividad (*uptime*).

## Capacidades (Capabilities)

### Nuevas Capacidades
- `servidor-web`: Servicio HTTP embebido en el ESP32-C3 para despachar la interfaz web y gestionar endpoints REST/HTTP de forma local y segura.
- `control-dispositivos`: Gestión del estado de actuadores e indicadores físicos/virtuales garantizando inicialización en estado seguro (Fail-Safe).

### Capacidades Modificadas
*(Ninguna; se trata del primer hito del sistema domótico).*

## Impacto (Impact)
- **Nuevo sketch:** `supermini_webserver/supermini_webserver.ino`.
- **Dependencias:** Librerías estándar del core de ESP32 (`WiFi.h`, `WebServer.h`).
- **Compatibilidad de compilación:** Valorable y verificable mediante `arduino-cli` con FQBN `esp32:esp32:esp32c3:CDCOnBoot=cdc,FlashMode=dio`.
