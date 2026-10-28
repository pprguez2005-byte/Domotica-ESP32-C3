# Design: Preparación y Adquisición de Hardware para el Proyecto de Domótica

## Context

Véase `proposal.md` para la motivación.  
El proyecto dispone de un microcontrolador **ESP32-C3 Super Mini** con Wi-Fi, Bluetooth LE y un servidor web funcional en `http://192.168.1.38`. Actualmente conmuta únicamente un LED en placa y un estado virtual. Para implementar el **Hito 2 (Control de Cargas Físicas)** y el **Hito 3 (Sensores Ambientales)**, el usuario necesita saber qué microcontroladores o componentes periféricos adquirir, cómo conectarlos con seguridad y cómo evitar riesgos eléctricos o daños por sobretensión en los pines GPIO.

---

## Goals / Non-Goals

**Goals:**
- Determinar si el microcontrolador actual (ESP32-C3 Super Mini) es suficiente para el proyecto y presentar opciones de microcontroladores adicionales si desea ampliar o trabajar con más comodidad.
- Definir la lista de compra exacta de componentes periféricos (módulo relé, material de prototipado seguro y sensores ambientales).
- Diseñar la asignación de pines GPIO seguros en el ESP32-C3 Super Mini evitando pines conflictivos (strapping pins y USB).
- Establecer un procedimiento de aprendizaje seguro en baja tensión (LEDs y resistencias de 3.3V/5V) antes de conmutar cargas de 230V en la vivienda.

**Non-Goals:**
- Manipular o cablear directamente la red de 230V de la vivienda en esta etapa inicial.
- Modificar el protocolo de red ni la API HTTP implementada en el Hito 1.

---

## Decisions

### 1. Evaluación del Microcontrolador: ¿Comprar otro o usar el actual?
- **Decisión:** Mantener el **ESP32-C3 Super Mini actual como microcontrolador principal** para este proyecto, ya que tiene potencia y memoria sobradas (CPU RISC-V 160MHz, 4MB Flash, Wi-Fi 2.4GHz) y suficientes pines libres para 1-2 relés y un bus de sensores I2C.
- **Microcontroladores recomendados en caso de querer comprar unidades adicionales:**
  1. **ESP32 NodeMCU clásico (ESP32-WROOM-32 de 30 o 38 pines) [Recomendado para mesa de pruebas]:**
     - *Por qué:* Cuenta con chip conversor USB-UART integrado (CP2102 o CH340), circuito de autoreset automático (no requiere pulsar botones `BOOT` o `RST` manualmente para programar), decenas de pines accesibles y formato muy amigable para protoboard. Precio muy bajo (~3-4 €).
  2. **ESP32-C3 Super Mini (Unidades extra) [Recomendado para instalación oculta]:**
     - *Por qué:* Tamaño hipercompacto (~20 x 17 mm). Ideal para ocultar dentro de cajas de mecanismos de pared, cajas de derivación o plafones de luz. Precio: ~2-3 €.
  3. **Módulos comerciales "Smart" basados en ESP (Shelly Plus 1 o Sonoff Mini R4):**
     - *Por qué:* Vienen con caja ignífuga certificada CE, relé de 16A y fuente conmutada de 230V interna. Son la opción más segura si más adelante no se quiere soldar ni manipular cables de 230V al descubierto.

### 2. Lista de Compra de Componentes Periféricos Necesarios (Hito 2 y 3)
Para realizar físicamente el proyecto se recomienda adquirir:
1. **Actuador (Hito 2): Módulo de Relé de 1 canal (o 2 canales) con Optoacoplador:**
   - Debe funcionar con alimentación de 5V pero admitir señal de disparo (IN) a nivel lógico de **3.3V** (compatible con ESP32).
   - Optoacoplado: el aislamiento óptico protege el microcontrolador de picos de inducción magnética generados por la bobina del relé.
2. **Kit de Prototipado Seguro (Baja Tensión):**
   - 1x Placa de pruebas pequeña/mediana (*Breadboard / Protoboard* de 400 o 830 puntos).
   - 1x Paquete de cables Jumper Dupont (combinación de Macho-Macho, Macho-Hembra y Hembra-Hembra).
   - 4x LEDs de 5 mm (rojos, verdes o amarillos) y 4x resistencias de 220 Ω o 330 Ω (para simular el encendido de bombillas a 3.3V sin riesgo alguno).
3. **Sensor Ambiental (Hito 3):**
   - **Opción A (Recomendada): Sensor BME280 (I2C):** Mide con gran precisión Temperatura, Humedad relativa y Presión barométrica usando solo 2 cables de datos (`SDA` y `SCL`).
   - **Opción B (Económica): Sensor DHT22 / AM2302:** Mide temperatura y humedad con 1 cable de datos (protocolo unifilar).

### 3. Asignación de Pines Seguros en ESP32-C3 Super Mini
El ESP32-C3 Super Mini tiene un número reducido de pines y algunos están comprometidos:
- **Pines a evitar para relés:**
  - `GPIO 9`: Botón físico `BOOT` (debe estar en nivel alto durante el arranque normal).
  - `GPIO 8`: LED integrado en placa y pin de strapping.
  - `GPIO 18` / `GPIO 19`: Bus de datos USB D- / D+.
- **Pines recomendados para el Hito 2 (Relé/Carga):**
  - **`GPIO 4`** o **`GPIO 1`**: Pines de entrada/salida de propósito general limpios, sin pull-ups conflictivos en arranque.
- **Pines recomendados para el Hito 3 (Bus I2C para BME280):**
  - **`GPIO 6`** (`SDA`) y **`GPIO 7`** (`SCL`) o reasignables por software.

---

## Risks / Trade-offs

- **[Riesgo de electrocución con 230V AC]** → **Mitigación:** Seguir una estrategia de dos fases. Primero validar todo el circuito con LEDs y resistencias a 3.3V/5V en la protoboard. Solo conectar a aparatos reales de red tras dominar la lógica y con supervisión/módulos con aislamiento adecuado.
- **[Bobina de relé no disparada por 3.3V]** → **Mitigación:** Seleccionar módulos de relé que incorporen transistor/optoacoplador en la entrada `IN` diseñado para disparar con 3.3V (común en módulos de Arduino/ESP32).
- **[Pico de corriente inductiva (Flyback) al apagar relé]** → **Mitigación:** Usar módulos comerciales de relé que ya incluyen diodo de protección en paralelo con la bobina.

---

## Migration Plan

1. El usuario revisa las recomendaciones de compra y adquiere los elementos de prototipado y actuadores.
2. Mientras se reciben los componentes, se puede adaptar el código de `supermini_webserver` para direccionar el pin físico seleccionado (`GPIO 4`), de forma que el firmware esté listo cuando llegue el hardware.
