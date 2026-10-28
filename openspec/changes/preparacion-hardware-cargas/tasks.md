# Tasks: Domótica Casa Cebollo - Luces y Persiana Motorizada

## 1. Planificación y Selección de Hardware

- [ ] 1.1 Documentar la lista de compra detallada para Casa Cebollo distinguiendo entre el kit de aprendizaje en mesa (ESP32 propio + protoboard + LEDs) y los módulos de instalación definitiva (Shelly Plus 2PM para persiana y Shelly Plus 1 para luces).
- [ ] 1.2 Diseñar el diagrama de conexionado del motor de persiana de 4 cables (Neutro, Tierra, Fase Subir, Fase Bajar) detallando la lógica de interbloqueo obligatorio.

## 2. Desarrollo del Firmware de Simulación para Casa Cebollo

- [ ] 2.1 Implementar en el servidor web los controles para luces y persiana (botones virtuales Subir, Bajar, Parar y tiempo máximo de maniobra).
- [ ] 2.2 Implementar en el código la máquina de estados con interbloqueo estricto (garantizando que las salidas de subida y bajada nunca se activen simultáneamente).
- [ ] 2.3 Compilar el sketch con `arduino-cli` verificando que no existan errores ni advertencias.

## 3. Verificación de Funcionamiento en Mesa

- [ ] 3.1 Probar en la interfaz web la conmutación de luces y la secuencia de la persiana con LEDs de prueba (LED verde para subir, LED rojo para bajar).
- [ ] 3.2 Verificar que pulsar "Bajar" mientras está "Subiendo" detiene primero la subida antes de iniciar la bajada (prueba de estrés de interbloqueo).

## Workflow follow-up

- Sincronizar las especificaciones con `openspec sync-specs` o archivar el cambio cuando la simulación de luces y persiana esté validada.
