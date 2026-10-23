# Tasks: Servidor Web Domótico en ESP32-C3

## 1. Estructura y Código del Servidor

- [x] 1.1 Crear la carpeta `supermini_webserver` y el archivo `supermini_webserver.ino` con la conexión a `MIWIFI_B07C`, el servidor HTTP nativo y la interfaz web táctil responsiva.
- [x] 1.2 Implementar los endpoints seguros `/api/toggle` (solo método POST) y `/api/status` (método GET) con estado Fail-Safe en GPIOs.

## 2. Compilación y Flasheo

- [x] 2.1 Compilar el sketch con `arduino-cli` utilizando el FQBN `esp32:esp32:esp32c3:CDCOnBoot=cdc,FlashMode=dio` y verificar salida sin errores.
- [x] 2.2 Subir el binario al ESP32-C3 en el puerto `COM5` con `arduino-cli upload` y verificar que arranca en la red local.

## 3. Verificación de Funcionamiento

- [x] 3.1 Conectar al panel web desde el navegador en `http://192.168.1.38` y verificar que los botones conmutan el estado y muestran respuesta visual en tiempo real.
