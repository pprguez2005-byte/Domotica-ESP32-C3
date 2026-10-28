# Design: Domótica Casa Cebollo - Luces y Persiana Motorizada

## Context

Véase `proposal.md` para la motivación.  
El usuario desea domotizar la vivienda real **"Casa Cebollo"** con dos objetivos fundamentales:
1. **Control de luces.**
2. **Control de una persiana motorizada.**

Dado que la placa ESP previa era prestada, se debe definir el hardware a adquirir y el método constructivo adecuado para un usuario principiante, priorizando la máxima seguridad eléctrica en una vivienda habitada.

---

## Goals / Non-Goals

**Goals:**
- Establecer la arquitectura para controlar luces y persiana motorizada con total seguridad.
- Diseñar el mecanismo de **interbloqueo de seguridad** para el motor de la persiana (imposibilidad física/lógica de alimentar subida y bajada al mismo tiempo).
- Brindar una recomendación de compra clara: kit de aprendizaje en mesa de pruebas (baja tensión) y módulos certificados para la instalación en pared de Casa Cebollo.
- Mantener la operatividad de los interruptores de pared físicos existentes (siempre funcionales aunque caiga la Wi-Fi).

**Non-Goals:**
- Conectar componentes DIY al descubierto a la red eléctrica de 230V sin aislamiento adecuado o caja ignífuga.
- Motores de persiana por radiofrecuencia (RF 433 MHz) con mandos propietarios cerrados (el diseño se centra en motores tubulares estándar de 4 cables).

---

## Decisions

### 1. Anatomía y Conexión de una Persiana Motorizada Estándar (230V)
Un motor tubular de persiana estándar cuenta con **4 cables**:
```text
           +-------------------------------------+
           |      Motor Tubular de Persiana      |
           +-------------------------------------+
                  |           |          |          |
            [Amarillo/Verde] [Azul]   [Marrón]   [Negro]
                  |           |          |          |
                Tierra      Neutro     Fase 1     Fase 2
                 (GND)        (N)     (SUBIR)    (BAJAR)
```
- **Azul (Neutro):** Va conectado directo al neutro general de la instalación eléctrica.
- **Amarillo/Verde (Tierra):** Protección a la toma de tierra del edificio.
- **Marrón y Negro (Fases de giro):**
  - Si recibe corriente el cable Marrón → El motor gira en sentido SUBIDA.
  - Si recibe corriente el cable Negro → El motor gira en sentido BAJADA.
  - ⚠️ **REGLA CRÍTICA (Interbloqueo):** Si reciben corriente ambos cables simultáneamente, los bobinados entran en conflicto y el motor se quema en segundos.

### 2. Estrategia de Hardware: Recomendación de Compra para Casa Cebollo

Para garantizar una experiencia formativa sin poner en riesgo la instalación de la vivienda, se adopta una **estrategia en 2 fases**:

#### Fase 1: Banco de Pruebas y Aprendizaje en Mesa (Baja Tensión 5V/3.3V)
Permite al usuario desarrollar la lógica, simular la persiana con LEDs y probar el servidor web sin tocar 230V:
- **Microcontrolador propio:** **ESP32 NodeMCU (ESP32-WROOM-32 de 30 o 38 pines)** (~3-4 €).
  - *Ventaja:* Conversor USB integrado, conexión fácil por USB al PC, auto-reset directo.
- **Kit de prototipado:** 1x Protoboard de 400 u 830 puntos, cables jumper Dupont, 4x LEDs (2 para simular luces, 1 LED verde para "subir persiana", 1 LED rojo para "bajar persiana") y resistencias de 220 Ω / 330 Ω.
- **Opcional para pruebas:** Módulo de relé de 2 o 4 canales optoacoplado de 5V (nivel lógico 3.3V).

#### Fase 2: Instalación Definitiva en la Pared de Casa Cebollo (Máxima Seguridad 230V)
Para empotrar dentro de las cajas de mecanismos de la pared de la vivienda, el método más seguro y profesional para principiantes es usar **módulos inteligentes basados en ESP32 con marcado CE**:
- **Para la persiana:** **Shelly Plus 2PM** (o Sonoff Dual R3) (~20-25 €).
  - *Por qué:* Incorpora un chip ESP32 en su interior, cabe detrás del pulsador de persiana de la pared, tiene **interbloqueo por hardware integrado**, protección térmica, medición de consumo y calibración precisa de recorrido (0-100%).
  - Mantiene conectados los dos pulsadores físicos de la pared (flecha arriba / flecha abajo).
- **Para las luces:** **Shelly Plus 1** o **Sonoff Mini R4** (~10-14 € por circuito).
  - *Por qué:* Se conecta en serie con el interruptor de pared actual. Permite encender desde la pared o desde el móvil de forma combinada.

---

## Risks / Trade-offs

- **[Cruce de fases en motor de persiana]** → **Mitigación:** En software, implementar máquina de estados con tiempo muerto de 200 ms entre cambio de sentido y validación cruzada. En hardware real, utilizar módulos con interbloqueo físico (relé SPDT o Shelly Plus 2PM).
- **[Pérdida de control si se cae la red Wi-Fi o falla el micro]** → **Mitigación:** Cablear siempre los pulsadores e interruptores físicos existentes a las entradas de conmutación de los actuadores (Fail-Operational local).
- **[Riesgo de electrocución o incendio en empotrados]** → **Mitigación:** Prohibir el uso de protoboards o placas al aire conectadas a 230V dentro de las paredes de Casa Cebollo; emplear módulos con caja aislante ignífuga certificada.

---

## Migration Plan

1. El usuario adquiere el kit de mesa (ESP32 NodeMCU + protoboard + LEDs) para verificar la programación y la interfaz web con total seguridad.
2. Se programa en el firmware la interfaz web completa para Casa Cebollo:
   - Interruptores de Luces (ON/OFF).
   - Control de Persiana (Subir / Bajar / Parar).
3. Una vez validada la lógica en mesa, se procede a la adquisición y conexionado de los módulos empotrables definitivos en la vivienda.
