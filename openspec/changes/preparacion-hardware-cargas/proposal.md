# Propuesta: Control de Lámpara de Casa con ESP32 y Relé (Primer Hito Físico)

## Why

Para iniciar la domotización práctica de **"Casa Cebollo"** de forma segura y accesible para un usuario principiante, se selecciona como primer dispositivo real una **lámpara doméstica**. Este objetivo permite validar el ciclo completo (servidor web, conmutación física, aislamiento y principio Fail-Safe) sin la complejidad mecánica de una persiana ni la necesidad de abrir cajas de pared en una primera toma de contacto.

Dado que la placa previa era prestada, se orienta al usuario en la compra de su propio microcontrolador (ESP32) y del módulo de relé adecuado para gobernar la lámpara.

## What Changes

- **Definición del hardware específico a adquirir para la lámpara:**
  - Microcontrolador propio: **ESP32 NodeMCU (ESP32-WROOM-32)** por facilidad de conexión USB y autoreset.
  - Actuador: **Módulo de relé de 1 canal optoacoplado (5V VCC, señal lógica 3.3V)**.
  - Accesorios de conexión y seguridad: Cables jumper Dupont, protoboard para pruebas y caja plástica aislante para alojar el relé a 230V.
- **Estrategia de conexión de la lámpara en 3 fases progresivas:**
  1. *Fase 1 (Mesa - Baja tensión):* Simulación en protoboard con LED testigo.
  2. *Fase 2 (Verificación de relé en vacío):* Escucha del "clic" mecánico y LED de estado del módulo relé a 5V/3.3V sin conectar aún los 230V de la lámpara.
  3. *Fase 3 (Conexión segura de la lámpara):* Interrupción de fase en bornes `COM` y `NO` del relé con caja protectora.
- **Ajuste de especificación (`control-dispositivos`):**
  - Requisito de control de canal de lámpara mediante salida digital con estado Fail-Safe (lámpara apagada por defecto tras reinicio o pérdida de red).

## Capabilities

### New Capabilities
*(Ninguna; se concreta el dominio de control de actuadores).*

### Modified Capabilities
- `control-dispositivos`: Se formaliza la conmutación de carga monomodo (lámpara) mediante relé optoacoplado y polaridad segura.

## Impact

- **Hardware:** Compra de 1x ESP32 NodeMCU, 1x módulo relé de 1 canal, protoboard y cables.
- **Firmware:** Adaptación del sketch para asociar el botón de la lámpara del servidor web al pin GPIO físico de control.
- **Seguridad:** Aislamiento eléctrico completo y protección de 230V encapsulada en caja aislante.
