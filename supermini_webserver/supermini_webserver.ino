#include <WiFi.h>
#include <WebServer.h>
#include "secrets.h"

// ==============================================================================
// CONFIGURACIÓN DE PINES Y PRINCIPIO FAIL-SAFE
// ==============================================================================
// En el ESP32-C3 Super Mini:
// - GPIO 8: LED de usuario (en placas que lo incluyen, activo en nivel LOW).
// - GPIO 4: Pin para futuro módulo relé / carga externa (activo en nivel HIGH).
const int PIN_LED = 8;
const int PIN_RELAY = 4;

// Estados de los canales
bool stateLed = false;
bool stateRelay = false;

// Servidor Web en el puerto 80
WebServer server(80);

// ==============================================================================
// INTERFAZ WEB TÁCTIL (ALMACENADA EN MEMORIA FLASH PROGMEM)
// ==============================================================================
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <title>Domótica ESP32-C3</title>
  <style>
    :root {
      --bg: #0f172a;
      --card: #1e293b;
      --card-border: #334155;
      --text: #f8fafc;
      --text-muted: #94a3b8;
      --primary: #38bdf8;
      --on-color: #22c55e;
      --off-color: #64748b;
    }
    * { box-sizing: border-box; margin: 0; padding: 0; font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif; }
    body { background-color: var(--bg); color: var(--text); padding: 16px; min-height: 100vh; display: flex; flex-direction: column; align-items: center; }
    .container { width: 100%; max-width: 480px; }
    header { text-align: center; margin-bottom: 24px; padding-top: 10px; }
    header h1 { font-size: 1.6rem; color: var(--primary); display: flex; align-items: center; justify-content: center; gap: 8px; }
    header p { font-size: 0.9rem; color: var(--text-muted); margin-top: 4px; }
    .grid { display: flex; flex-direction: column; gap: 16px; margin-bottom: 24px; }
    .card { background: var(--card); border: 1px solid var(--card-border); border-radius: 16px; padding: 18px; display: flex; align-items: center; justify-content: space-between; box-shadow: 0 4px 12px rgba(0,0,0,0.2); }
    .card-info { display: flex; flex-direction: column; gap: 4px; }
    .card-title { font-size: 1.1rem; font-weight: 600; }
    .card-desc { font-size: 0.8rem; color: var(--text-muted); }
    .badge { display: inline-block; padding: 3px 8px; border-radius: 999px; font-size: 0.75rem; font-weight: 700; text-transform: uppercase; margin-top: 4px; width: fit-content; }
    .badge.on { background: rgba(34, 197, 94, 0.2); color: var(--on-color); border: 1px solid var(--on-color); }
    .badge.off { background: rgba(100, 116, 139, 0.2); color: var(--off-color); border: 1px solid var(--off-color); }
    
    /* Botón switch táctil */
    .switch-btn {
      width: 64px;
      height: 36px;
      background: var(--off-color);
      border-radius: 999px;
      border: none;
      outline: none;
      cursor: pointer;
      position: relative;
      transition: background 0.25s ease;
      -webkit-tap-highlight-color: transparent;
    }
    .switch-btn::after {
      content: '';
      position: absolute;
      top: 3px;
      left: 4px;
      width: 30px;
      height: 30px;
      background: #ffffff;
      border-radius: 50%;
      transition: transform 0.25s ease;
      box-shadow: 0 2px 4px rgba(0,0,0,0.3);
    }
    .switch-btn.active {
      background: var(--on-color);
    }
    .switch-btn.active::after {
      transform: translateX(26px);
    }

    /* Telemetría */
    .telemetry { background: rgba(30, 41, 59, 0.5); border: 1px dashed var(--card-border); border-radius: 12px; padding: 14px; font-size: 0.85rem; color: var(--text-muted); }
    .telemetry-row { display: flex; justify-content: space-between; margin-bottom: 6px; }
    .telemetry-row:last-child { margin-bottom: 0; }
    .telemetry-val { color: var(--text); font-weight: 500; font-family: monospace; }
    footer { text-align: center; margin-top: auto; padding: 16px 0 8px; font-size: 0.75rem; color: var(--text-muted); }
  </style>
