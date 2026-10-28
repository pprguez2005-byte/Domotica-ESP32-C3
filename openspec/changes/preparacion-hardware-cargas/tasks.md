# Tasks: Control de Lámpara de Casa con ESP32 y Relé

## 1. Definición y Adquisición de Componentes

- [ ] 1.1 Documentar la lista de compra detallada para la lámpara (ESP32 NodeMCU, módulo relé 1 canal 5V optoacoplado, cables Dupont y caja aislante) y verificar la elección de componentes con el usuario.
- [ ] 1.2 Elaborar la guía visual de conexionado de la lámpara a los bornes `COM` y `NO` del relé respetando el aislamiento del neutro.

## 2. Preparación y Compilación del Firmware

- [ ] 2.1 Actualizar el sketch del servidor web para asignar un pin GPIO físico dedicado (ej. `GPIO 4` o `GPIO 23`) a la "Lámpara de Casa" con inicialización Fail-Safe (apagada por defecto).
- [ ] 2.2 Compilar el firmware con `arduino-cli` verificando que no existan errores ni advertencias.

## 3. Verificación Progresiva por Fases

- [ ] 3.1 Probar la conmutación en mesa mediante LED y resistencia de prueba al pulsar el botón web desde el navegador.
- [ ] 3.2 Conectar el módulo relé en vacío al ESP32 (sin conectar a 230V) y verificar la activación auditiva del "clic" mecánico y su LED indicador.
- [ ] 3.3 Realizar el montaje final de la lámpara dentro de la caja de protección plástica y verificar el control completo desde el móvil.

## Workflow follow-up

- Sincronizar las especificaciones con `openspec sync-specs` o archivar el cambio cuando la lámpara funcione satisfactoriamente.
