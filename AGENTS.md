# Directrices del Agente para el Proyecto de Domótica (ESP32-C3 Super Mini)

## 1. Obligación de Lectura y Cumplimiento
En cada interacción de trabajo, el agente DEBE tener en cuenta y aplicar las directrices maestras recogidas en:
- [`PROJECT_RULES.md`](file:///C:/Users/Usuario/Desktop/Cosas_proyectos/Domotica/PROJECT_RULES.md)

## 2. Visión del Proyecto y Enfoque
- **Objetivo:** Desarrollo de un sistema de domótica (Smart Home) modular utilizando la placa **ESP32-C3 Super Mini** conectada a la red Wi-Fi doméstica (`MIWIFI_B07C`, IP local `192.168.1.38`).
- **Nivel del Usuario:** Principiante. Explicar todo de forma clara, didáctica, paso a paso, asegurando que entiende cada elemento y advirtiendo sobre seguridad eléctrica en conexiones físicas.
- **Hoja de Ruta:**
  1. Servidor web HTTP interactivo en el ESP32.
  2. Control de cargas físicas (relé / LED externo).
  3. Sensores ambientales (DHT / BME280).
  4. Domótica avanzada (control por voz con Alexa / bot de Telegram).

## 3. Automatización Total del Flujo de OpenSpec
El usuario NO debe escribir comandos de OpenSpec (como `/opsx-propose`, `/opsx-apply`, etc.). El agente debe automatizar el ciclo de vida completo de forma transparente:
1. **Interpretación y Propuesta (`propose`)**:
   - Cada solicitud de nueva funcionalidad o cambio técnico se estructura de inmediato como un cambio en OpenSpec dentro de `openspec/changes/<change-name>/` (con `proposal.md`, `specs/`, y `tasks.md`).
   - Todos los artefactos se generan en **español**.
2. **Implementación (`apply`)**:
   - El agente ejecuta las tareas programadas, crea o edita el código fuente (.ino, .h, .cpp), y valida la compilación con `arduino-cli` usando los parámetros FQBN correctos (`esp32:esp32:esp32c3:CDCOnBoot=cdc,FlashMode=dio`).
   - Se actualizan los estados en `tasks.md`.
3. **Sincronización y Archivo (`archive`)**:
   - Al finalizar el hito con éxito, se sincronizan las especificaciones principales en `openspec/specs/` y se archiva el cambio con `openspec archive <change-name> --yes`.

## 4. Parámetros Técnicos de Compilación y Placa
- **FQBN Obligatorio:** `esp32:esp32:esp32c3:CDCOnBoot=cdc,FlashMode=dio` (imprescindible `CDCOnBoot=cdc` para `Serial.print` por USB nativo).
- **Puerto:** `COM5`.
- **arduino-cli:** `C:\Users\Usuario\AppData\Local\Programs\Arduino IDE\resources\app\lib\backend\resources\arduino-cli.exe`
- **Subida y Arranque:** La placa carece de auto-reset por DTR/RTS; si no arranca tras subir, recordar pulsar botón físico `RST`. Si entra en bootloop, forzar modo descarga manteniendo botón `BOOT` (GPIO 9) al conectar el USB.
