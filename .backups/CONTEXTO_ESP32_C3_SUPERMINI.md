# 📋 Contexto de Proyecto: ESP32-C3 Super Mini (Puesta en Marcha y Domótica)

> **Documento de traspaso de contexto para Agente de IA.**  
> **Fecha de creación:** 23 de octubre de 2026  
> **Estado:** Placa recuperada, entorno operativo, conectada a Wi-Fi local y lista para proyectos de domótica paso a paso.

---

## 1. 🎯 Objetivo del Proyecto
El usuario parte de **nivel cero** en microcontroladores y programación.  
El objetivo actual es avanzar **paso a paso** en el desarrollo de proyectos de **domótica (Smart Home)** utilizando una placa compacta **ESP32-C3 Super Mini** conectada a la red local del hogar.

---

## 2. 🔌 Hardware Identificado y Características
- **Placa:** ESP32-C3 Super Mini (modelo compacto con antena cerámica).
- **Procesador:** ESP32-C3 (RISC-V de 32 bits a 160 MHz, monocúcleo).
- **Memoria Flash:** 4 MB embebida (modo `DIO`, 80 MHz).
- **Conectividad:** Wi-Fi 2.4 GHz (802.11 b/g/n) + Bluetooth 5 (LE).
- **Interfaz USB:** Conexión USB nativa directa a los pines del procesador (USB-Serial/JTAG, GPIO18 D- y GPIO19 D+). Sin chip conversor externo tipo CH340/CP2102.
- **LEDs en placa:**
  - **LED Rojo (PWR):** Soldado directamente a la línea de 3.3V (indicador de alimentación, siempre encendido mientras haya corriente).
  - **LED de Usuario (si existe en la variante):** Mapeado en **GPIO 8** (activo a nivel `LOW`). *Nota: muchas variantes chinas omiten el LED de usuario y solo incluyen el rojo.*
- **Botones físicos:** Botón `BOOT` (GPIO 9) y botón `RST` (Reset/EN).

---

## 3. 💻 Entorno y Herramientas en el PC (Windows)
- **Sistema Operativo:** Windows.
- **Puerto Serie Identificado:** **`COM5`** (`Dispositivo serie USB`).
  - *(Nota: COM3 y COM4 son puertos virtuales de Bluetooth, no usarlos).*
- **IDE:** Arduino IDE 2.x instalado.
- **Paquete de Placas Instalado:** `esp32` de Espressif Systems (versión `3.3.12`).
- **Parámetros FQBN obligatorios:**
  ```text
  esp32:esp32:esp32c3:CDCOnBoot=cdc,FlashMode=dio
  ```
  > ⚠️ **Ajuste Crítico:** `USB CDC On Boot = Enabled` (`CDCOnBoot=cdc`). Si no se activa, la función `Serial.print()` no envía texto a través del USB nativo a la consola del PC.
- **Rutas de herramientas CLI disponibles en el sistema:**
  - `arduino-cli`: `C:\Users\Usuario\AppData\Local\Programs\Arduino IDE\resources\app\lib\backend\resources\arduino-cli.exe`
  - `esptool`: `C:\Users\Usuario\AppData\Local\Arduino15\packages\esp32\tools\esptool_py\5.3.1\esptool.exe`

---

## 4. 🛠️ Problemas Iniciales Diagnosticados y Resueltos

### A. Ruido en bucle de conexión/desconexión USB en Windows
- **Causa:** El firmware de fábrica de la placa sufría un cuelgue continuo (*bootloop*). En los ESP32 con USB nativo (como el C3), cuando el procesador se reinicia en pánico, el controlador USB se resetea y hace sonar a Windows en bucle.
- **Solución implementada:** Se arrancó en modo descarga forzada (*ROM Bootloader*) manteniendo presionado el botón **`BOOT`** mientras se conectaba el cable USB.

### B. Fallo de compilación por sintaxis en SSID/Password
- **Causa:** Se introdujeron las credenciales de Wi-Fi sin comillas (`const char* ssid = MIWIFI_B07C;`).
- **Solución implementada:** Se añadieron las comillas dobles correspondientes (`"MIWIFI_B07C"`).

### C. Reset post-grabación
- El ESP32-C3 Super Mini no cuenta con circuito de auto-reinicio por transistores DTR/RTS. Tras subir código, en ocasiones requiere pulsar una vez el botón físico **`RST`** o reconectar el cable USB para que comience a ejecutar el programa.

---

## 5. 🌐 Estado Actual de Red y Conectividad
- **Red Wi-Fi configurada:** `MIWIFI_B07C` (Banda 2.4 GHz).
- **Estado de conexión:** Conectado y estable.
- **Dirección IP local asignada por DHCP:** **`192.168.1.38`**
- **Potencia de señal (RSSI):** `-57 dBm` (Señal excelente).

---

## 6. 📂 Códigos Guardados en el Equipo
Los proyectos de prueba funcionales se encuentran en la carpeta de Arduino del usuario:

1. **Test de Funcionamiento y Parpadeo:**
   - **Ruta:** `C:\Users\Usuario\Documents\Arduino\supermini_blink\supermini_blink.ino`
   - **Función:** Activa/desactiva GPIOs candidatos a LED (GPIO 8, 2, 3...) y envía telemetría serie a 115200 baudios.

2. **Conexión Wi-Fi y Asignación de IP:**
   - **Ruta:** `C:\Users\Usuario\Documents\Arduino\supermini_wifi\supermini_wifi.ino`
   - **Función:** Conecta a la red local y notifica el estado y la dirección IP por el puerto serie.

---

## 7. 🚀 Hoja de Ruta para Próximos Pasos (Domótica)
El usuario ha expresado interés en continuar **paso a paso**. Los hitos recomendados en orden didáctico son:

1. **Hito 1 (Inmediato): Servidor Web Básico en el ESP32**
   - El ESP32 servirá una página web HTML sencilla accesible desde cualquier móvil o navegador de la casa en `http://192.168.1.38`.
   - Permitirá pulsar un botón en el navegador del móvil y ver el cambio de estado reflejado.
2. **Hito 2: Control de un elemento físico (LED externo o Módulo Relé)**
   - Conectar un módulo relé de 1 canal a un pin digital (ej. GPIO 4 o GPIO 5) para accionar una carga real (bombilla, lámpara, etc.).
3. **Hito 3: Lectura de Sensores Ambientales**
   - Integración de un sensor de temperatura y humedad (DHT11/DHT22 o BMP280/BME280) y visualización de lecturas en tiempo real en la página web.
4. **Hito 4: Control por Voz / Notificaciones (Avanzado)**
   - Integración con Alexa (vía emulación local o SinricPro) o envío de alertas a bot de Telegram.

---

## ⚙️ Comandos Rápidos de Compilación y Subida para el Agente

Para compilar y subir cualquier sketch directamente a este ESP32-C3 sin intervención manual del usuario:

```powershell
# Definición de rutas
$cli = "C:\Users\Usuario\AppData\Local\Programs\Arduino IDE\resources\app\lib\backend\resources\arduino-cli.exe"
$fqbn = "esp32:esp32:esp32c3:CDCOnBoot=cdc,FlashMode=dio"
$port = "COM5"
$sketchPath = "C:\Ruta\Al\Sketch"

# Compilar
& $cli compile --fqbn $fqbn $sketchPath

# Subir
& $cli upload -p $port --fqbn $fqbn $sketchPath
```
