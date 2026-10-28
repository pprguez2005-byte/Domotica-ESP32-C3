# Design: Control de Lámpara de Casa con ESP32 y Relé

## Context

Véase `proposal.md` para la motivación.  
El usuario ha determinado que el primer objetivo físico real de domótica en **Casa Cebollo** será el **control de una lámpara doméstica**.  
Dado que la placa ESP anterior era prestada y el usuario es principiante, este diseño aborda:
1. La lista exacta de componentes a comprar.
2. El funcionamiento del relé electromecánico (`COM`, `NO`, `NC`).
3. El proceso paso a paso de cableado seguro sin riesgo de descarga eléctrica.

---

## Goals / Non-Goals

**Goals:**
- Proporcionar la lista de compra exacta y económica para controlar la lámpara.
- Explicar de forma visual cómo se intercala un relé en el cable de una lámpara tradicional.
- Establecer un protocolo de pruebas seguro en 3 fases: simulación en mesa con LED → prueba del relé en vacío escuchando el "clic" → conexión final de la lámpara en caja aislante.
- Mantener la arquitectura de seguridad establecida en `SECURITY.md` (Fail-Safe apagado por defecto, conmutación por `POST`).

**Non-Goals:**
- Cablear motores de persiana ni abrir cajas de mecanismos empotradas en pared en este primer hito.
- Modificar el sistema eléctrico general de la vivienda (la lámpara es un dispositivo portátil autónomo conectado a enchufe).

---

## Decisions

### 1. ¿Cómo funciona un Relé en el cable de una lámpara?
Una lámpara de casa típica tiene 2 hilos que van al enchufe: **Fase** y **Neutro**:
```text
[Enchufe 230V] ---- Neutro (Azul) --------------------------> [Bombilla Lámpara]
                   Fase (Marrón) -----> [COM]     [NO] ------> [Bombilla Lámpara]
                                          |         |
                                      +-----------------+
                                      |   MÓDULO RELÉ   |
                                      +-----------------+
                                          |    |    |
                                         VCC  GND  IN
                                          |    |    |
                                       [ 5V   GND  GPIO 4 ] -> ESP32
```
- **Neutro (Azul):** Va directo a la lámpara sin cortarse.
- **Fase (Marrón):** Se corta para pasar por los bornes del relé:
  - **`COM` (Común):** Entrada de la fase que viene del enchufe.
  - **`NO` (Normalmente Abierto / Normally Open):** Salida de la fase hacia la bombilla.
  - *Comportamiento:* Mientras el relé esté apagado, el circuito está abierto y no pasa corriente (la lámpara está apagada). Cuando el ESP32 envía la orden al pin `IN`, el relé une `COM` con `NO` y la lámpara se enciende.

### 2. Lista de Compra Recomendada para la Lámpara

| Componente | Qué buscar exactamente | Precio aprox. | Función |
| :--- | :--- | :---: | :--- |
| **Microcontrolador** | **ESP32 NodeMCU (ESP32-WROOM-32 de 30 o 38 pines)** con USB | 3 – 4 € | Cerebro del sistema. Se programa y alimenta directo por USB desde el PC o cargador de móvil. |
| **Actuador** | **Módulo Relé 1 canal 5V con optoacoplador** (trigger configurable o compatible 3.3V) | 1 – 2 € | Interruptor controlado electrónicamente por el ESP32. Soporta hasta 10A / 250V AC. |
| **Prototipado** | **Pack Cables Dupont (Macho-Hembra y Macho-Macho)** + **Protoboard pequeña** | 2 – 3 € | Para conectar los pines del ESP32 al relé de forma rápida sin necesidad de soldar. |
| **Seguridad** | **Cajita de proyectos de plástico o caja de derivación pequeña** (ej. 80x50 mm) | 1 – 2 € | **Fundamental:** Para meter el relé dentro y que ningún cable de 230V quede al aire. |

*Coste total estimado:* Menos de 10 € en total.

### 3. Protocolo de Pruebas Seguro en 3 Fases (Cero Riesgos)

1. **Fase 1 (Mesa de trabajo a 3.3V con LED):**
   - Conectamos un LED con una resistencia de 220 Ω al ESP32.
   - Accedemos a la web en el móvil y verificamos que el botón de "Lámpara" enciende y apaga el LED.
2. **Fase 2 (Prueba del Relé en vacío a 5V, sin 230V):**
   - Conectamos `VCC`, `GND` e `IN` del módulo relé al ESP32.
   - Pulsamos el botón en la web: debemos escuchar un **"clic" metálico** claro del relé y ver cómo se enciende el LED indicador del propio módulo relé.
   - *Ventaja:* Verificamos que el circuito y el código funcionan al 100% sin haber tocado ni un solo voltio peligroso.
3. **Fase 3 (Conexión final de la lámpara en caja aislante):**
   - Desenchufamos la lámpara de la pared.
   - Conectamos la fase a los bornes `COM` y `NO` con los tornillos bien apretados.
   - Cerramos la tapa de la caja plástica antes de volver a enchufar la lámpara a la pared.

---

## Risks / Trade-offs

- **[Tensión de 230V en los bornes del relé]** → **Mitigación:** Prohibir totalmente manipular los bornes con la lámpara enchufada. Alojar siempre el módulo relé en una caja de plástico cerrada.
- **[Señal lógica de 3.3V no activa relé de 5V]** → **Mitigación:** Elegir módulos con optoacoplador o transistor NPN en la entrada `IN` que disparan a partir de 2.0V (compatibles con 3.3V TTL).

---

## Migration Plan

1. El usuario adquiere el ESP32 NodeMCU y el módulo de relé de 1 canal.
2. Dejamos preparado el sketch en `supermini_webserver` adaptado al pin asignado para el relé.
3. Cuando llegue el material, realizamos juntos las pruebas de Fase 1 y Fase 2 antes de la conexión final.
