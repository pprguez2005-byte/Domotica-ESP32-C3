# Delta de Especificación: Control de Dispositivos y Cargas

## Purpose
Gestiona la lógica de estado, conmutación física y principio de fallo seguro (Fail-Safe) para actuadores y testigos en el ESP32-C3.

## ADDED Requirements

### Requirement: Inicialización en Estado Seguro (Fail-Safe)
El microcontrolador DEBE (SHALL) inicializar todos los pines de control físico en estado seguro / inactivo tras cualquier reinicio o caída de alimentación eléctrica.

#### Scenario: Arranque o reinicio del microcontrolador
- **WHEN** el ESP32-C3 inicia o se reinicia por corte de corriente o watchdog
- **THEN** los pines GPIO asociados a cargas o relés se configuran inmediatamente en estado inactivo / apagado antes de inicializar la red Wi-Fi

### Requirement: Conmutación de Canales de Dispositivo
El sistema DEBE (SHALL) permitir conmutar el estado lógico de cada canal registrado y reflejar el cambio en su salida física y en la memoria del sistema.

#### Scenario: Cambio de estado de un canal
- **WHEN** se solicita conmutar el canal de "Luz" o "Relé"
- **THEN** el sistema invierte su estado (de apagado a encendido o viceversa) y actualiza el nivel de la salida asociada
