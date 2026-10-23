# 🏠 Proyecto de Domótica (Smart Home) con ESP32-C3 Super Mini

> **GUÍA MAESTRA, CONTEXTO TÉCNICO Y NORMAS DEL PROYECTO**  
> Este documento unifica la visión del proyecto, el contexto técnico del hardware, la hoja de ruta de domótica y las reglas operativas de trabajo.  
> **Lectura obligatoria para cualquier agente en cada sesión.**

---

## 1. 🎯 Visión y Alcance del Proyecto

- **Objetivo:** Construir un sistema de domótica modular para el hogar utilizando la placa ultracompacta **ESP32-C3 Super Mini** conectada a la red Wi-Fi doméstica.
- **Perfil del usuario:** Nivel principiante en microcontroladores y programación.
- **Enfoque pedagógico:**
  - Desarrollo **paso a paso**, validando cada funcionalidad antes de avanzar.
  - Explicaciones claras, didácticas y comprensibles (sin asumir conocimientos previos).
  - Indicaciones rigurosas sobre seguridad eléctrica y cableado (distinción entre 3.3V y 5V).

---

## 2. 🔌 Hardware y Entorno Técnico

### Placa y Microcontrolador
- **Modelo:** ESP32-C3 Super Mini (diseño miniatura con antena cerámica).
- **Procesador:** ESP32-C3 (arquitectura RISC-V de 32 bits a 160 MHz, monocúcleo).
- **Memoria Flash:** 4 MB embebida (modo `DIO`, 80 MHz).
- **Conectividad:** Wi-Fi 2.4 GHz (802.11 b/g/n) + Bluetooth 5 (LE).
- **Puerto USB:** Nativo USB-Serial/JTAG directo al procesador (GPIO 18 D- y GPIO 19 D+). Sin chip conversor externo (como CH340 o CP2102).
- **Pines y componentes en placa:**
  - **LED Rojo (PWR):** Conectado directamente a la línea de 3.3V (siempre encendido con corriente).
  - **LED de Usuario:** GPIO 8 (activo a nivel `LOW` en las variantes que lo incluyen).
  - **Botón `BOOT`:** GPIO 9 (pulsar al conectar USB para forzar modo descarga si hay bootloop).
  - **Botón `RST`:** Reset / EN (pulsar tras grabar firmware si la placa no reinicia automáticamente).

### Entorno en el PC (Windows)
- **Puerto Serie Identificado:** **`COM5`** (`Dispositivo serie USB`).
  - *(Descartar puertos virtuales Bluetooth como COM3 o COM4).*
- **Parámetros FQBN obligatorios:**
  ```text
  esp32:esp32:esp32c3:CDCOnBoot=cdc,FlashMode=dio
  ```
  > ⚠️ **Ajuste Crítico:** `CDCOnBoot=cdc` (USB CDC On Boot = Enabled). Sin este flag, `Serial.print()` no envía datos por el puerto USB nativo a la consola de Windows.
- **Rutas de herramientas CLI:**
  - `arduino-cli`: `C:\Users\Usuario\AppData\Local\Programs\Arduino IDE\resources\app\lib\backend\resources\arduino-cli.exe`
  - `esptool`: `C:\Users\Usuario\AppData\Local\Arduino15\packages\esp32\tools\esptool_py\5.3.1\esptool.exe`

### Red y Conectividad Doméstica
- **Red Wi-Fi configurada:** `MIWIFI_B07C` (2.4 GHz).
- **Dirección IP local asignada:** **`192.168.1.38`** (DHCP / Reserva local).
- **RSSI reportado:** `-57 dBm` (conexión óptima).

---

## 3. 🛠️ Incidencias Resueltas y Buenas Prácticas

1. **Bucle de conexión/desconexión USB (Bootloop en Windows):**
   - *Causa:* Pánico en arranque reinicia el USB nativo en bucle.
   - *Solución:* Mantener pulsado el botón **`BOOT`** (GPIO 9) mientras se conecta el cable USB para entrar en modo *ROM Bootloader*.
2. **Sintaxis en credenciales Wi-Fi:**
   - Recordar siempre entrecomillar strings en C++ (`const char* ssid = "MIWIFI_B07C";`).
3. **Ausencia de auto-reinicio por hardware:**
   - La placa no tiene circuito DTR/RTS. Tras flashear un sketch con `arduino-cli upload`, puede ser necesario presionar una vez el botón físico **`RST`**.

---

## 4. 🚀 Hoja de Ruta de Domótica

1. **Hito 1: Servidor Web Básico en el ESP32 (Siguiente paso)**
   - Desplegar servidor HTTP accesible en `http://192.168.1.38`.
   - Interfaz web minimalista con botones para interactuar y visualizar estados desde el móvil.
2. **Hito 2: Control de Cargas Físicas (Relé o LED externo)**
   - Conectar un módulo relé de 1 canal o LED a un GPIO seguro (ej. GPIO 4 o 5) para controlar dispositivos reales.
3. **Hito 3: Monitorización Ambiental**
   - Integración de sensor de temperatura y humedad (DHT11/DHT22 o BME280) y telemetría en tiempo real en la web.
4. **Hito 4: Control por Voz y Notificaciones**
   - Integración con asistentes de voz (Alexa / SinricPro) o bot de alertas por Telegram.

---

## 5. 🔄 Automatización del Flujo OpenSpec

**Regla de Oro:** El usuario **no** ejecuta comandos de OpenSpec. El agente gestiona todo el ciclo de vida:

1. **Propuesta (`propose`)**:
   - Cada nueva solicitud se estructura como un cambio en `openspec/changes/<change-name>/` con `proposal.md`, `specs/` y `tasks.md`.
   - Todo se redacta en **español**.
2. **Implementación (`apply`)**:
   - El agente ejecuta las tareas programadas, escribe el código y valida la compilación con `arduino-cli`:
     ```powershell
     $cli = "C:\Users\Usuario\AppData\Local\Programs\Arduino IDE\resources\app\lib\backend\resources\arduino-cli.exe"
     $fqbn = "esp32:esp32:esp32c3:CDCOnBoot=cdc,FlashMode=dio"
     $port = "COM5"
     & $cli compile --fqbn $fqbn $sketchPath
     & $cli upload -p $port --fqbn $fqbn $sketchPath
     ```
   - Se actualizan las tareas completadas en `tasks.md`.
3. **Sincronización y Archivo (`archive`)**:
   - Tras validar con éxito el hito, el agente sincroniza las especificaciones principales y archiva el cambio (`openspec archive <change-name> --yes`).

---

## 6. 📝 Historial Dinámico de Decisiones

- **[23/10/2026] - Centralización de Contexto:** Se unificó toda la información de `CONTEXTO_ESP32_C3_SUPERMINI.md` en este archivo maestro y en `AGENTS.md`.
- **[23/10/2026] - Idioma oficial:** Español en todos los artefactos, documentación y comentarios.
- **[23/10/2026] - Gestión de Sketches:** Cada hito de domótica tendrá su carpeta dedicada dentro del repositorio para preservar el historial funcional (ej. `supermini_wifi`, `supermini_webserver`, etc.).
