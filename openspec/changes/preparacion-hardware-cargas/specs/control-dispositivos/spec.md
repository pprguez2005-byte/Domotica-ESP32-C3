# Spec Delta: control-dispositivos

## ADDED Requirements

### Requirement: Control de Salida Física Externa Aislada
El microcontrolador DEBE (SHALL) emitir la señal de conmutación a través de un pin GPIO dedicado configurado como salida digital para controlar módulos actuadores externos de luz o relés optoacoplados con nivel lógico compatible de 3.3V.

#### Scenario: Activación de canal de iluminación
- **WHEN** se recibe la orden de encendido de luz desde la web o el pulsador
- **THEN** el pin GPIO dedicado conmuta al estado activo cerrando el circuito de iluminación

#### Scenario: Desactivación de canal de iluminación
- **WHEN** se recibe la orden de apagado de luz
- **THEN** el pin GPIO conmuta al estado inactivo abriendo el circuito de iluminación

### Requirement: Interbloqueo Mutuo en Motores de Persiana (Mutual Interlock)
El sistema DEBE (SHALL) asegurar que las salidas de Subida y Bajada de una persiana motorizada sean mutuamente excluyentes en todo momento, impidiendo bajo cualquier circunstancia que ambas reciban alimentación simultánea para evitar la destrucción del motor tubular.

#### Scenario: Intento de activación simultánea de subida y bajada
- **WHEN** se solicita la maniobra de bajada mientras la persiana está subiendo
- **THEN** el sistema desactiva inmediatamente la salida de subida, aplica una pausa de seguridad mínima de 200 ms y posteriormente activa la salida de bajada

#### Scenario: Inicialización segura de persiana
- **WHEN** el microcontrolador se reinicia o restablece tras un corte de alimentación
- **THEN** ambas salidas de subida y bajada permanecen en estado inactivo garantizando reposo absoluto del motor

### Requirement: Temporización y Parada de Maniobra de Persiana
El sistema DEBE (SHALL) permitir detener manualmente la marcha del motor en cualquier momento y cortar automáticamente la alimentación tras expirar el tiempo máximo de carrera de la persiana para proteger los finales de carrera del motor.

#### Scenario: Detención manual en curso
- **WHEN** el usuario pulsa la acción de Parar mientras la persiana está en movimiento
- **THEN** la salida activa se desactiva de inmediato deteniendo la persiana en su posición actual

#### Scenario: Fin de carrera por tiempo
- **WHEN** la maniobra de subida o bajada alcanza el tiempo límite configurado (ej. 25 segundos)
- **THEN** el firmware desenergiza la salida del motor de forma preventiva
