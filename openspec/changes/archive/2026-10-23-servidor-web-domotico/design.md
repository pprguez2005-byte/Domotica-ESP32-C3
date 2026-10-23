# Diseño Técnico: Servidor Web Domótico en ESP32-C3

## Contexto (Context)
El ESP32-C3 Super Mini se conecta a la red Wi-Fi `MIWIFI_B07C` y obtiene la IP local `192.168.1.38`. Se requiere levantar un servidor HTTP embebido en el puerto 80 sin saturar la memoria RAM del microcontrolador y respetando las normas de seguridad de `SECURITY.md`.

## Objetivos / No Objetivos (Goals / Non-Goals)

**Objetivos:**
- Servir una interfaz web ligera autocontenida (HTML5 + CSS + Vanilla JS mínimo) almacenada en la memoria flash (PROGMEM).
- Endpoint REST `/api/toggle` con método `POST` y `/api/status` con método `GET`.
- Mapeo de canales:
  - Canal 1: LED de usuario / testigo virtual (GPIO 8 si está disponible, activo en nivel bajo; emulado internamente si la variante carece de LED físico).
  - Canal 2: Canal de Relé de prueba (GPIO 4 configurado en modo seguro *Fail-Safe*).
- Retroalimentación en tiempo real en la pantalla del móvil sin recargar la página entera (usando `fetch` asíncrono en JavaScript).

**No Objetivos:**
- Autenticación compleja con base de datos o cuentas de usuario (se mantiene en red local protegida por router).
- Conexión a internet exterior o asistentes de voz en este hito (reservado a hitos posteriores).
- Almacenamiento SPIFFS/LittleFS en este hito (el HTML se compila directamente en el sketch para máxima simplicidad de compilación y subida sin herramientas adicionales).

## Decisiones Técnicas (Decisions)

1. **Librería de Servidor Web:**
   - *Decisión:* Usar la librería oficial `WebServer.h` incluida en el core de ESP32.
   - *Alternativas consideradas:* `ESPAsyncWebServer`. Se descartó para este primer hito porque requiere librerías externas adicionales (`AsyncTCP`) que complican la instalación a un usuario principiante. `WebServer` estándar es nativa, muy estable y perfectamente adecuada para el tráfico doméstico.
2. **Almacenamiento de la Web en PROGMEM:**
   - *Decisión:* Guardar el código HTML/CSS/JS comprimido como un literal en memoria flash (`const char INDEX_HTML[] PROGMEM = R"rawliteral(...)rawliteral";`).
   - *Razón:* Cero dependencias de particiones de archivos y velocidad de respuesta instantánea.
3. **Seguridad en conmutaciones (POST Only):**
   - *Decisión:* Exigir explícitamente `server.method() == HTTP_POST` para la ruta `/api/toggle`.
   - *Razón:* Cumplir con `SECURITY.md` para evitar conmutaciones accidentales.

## Riesgos y Mitigaciones (Risks / Trade-offs)

- **[Riesgo] Ausencia de LED físico en algunas variantes de ESP32-C3 Super Mini:**
  - *Mitigación:* Se añade telemetría serie por USB a 115200 baudios y actualización visual en la propia web para que el usuario siempre vea el cambio de estado con total certeza.
- **[Riesgo] Cuelgue de conexión Wi-Fi:**
  - *Mitigación:* Comprobación en el bucle principal (`loop()`) para reconectar automáticamente si la señal Wi-Fi cae.
