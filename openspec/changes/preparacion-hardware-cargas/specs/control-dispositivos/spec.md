# Spec Delta: control-dispositivos

## ADDED Requirements

### Requirement: Control de Conmutación de Lámpara por Relé Físico
El microcontrolador DEBE (SHALL) controlar el encendido y apagado de la lámpara conmutando un pin GPIO de salida conectado a la entrada de control (IN) del módulo de relé optoacoplado.

#### Scenario: Encendido de la lámpara
- **WHEN** se envía la orden de encendido de la lámpara desde la interfaz web o API POST
- **THEN** el pin GPIO conmuta al nivel lógico que activa la bobina del relé cerrando el circuito de 230V de la lámpara

#### Scenario: Apagado de la lámpara
- **WHEN** se envía la orden de apagado de la lámpara
- **THEN** el pin GPIO conmuta al nivel lógico inactivo abriendo el circuito de 230V y cortando la corriente hacia la lámpara

### Requirement: Protección Fail-Safe y Polaridad de Reposo
El firmware DEBE (SHALL) garantizar que tras cualquier reinicio, corte de corriente o pérdida de Wi-Fi, el estado por defecto del relé mantenga el circuito de la lámpara abierto e inactivo.

#### Scenario: Arranque de seguridad
- **WHEN** el microcontrolador se enciende o reinicia por watchdog
- **THEN** el pin GPIO se configura inmediatamente en el nivel de reposo del módulo relé asegurando que la lámpara permanezca apagada

#### Scenario: Conmutación con relé activo en nivel bajo
- **WHEN** se conecta un módulo de relé cuya activación ocurre con nivel lógico LOW
- **THEN** el firmware establece el pin GPIO en HIGH durante el estado inactivo para impedir el encendido no deseado
