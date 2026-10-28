# Propuesta: Preparación y Adquisición de Hardware para Control de Cargas y Sensores

## Why

El proyecto cuenta actualmente con el servidor web interactivo operativo en simulación (utilizando el LED de usuario de placa y variables en memoria). Para avanzar al **Hito 2 (Control de Cargas Físicas)** y **Hito 3 (Monitorización Ambiental)**, es necesario definir la arquitectura de hardware real, guiar al usuario en la selección y compra de componentes periféricos (módulos de relé, sensores y material de prototipado seguro), y clarificar si requiere adquirir microcontroladores adicionales o si su **ESP32-C3 Super Mini** actual es suficiente.

## What Changes

- **Guía de selección y recomendación de hardware:**
  - Análisis del microcontrolador actual (ESP32-C3 Super Mini) y comparativa con alternativas de desarrollo (ESP32 NodeMCU clásico de 30/38 pines) y comerciales (Shelly / Sonoff).
  - Lista de compra recomendada para control de cargas (módulo relé optoacoplado de 1 o 2 canales compatible con lógica de 3.3V).
  - Material didáctico de prototipado seguro de baja tensión (protoboard, cables Dupont, LEDs y resistencias) para aprender sin riesgo eléctrico de 230V.
  - Selección de sensor ambiental para el siguiente hito (sensor I2C BME280 o DHT22).
- **Asignación de pines seguros en ESP32-C3:** Definición del pin GPIO libre y seguro (GPIO 4 o GPIO 1) para comandar el actuador físico sin interferir con los pines de strapping (`GPIO 9 BOOT`, `GPIO 8 LED`) ni con el puerto USB nativo.
- **Ampliación de especificación:** Se actualiza la especificación de `control-dispositivos` para formalizar el control sobre una salida física externa aislada y la gestión de polaridad (relés activos en bajo `LOW` o alto `HIGH`).

## Capabilities

### New Capabilities
*(Ninguna; se amplían las capacidades de control existentes).*

### Modified Capabilities
- `control-dispositivos`: Se añaden requisitos para el control de actuadores físicos externos, gestión de niveles lógicos de activación y protección por aislamiento galvánico/optoacoplador.

## Impact

- **Hardware requerido:** Módulo de relé optoacoplado, protoboard, cables jumper y componentes de prueba de baja tensión.
- **Firmware:** El sketch `supermini_webserver` se adaptará para conmutar un pin GPIO físico externo junto al testigo virtual.
- **Seguridad:** Cumplimiento de las directrices de `SECURITY.md` y `PROJECT_RULES.md` (aislamiento eléctrico, estado Fail-Safe y pruebas seguras sin manipular 230V directamente en fases iniciales).
