# 🏠 Domótica Smart Home con ESP32-C3 Super Mini

<div align="center">

![ESP32-C3](https://img.shields.io/badge/Hardware-ESP32--C3%20Super%20Mini-blue?style=for-the-badge&logo=espressif)
![Framework](https://img.shields.io/badge/Framework-Arduino%20C%2B%2B-00979D?style=for-the-badge&logo=arduino)
![Methodology](https://img.shields.io/badge/Workflow-OpenSpec%20Automated-brightgreen?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-En%20Desarrollo%20Activo-orange?style=for-the-badge)

**Sistema modular de automatización doméstica paso a paso impulsado por microcontroladores ultracompactos y desarrollo guiado por especificaciones.**

[Plan Casa Cebollo](PLAN_DOMOTICA_CASA_CEBOLLO.md) •
[Características](#-características-del-hardware) •
[Hoja de Ruta](#-hoja-de-ruta) •
[Estructura](#-estructura-del-proyecto) •
[Guía Rápida](#-guía-rápida-de-compilación-y-subida) •
[Seguridad y Normas](#-seguridad-y-normas) •
[Política de Ciberseguridad](SECURITY.md)

</div>

---

## 📖 Descripción del Proyecto

Este proyecto documenta y construye un **sistema de domótica (Smart Home) modular para el hogar**, diseñado específicamente desde un enfoque didáctico y evolutivo paso a paso. 

Utiliza la placa **ESP32-C3 Super Mini**, un microcontrolador miniatura de bajo coste y gran potencia basado en la arquitectura RISC-V, dotado de conectividad Wi-Fi y Bluetooth LE para controlar dispositivos físicos, recopilar telemetría de sensores ambientales e interactuar con interfaces web y asistentes virtuales.

El desarrollo se gestiona íntegramente mediante el estándar de especificaciones **OpenSpec**, garantizando trazabilidad, pruebas de compilación automáticas y respaldo integral de código.

---

## ⚡ Características del Hardware

| Parámetro | Detalle Técnico |
| :--- | :--- |
| **Placa** | ESP32-C3 Super Mini (con antena cerámica integrada) |
| **Núcleo / CPU** | RISC-V de 32 bits a 160 MHz (monocúcleo) |
| **Memoria Flash** | 4 MB embebida (Modo `DIO`, 80 MHz) |
| **Conectividad** | Wi-Fi 2.4 GHz (802.11 b/g/n) + Bluetooth 5 (LE) |
| **Interfaz USB** | USB nativo directo a CPU (GPIO 18 D- / GPIO 19 D+) |
| **LEDs en placa** | LED Rojo (PWR en 3.3V) / LED de Usuario opcional (GPIO 8) |
| **Botones físicos**| `BOOT` (GPIO 9) y `RST` (Reset / EN) |
| **Tensión de Trabajo** | 3.3 V (los pines GPIO **no** toleran 5 V directamente) |

```text
               ESP32-C3 Super Mini (Pinout Resumido)
                       +-------------------+
                 5V  --| [ ]           [ ] |-- 3V3
                GND  --| [ ]           [ ] |-- GND
             GPIO 0  --| [ ]  [Antena] [ ] |-- GPIO 1
             GPIO 2  --| [ ]  Cerámica [ ] |-- GPIO 3
             GPIO 4  --| [ ]           [ ] |-- GPIO 5
             GPIO 6  --| [ ]   [CPU]   [ ] |-- GPIO 7
             GPIO 8  --| [ ]           [ ] |-- GPIO 9 (BOOT)
             GPIO 10 --| [ ]   [USB]   [ ] |-- GPIO 20 (RX)
                       +-------------------+
                               [USB-C]
```

---

## 🚀 Hoja de Ruta (Roadmap)

> 📌 **Plan Director Completo de Fases:** Consulta [`PLAN_DOMOTICA_CASA_CEBOLLO.md`](PLAN_DOMOTICA_CASA_CEBOLLO.md) para la guía paso a paso de automatización inalámbrica por Wi-Fi de luces y persiana.

- [x] **Fase 0: Puesta en Marcha y Conexión Base**
  - Desbloqueo y recuperación de la placa en modo ROM Bootloader.
  - Conexión a la red Wi-Fi doméstica (`MIWIFI_B07C`) y asignación de IP fija/DHCP (`192.168.1.38`).
  - Configuración del flujo de trabajo con OpenSpec, respaldos y Git.
- [x] **Hito 1: Servidor Web HTTP Interactivo**
  - Servidor web ligero embebido en el ESP32 accesible desde móvil y PC en `http://192.168.1.38`.
  - Panel de control minimalista con botones para interactuar y visualizar estados.
  - Implementado con seguridad POST-only para actuadores y Fail-Safe.
- [ ] **Hito 2: Control de Cargas Físicas (Actuadores)**
  - Integración de módulo relé de 1 canal / LED externo para controlar lámparas o aparatos reales.
  - Aislamiento eléctrico y protección de los pines GPIO.
- [ ] **Hito 3: Monitorización Ambiental (Sensores)**
  - Lectura de temperatura y humedad con sensor (DHT11 / DHT22 o BME280).
  - Telemetría en tiempo real y gráficos en el servidor web local.
- [ ] **Hito 4: Integración Avanzada (Voz y Alertas)**
  - Control por voz mediante Amazon Alexa (SinricPro / emulación local Belkin WeMo).
  - Bot de notificaciones y alertas automáticas en Telegram.

---

## 📂 Estructura del Proyecto

```plaintext
Domotica/
├── .agents/                 # Habilidades y flujos de trabajo del agente IA
│   ├── skills/              # Skills de OpenSpec configuradas
│   └── workflows/           # Comandos y flujos (propose, apply, archive...)
├── .backups/                # Copias de seguridad históricas (política anti-pérdida)
│   └── CONTEXTO_ESP32_C3_SUPERMINI.md
├── openspec/                # Sistema de especificaciones guiadas
│   ├── changes/             # Cambios activos y archivados
│   ├── specs/               # Especificaciones consolidadas del sistema
│   └── config.yaml          # Configuración del estándar OpenSpec
├── supermini_wifi/          # Sketch base de conexión y diagnóstico Wi-Fi
│   └── supermini_wifi.ino
├── AGENTS.md                # Instrucciones operativas del agente de desarrollo
├── PROJECT_RULES.md         # Documento maestro: contexto, reglas técnicas y hardware
├── README.md                # Portada y documentación general del proyecto
└── .gitignore               # Exclusión de binarios y temporales de compilación
```

---

## 💻 Guía Rápida de Compilación y Subida

### 1. Parámetros Críticos de Placa
El ESP32-C3 Super Mini utiliza comunicación USB nativa directa sin chip conversor intermedio. Por ello, el parámetro **`CDCOnBoot=cdc`** es **obligatorio** para poder ver los mensajes de `Serial.print()` en la consola:

- **FQBN Requerido:**
  ```text
  esp32:esp32:esp32c3:CDCOnBoot=cdc,FlashMode=dio
  ```
- **Puerto Serie (Windows):** `COM5`

### 2. Comandos CLI (PowerShell)

Para compilar y grabar cualquier sketch usando `arduino-cli`:

```powershell
$cli = "C:\Users\Usuario\AppData\Local\Programs\Arduino IDE\resources\app\lib\backend\resources\arduino-cli.exe"
$fqbn = "esp32:esp32:esp32c3:CDCOnBoot=cdc,FlashMode=dio"
$port = "COM5"
$sketch = "C:\Users\Usuario\Desktop\Cosas_proyectos\Domotica\supermini_wifi"

# Compilar el código
& $cli compile --fqbn $fqbn $sketch

# Subir a la placa ESP32-C3
& $cli upload -p $port --fqbn $fqbn $sketch
```

### 3. Solución de Problemas Comunes de Subida
- **Bootloop / Desconexiones continuas de USB en Windows:** Mantén presionado el botón físico **`BOOT`** (GPIO 9) mientras conectas el cable USB al PC para forzar el modo de descarga (*ROM Bootloader*).
- **El programa no arranca tras grabar:** La placa no posee circuito de autoreset (DTR/RTS). Pulsa una vez el botón físico **`RST`** tras finalizar la subida.

---

## 🛡️ Seguridad y Normas del Proyecto

Para consultar el estándar íntegro de ciberseguridad, privacidad y protección contra intrusiones:
👉 **[SECURITY.md](SECURITY.md)**

1. **Seguridad Eléctrica y Fail-Safe:**
   - La lógica del ESP32-C3 opera a **3.3V**. Nunca conectes señales de 5V directamente a los pines GPIO sin convertidor de nivel lógico o divisor resistivo.
   - En caso de reinicio o pérdida de conexión, los relés y actuadores quedan por defecto en estado apagado/seguro.
2. **Ciberseguridad en el Hogar:**
   - Cero apertura de puertos en el router (sin port forwarding / DMZ).
   - Acceso web protegido y peticiones críticas por POST.
3. **Política Estricta de Respaldos y Secretos:**
   - Ninguna clave API ni contraseña se sube a Git (aislamiento en `.gitignore`).
   - Ningún archivo se elimina o sobreescribe sin una copia previa en la carpeta `.backups/`.
4. **Flujo de Trabajo Automatizado:**
   - No es necesario ejecutar comandos manuales de OpenSpec; el agente interpreta los requerimientos, crea las especificaciones, aplica los cambios y archiva el resultado automáticamente.

---

<div align="center">
Desarrollado con ❤️ para aprendizaje y control inteligente del hogar.
</div>
