# Directrices del Agente para el Proyecto de Domótica (ESP32-C3 Super Mini)

## 1. Obligación de Lectura y Cumplimiento
En cada interacción de trabajo, el agente DEBE tener en cuenta y aplicar las directrices maestras recogidas en:
- [`PROJECT_RULES.md`](file:///C:/Users/Usuario/Desktop/Cosas_proyectos/Domotica/PROJECT_RULES.md)
- [`SECURITY.md`](file:///C:/Users/Usuario/Desktop/Cosas_proyectos/Domotica/SECURITY.md)

## 2. 🔐 Regla Inviolable de Seguridad: Secretos, APIs y Credenciales (Zero Leaks)
- **PROHIBICIÓN ABSOLUTA:** NUNCA subir claves de API, tokens, contraseñas personales o certificados a Git ni repositorios remotos.
- **Aislamiento en `.gitignore`:** Todo archivo que contenga credenciales, tokens o claves de API (como `secrets.h`, `.env`, `credentials.h`, `api_keys.h`, `service-account.json`, etc.) DEBE estar incluido en `.gitignore` ANTES de crearse o editarse.
- **Uso de plantillas:** En el repositorio solo se permiten plantillas sin datos reales (ej. `secrets.example.h`).
- **Verificación previa a cualquier commit:** Antes de ejecutar `git add` o `git commit`, el agente DEBE comprobar que no se incluya accidentalmente ningún secreto sensible.

## 3. 🛡️ Ciberseguridad y Protección de la Vivienda Real
- **Sin apertura de puertos (No Port Forwarding):** Nunca proponer ni configurar redirección directa de puertos en el router hacia el ESP32. El acceso remoto solo se diseñará mediante conexiones salientes cifradas (TLS / Telegram / VPN).
- **Principio Fail-Safe en Hardware:** Todo actuador (relés, motores, luces) debe inicializarse en estado seguro/apagado por defecto ante reinicios o desconexión.
- **Seguridad en la Web:** Métodos `POST` para cambiar estados de relés/luces; `GET` únicamente para lectura de sensores. Protección contra saturación (rate limiting).
- **Consulta previa obligatoria:** Si el agente considera útil o necesario instalar o descargar cualquier skill, paquete o extensión adicional de OpenSpec o del sistema, **DEBE pedir permiso explícito al usuario antes de proceder**.

## 4. Política Estricta de Backups (Cero Pérdida de Datos)
- **Git:** El repositorio Git local se mantiene actualizado en cada avance relevante.
- **Carpeta `.backups/`:** Antes de eliminar o sobreescribir sustancialmente cualquier archivo existente, el agente DEBE guardar una copia completa en `.backups/`.
- **Prohibición:** NUNCA borrar archivos sin confirmación y sin respaldo previo en `.backups/`.

## 5. Visión del Proyecto y Enfoque
- **Objetivo:** Desarrollo de un sistema de domótica (Smart Home) modular utilizando la placa **ESP32-C3 Super Mini** conectada a la red Wi-Fi doméstica (`MIWIFI_B07C`, IP local `192.168.1.38`).
- **Nivel del Usuario:** Principiante. Explicar todo de forma clara, didáctica, paso a paso, asegurando que entiende cada elemento y advirtiendo sobre seguridad eléctrica en conexiones físicas.
- **Hoja de Ruta:**
  1. Servidor web HTTP interactivo en el ESP32.
  2. Control de cargas físicas (relé / LED externo).
  3. Sensores ambientales (DHT / BME280).
  4. Domótica avanzada (control por voz con Alexa / bot de Telegram).

## 6. Automatización Total del Flujo de OpenSpec
El usuario NO debe escribir comandos de OpenSpec (como `/opsx-propose`, `/opsx-apply`, etc.). El agente debe automatizar el ciclo de vida completo de forma transparente:
1. **Interpretación y Propuesta (`propose`)**:
   - Cada solicitud de nueva funcionalidad o cambio técnico se estructura de inmediato como un cambio en OpenSpec dentro de `openspec/changes/<change-name>/` (con `proposal.md`, `specs/`, y `tasks.md`).
   - Todos los artefactos se generan en **español**.
2. **Implementación (`apply`)**:
   - El agente ejecuta las tareas programadas, crea o edita el código fuente (.ino, .h, .cpp), y valida la compilación con `arduino-cli` usando los parámetros FQBN correctos (`esp32:esp32:esp32c3:CDCOnBoot=cdc,FlashMode=dio`).
   - Se actualizan los estados en `tasks.md`.
3. **Sincronización y Archivo (`archive`)**:
   - Al finalizar el hito con éxito, se sincronizan las especificaciones principales en `openspec/specs/` y se archiva el cambio con `openspec archive <change-name> --yes`.

## 7. Parámetros Técnicos de Compilación y Placa
- **FQBN Obligatorio:** `esp32:esp32:esp32c3:CDCOnBoot=cdc,FlashMode=dio` (imprescindible `CDCOnBoot=cdc` para `Serial.print` por USB nativo).
- **Puerto:** `COM5`.
- **arduino-cli:** `C:\Users\Usuario\AppData\Local\Programs\Arduino IDE\resources\app\lib\backend\resources\arduino-cli.exe`
- **Subida y Arranque:** La placa carece de auto-reset por DTR/RTS; si no arranca tras subir, recordar pulsar botón físico `RST`. Si entra en bootloop, forzar modo descarga manteniendo botón `BOOT` (GPIO 9) al conectar el USB.
