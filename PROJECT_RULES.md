# 🏠 Proyecto de Domótica (Smart Home) con ESP32-C3 Super Mini

> **GUÍA MAESTRA, CONTEXTO TÉCNICO Y NORMAS DEL PROYECTO**  
> Este documento unifica la visión del proyecto, el contexto técnico del hardware, la hoja de ruta de domótica y las reglas operativas de trabajo.  
> **Lectura obligatoria para cualquier agente en cada sesión.**

---

## 1. 🔐 Regla Inviolable: Protección de APIs, Secretos y Credenciales (Zero Leaks)

- **NUNCA subir a Git claves de API, tokens ni credenciales:** Está terminantemente prohibido hacer commit o push de cualquier clave privada, API Key (ej. Telegram Bot token, SinricPro, tokens de servicios cloud), contraseñas de red o certificados.
- **Aislamiento en `.gitignore`:** Todo archivo que contenga credenciales o claves privadas debe estar incluido obligatoriamente en [`.gitignore`](file:///C:/Users/Usuario/Desktop/Cosas_proyectos/Domotica/.gitignore). Esto incluye expresamente:
  - Archivos de cabecera C/C++: `secrets.h`, `credentials.h`, `wifi_credentials.h`, `api_keys.h`, `token.h`, `tokens.h`, `config.local.h`.
  - Archivos de entorno y configuración: `.env`, `*.env`, `.env.*`, `secrets.json`, `credentials.json`, `service-account*.json`.
  - Certificados y llaves: `*.pem`, `*.key`, `*.crt`, `*.cert`.
- **Estrategia de plantillas seguras:** Cuando el código necesite credenciales o claves para compilar, solo se subirá al repositorio un archivo de ejemplo público (por ejemplo, `secrets.example.h` con campos vacíos `""`). El usuario creará localmente su copia privada (`secrets.h`) que Git ignorará por completo.
- **Auditoría pre-commit:** Antes de cada `git add` y `git commit`, el agente debe revisar que no se filtre ningún dato confidencial.

---

## 2. 🛡️ Política de Ciberseguridad y Privacidad Doméstica (Casa Real)

> Documento extendido de referencia: [`SECURITY.md`](file:///C:/Users/Usuario/Desktop/Cosas_proyectos/Domotica/SECURITY.md)

Al tratarse de una instalación en una vivienda real conectada a la red Wi-Fi, todo desarrollo debe aplicar principios estrictos de ciberseguridad IoT:

1. **Aislamiento de Red (Sin apertura de puertos / No Port Forwarding):**
   - NUNCA abrir puertos directos en el router doméstico hacia la IP del ESP32.
   - El acceso remoto se efectuará únicamente mediante conexiones salientes cifradas (TLS/HTTPS con Telegram, SinricPro o túneles VPN WireGuard/Tailscale).
2. **Seguridad en Servidor Web Local:**
   - Métodos HTTP seguros: Las acciones que alteran estado (relés, actuadores) solo se admiten por `POST`, nunca por `GET`.
   - Control de acceso: Protección de rutas administrativas con autenticación para evitar accesos no autorizados dentro de la red local.
   - Rate limiting (protección de actuadores): Evitar conmutaciones rápidas que puedan dañar relés mecánicos o provocar sobrecalentamiento.
3. **Cifrado en Tránsito (TLS 1.2+):**
   - Toda comunicación con servicios externos empleará `WiFiClientSecure` con cifrado TLS.
4. **Principio Fail-Safe (Fallo Seguro):**
   - En caso de reinicio de la placa, caída de red o error de firmware, todos los actuadores y relés deben quedar por defecto en estado **apagado/seguro**.
5. **Privacidad Total (Cero Telemetría):**
   - No se implementará ninguna librería ni llamada que envíe telemetría o datos de hábitos de la vivienda a servidores externos no autorizados por el usuario.

---

## 3. 💾 Política de Backups y Control de Cambios

1. **Control de Versiones (Git Local y Remoto):**
   - El proyecto cuenta con repositorio Git sincronizado con GitHub (`https://github.com/pprguez2005-byte/Domotica-ESP32-C3`).
   - Cada hito o modificación relevante se registra mediante commits limpios y descriptivos.
   - En caso de fallo, se puede volver al estado anterior de inmediato (`git restore` o `git checkout`).
2. **Carpeta de Respaldos (`.backups/`):**
   - Antes de modificar sustancialmente o eliminar cualquier archivo existente a petición del usuario, el agente **DEBE** guardar una copia íntegra en [`.backups/`](file:///C:/Users/Usuario/Desktop/Cosas_proyectos/Domotica/.backups).
   - Prohibido borrar archivos sin respaldo previo.

---

## 4. 🎯 Visión y Alcance del Proyecto

- **Objetivo:** Construir un sistema de domótica modular para el hogar utilizando la placa ultracompacta **ESP32-C3 Super Mini** conectada a la red Wi-Fi doméstica.
- **Perfil del usuario:** Nivel principiante en microcontroladores y programación.
- **Enfoque pedagógico:**
  - Desarrollo **paso a paso**, validando cada funcionalidad antes de avanzar.
  - Explicaciones claras, didácticas y comprensibles.
  - Indicaciones rigurosas sobre seguridad eléctrica y cableado (3.3V vs 5V).
- **Descarga de Skills de OpenSpec:** Si en algún momento se considera necesario instalar una skill o plugin adicional de OpenSpec, **siempre se debe consultar y pedir confirmación previa al usuario** antes de descargar o instalar nada.

---

## 5. 🔌 Hardware y Entorno Técnico

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

## 6. 🛠️ Incidencias Resueltas y Buenas Prácticas

1. **Bucle de conexión/desconexión USB (Bootloop en Windows):**
   - *Solución:* Mantener pulsado el botón **`BOOT`** (GPIO 9) mientras se conecta el cable USB para entrar en modo *ROM Bootloader*.
2. **Sintaxis en credenciales Wi-Fi:**
   - Recordar siempre entrecomillar strings en C++ (`const char* ssid = "MIWIFI_B07C";`).
3. **Ausencia de auto-reinicio por hardware:**
   - Tras flashear un sketch con `arduino-cli upload`, presionar una vez el botón físico **`RST`** si no arranca de inmediato.

---

## 7. 🚀 Hoja de Ruta de Domótica

1. **Hito 1: Servidor Web Básico en el ESP32 (Siguiente paso)**
   - Desplegar servidor HTTP seguro accesible en `http://192.168.1.38`.
   - Interfaz web minimalista con botones para interactuar y visualizar estados desde el móvil.
2. **Hito 2: Control de Cargas Físicas (Relé o LED externo)**
   - Conectar un módulo relé de 1 canal o LED a un GPIO seguro con estado seguro *Fail-Safe*.
3. **Hito 3: Monitorización Ambiental**
   - Integración de sensor de temperatura y humedad (DHT11/DHT22 o BME280) con telemetría local protegida.
4. **Hito 4: Control por Voz y Notificaciones Seguras**
   - Integración con asistentes de voz (Alexa / SinricPro) o bot de alertas por Telegram bajo TLS.

---

## 8. 🔄 Automatización del Flujo OpenSpec

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

## 9. 📝 Historial Dinámico de Decisiones

- **[23/10/2026] - Protocolo de Ciberseguridad y Privacidad Doméstica:** Se crea `SECURITY.md` con reglas contra ciberataques, sin port-forwarding, fail-safe en relés, cifrado TLS saliente y consulta previa obligatoria antes de instalar cualquier skill nueva.
- **[23/10/2026] - Blindaje de APIs y Secretos:** Regla estricta inviolable para que ninguna clave de API, token o credencial se suba jamás a Git, manteniéndolas siempre aisladas en `.gitignore`.
- **[23/10/2026] - Sistema de Backups:** Se activa Git local y la carpeta `.backups/` como política obligatoria para evitar pérdida accidental de datos.
- **[23/10/2026] - Centralización de Contexto:** Se unificó toda la información de `CONTEXTO_ESP32_C3_SUPERMINI.md` en este archivo maestro, dejando una copia de seguridad en `.backups/`.
- **[23/10/2026] - Idioma oficial:** Español en todos los artefactos, documentación y comentarios.
- **[23/10/2026] - Gestión de Sketches:** Cada hito de domótica tendrá su carpeta dedicada dentro del repositorio para preservar el historial funcional.
