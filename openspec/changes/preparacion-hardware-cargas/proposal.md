# Propuesta: Domótica Casa Cebollo - Luces y Persiana Motorizada (Hardware y Actuadores)

## Why

El objetivo definitivo del proyecto es automatizar la vivienda **"Casa Cebollo"**, centrándose en dos necesidades reales:
1. **Control de iluminación:** Encender y apagar luces desde la interfaz web/móvil manteniendo la operatividad de los interruptores de pared existentes.
2. **Control de persiana motorizada:** Subir, bajar y detener una persiana con motor tubular de 230V AC, garantizando **interbloqueo mutuo obligatorio** para evitar que las señales de subida y bajada coincidan y quemen el motor.

Dado que la placa ESP previa era prestada, el usuario necesita adquirir su propio hardware y comprender cómo abordar tanto la fase de aprendizaje en mesa de trabajo como la instalación segura en las paredes de la vivienda.

## What Changes

- **Estrategia y selección de compra de hardware para Casa Cebollo:**
  - **Mesa de pruebas / Aprendizaje:** Adquisición de un microcontrolador propio **ESP32 NodeMCU (WROOM-32 de 38 pines)** o **ESP32-C3**, placa de pruebas (protoboard), cables jumper y LEDs de simulación (para simular el giro de subida/bajada y el encendido de luces en baja tensión sin riesgo).
  - **Instalación definitiva en pared (230V):** Recomendación de módulos empotrables certificados (tipo **Shelly Plus 2PM** para la persiana con interbloqueo por hardware, y **Shelly Plus 1 / Sonoff Mini R4** para iluminación), que incorporan procesador ESP32 interno y aislamiento ignífugo.
- **Ampliación de especificación (`control-dispositivos`):**
  - Requisito de **interbloqueo estricto (Mutual Interlock)**: prohibición de activar simultáneamente los relés de subida y bajada de la persiana.
  - Temporización de recorrido y estado de parada para motores de persiana.
  - Soporte para entrada de interruptores/pulsadores físicos de pared.

## Capabilities

### New Capabilities
*(Ninguna; se amplía el dominio de control de dispositivos).*

### Modified Capabilities
- `control-dispositivos`: Se añaden requisitos específicos para el control de motores bidireccionales (persianas motorizadas), temporización de maniobra e interbloqueo de seguridad.

## Impact

- **Hardware:** Selección y compra guiada de componentes DIY de mesa y módulos empotrables para Casa Cebollo.
- **Firmware:** Ampliación del servidor web para incluir botones de "Subir", "Bajar", "Parar" de persiana y control de luces.
- **Seguridad:** Cumplimiento riguroso de `SECURITY.md` (cero riesgo eléctrico en fase de diseño, aislamiento de 230V e interbloqueo físico/lógico).
