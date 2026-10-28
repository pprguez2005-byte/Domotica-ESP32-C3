# Spec Delta: control-dispositivos

## ADDED Requirements

### Requirement: Control de Salida Física Externa Aislada
El microcontrolador DEBE (SHALL) emitir la señal de conmutación a través de un pin GPIO dedicado (como GPIO 4 o GPIO 1) configurado como salida digital para controlar un módulo actuador externo o relé optoacoplado con nivel lógico compatible de 3.3V.

#### Scenario: Activación de actuador externo
- **WHEN** se recibe la orden de encendido para la carga física
- **THEN** el pin GPIO dedicado conmuta al estado lógico activo requerido por el módulo externo

#### Scenario: Desactivación de actuador externo
- **WHEN** se recibe la orden de apagado para la carga física
- **THEN** el pin GPIO dedicado conmuta al estado lógico inactivo manteniendo la carga apagada

### Requirement: Gestión de Polaridad e Inversión de Nivel Lógico
El sistema DEBE (SHALL) permitir definir la polaridad de activación de la carga (nivel activo en ALTO o BAJO) garantizando que el estado de reposo mantenga siempre el circuito del actuador completamente abierto.

#### Scenario: Configuración de módulo de relé activo en nivel bajo
- **WHEN** se utiliza un módulo relé cuya bobina se activa con nivel lógico LOW
- **THEN** el firmware establece el pin en nivel HIGH durante el reposo o reinicio para asegurar que permanezca desactivado