</head>
<body>
  <div class="container">
    <header>
      <h1>🏠 Domótica ESP32-C3</h1>
      <p>Panel de Control Local Seguro</p>
    </header>

    <div class="grid">
      <!-- Canal 1: Luz / Testigo -->
      <div class="card">
        <div class="card-info">
          <span class="card-title">💡 Luz de Prueba</span>
          <span class="card-desc">LED en placa (GPIO 8)</span>
          <span id="badge-1" class="badge off">Apagado</span>
        </div>
        <button id="btn-1" class="switch-btn" onclick="toggleDevice(1)"></button>
      </div>

      <!-- Canal 2: Simulador Relé -->
      <div class="card">
        <div class="card-info">
          <span class="card-title">🔌 Salida Relé</span>
          <span class="card-desc">Carga física / Enchufe (GPIO 4)</span>
          <span id="badge-2" class="badge off">Inactivo</span>
        </div>
        <button id="btn-2" class="switch-btn" onclick="toggleDevice(2)"></button>
      </div>
    </div>

    <!-- Telemetría -->
    <div class="telemetry">
      <div class="telemetry-row">
        <span>Red Wi-Fi:</span>
        <span id="tel-ssid" class="telemetry-val">--</span>
      </div>
      <div class="telemetry-row">
        <span>Señal (RSSI):</span>
        <span id="tel-rssi" class="telemetry-val">-- dBm</span>
      </div>
      <div class="telemetry-row">
        <span>IP Local:</span>
        <span id="tel-ip" class="telemetry-val">192.168.1.38</span>
      </div>
      <div class="telemetry-row">
        <span>Tiempo activo:</span>
        <span id="tel-uptime" class="telemetry-val">0 s</span>
      </div>
    </div>

    <footer>
      Seguridad IoT activa • POST-only API
    </footer>
  </div>

  <script>
    async function toggleDevice(id) {
      try {
        const response = await fetch('/api/toggle', {
          method: 'POST',
          headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
          body: 'id=' + id
        });
        if (response.ok) {
          const data = await response.json();
          updateUI(data.id, data.state);
        }
      } catch (err) {
        console.error('Error conmutando:', err);
      }
    }

    function updateUI(id, state) {
      const btn = document.getElementById('btn-' + id);
      const badge = document.getElementById('badge-' + id);
      if (state) {
        btn.classList.add('active');
        badge.className = 'badge on';
        badge.textContent = id === 1 ? 'Encendido' : 'Activo';
      } else {
        btn.classList.remove('active');
        badge.className = 'badge off';
        badge.textContent = id === 1 ? 'Apagado' : 'Inactivo';
      }
    }

    async function refreshStatus() {
      try {
        const res = await fetch('/api/status');
        if (res.ok) {
          const data = await res.json();
          updateUI(1, data.ch1);
          updateUI(2, data.ch2);
          document.getElementById('tel-ssid').textContent = data.ssid;
          document.getElementById('tel-rssi').textContent = data.rssi + ' dBm';
          document.getElementById('tel-ip').textContent = data.ip;
          document.getElementById('tel-uptime').textContent = data.uptime + ' s';
        }
      } catch (err) {
        console.warn('Conexión perdida con el ESP32');
      }
    }

    // Actualiza el estado al cargar y cada 3 segundos
    refreshStatus();
    setInterval(refreshStatus, 3000);
  </script>
</body>
</html>
)rawliteral";

// ==============================================================================
// MANEJADORES DE RUTAS DEL SERVIDOR HTTP
// ==============================================================================

// Ruta raíz: Envía el HTML
void handleRoot() {
  server.send(200, "text/html; charset=UTF-8", INDEX_HTML);
}

