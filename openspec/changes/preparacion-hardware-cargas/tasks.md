# Tasks: Preparación y Adquisición de Hardware para Control de Cargas

## 1. Definición de la Lista de Adquisición y Arquitectura de Conexión

- [ ] 1.1 Documentar la lista de compra de componentes recomendados (módulo relé optoacoplado de 3.3V/5V, protoboard, cables jumper, LEDs de prueba y sensor BME280) y verificar la comprensión de los requerimientos por el usuario.
- [ ] 1.2 Elaborar el diagrama esquemático de conexiones en baja tensión (ESP32-C3 Super Mini + LED/Resistencia en protoboard + módulo relé) indicando la asignación al pin seguro `GPIO 4`.

## 2. Preparación y Validación del Firmware para Actuación Física

- [ ] 2.1 Actualizar el sketch `supermini_webserver.ino` para inicializar y conmutar el pin `GPIO 4` junto con la lógica Fail-Safe (modo seguro apagado por defecto) y soporte para polaridad invertible.
- [ ] 2.2 Compilar el firmware con `arduino-cli` utilizando el FQBN `esp32:esp32:esp32c3:CDCOnBoot=cdc,FlashMode=dio` y verificar que no existen errores ni advertencias de compilación.

## 3. Pruebas de Funcionamiento y Verificación de Estado

- [ ] 3.1 Flashear el firmware en el ESP32-C3 Super Mini por el puerto `COM5` y verificar mediante un polímetro o LED externo en el pin `GPIO 4` que el voltaje conmuta entre 0V y 3.3V al pulsar los botones del servidor web.

## Workflow follow-up

- Sincronizar las especificaciones con `openspec sync-specs` o archivar el cambio cuando los componentes estén montados y validados.