// Endpoint de conmutación segura (POST Only)
void handleToggle() {
  if (server.method() != HTTP_POST) {
    server.send(405, "application/json", "{\"error\":\"Método no permitido. Solo se acepta POST.\"}");
    return;
  }

  if (!server.hasArg("id")) {
    server.send(400, "application/json", "{\"error\":\"Falta el parámetro id\"}");
    return;
  }

  int id = server.arg("id").toInt();
  bool newState = false;

  if (id == 1) {
    stateLed = !stateLed;
    // En muchas placas el LED integrado es activo a nivel LOW:
    digitalWrite(PIN_LED, stateLed ? LOW : HIGH);
    newState = stateLed;
    Serial.printf("[WEB] Luz de Prueba (Canal 1): %s\n", newState ? "ENCENDIDO" : "APAGADO");
  } else if (id == 2) {
    stateRelay = !stateRelay;
    // El relé físico es activo a nivel HIGH:
    digitalWrite(PIN_RELAY, stateRelay ? HIGH : LOW);
    newState = stateRelay;
    Serial.printf("[WEB] Salida Relé (Canal 2): %s\n", newState ? "ACTIVO" : "INACTIVO");
  } else {
    server.send(400, "application/json", "{\"error\":\"ID de dispositivo desconocido\"}");
    return;
  }

  String json = "{\"success\":true,\"id\":" + String(id) + ",\"state\":" + (newState ? "true" : "false") + "}";
  server.send(200, "application/json", json);
}

// Endpoint de telemetría de lectura (GET)
void handleStatus() {
  int uptimeSeconds = millis() / 1000;
  String json = "{";
  json += "\"ch1\":" + String(stateLed ? "true" : "false") + ",";
  json += "\"ch2\":" + String(stateRelay ? "true" : "false") + ",";
  json += "\"ssid\":\"" + String(WIFI_SSID) + "\",";
  json += "\"rssi\":" + String(WiFi.RSSI()) + ",";
  json += "\"ip\":\"" + WiFi.localIP().toString() + "\",";
  json += "\"uptime\":" + String(uptimeSeconds);
  json += "}";
  server.send(200, "application/json", json);
}

// Manejador de ruta no encontrada
void handleNotFound() {
  server.send(404, "text/plain", "404: Ruta no encontrada en el ESP32");
}

// ==============================================================================
// SETUP Y LOOP
// ==============================================================================

void setup() {
  // Inicialización inmediata de pines en modo seguro Fail-Safe
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_LED, HIGH); // Apagado por defecto (activo LOW)
  digitalWrite(PIN_RELAY, LOW); // Apagado por defecto (activo HIGH)

  Serial.begin(115200);
  delay(1500); // Pausa para puerto USB nativo CDC

  Serial.println("\n=========================================");
  Serial.println("  🏠 ESP32-C3: SERVIDOR WEB DOMÓTICO     ");
  Serial.println("=========================================");
  Serial.println("[SEGURIDAD] Pines configurados en modo Fail-Safe (Apagados).");
  Serial.printf("[WIFI] Conectando a red: %s\n", WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }

  Serial.println("\n[WIFI] ¡Conectado con éxito!");
  Serial.print("[RED] Dirección IP asignada: ");
  Serial.println(WiFi.localIP());
  Serial.printf("[RED] Potencia de señal (RSSI): %d dBm\n", WiFi.RSSI());

  // Registro de rutas HTTP
  server.on("/", HTTP_GET, handleRoot);
  server.on("/api/toggle", HTTP_POST, handleToggle);
  server.on("/api/status", HTTP_GET, handleStatus);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("[HTTP] Servidor Web activo en el puerto 80.");
  Serial.println("-----------------------------------------");
  Serial.printf("👉 Abre en tu móvil o PC: http://%s\n", WiFi.localIP().toString().c_str());
  Serial.println("=========================================\n");
}

void loop() {
  server.handleClient();

  // Control de reconexión Wi-Fi automática
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 10000) {
    lastCheck = millis();
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("[WIFI] Pérdida de conexión. Reconectando...");
      WiFi.reconnect();
    }
  }
}
