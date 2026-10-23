# servidor-web Specification

## Purpose
Proporciona un servicio HTTP local en el puerto 80 para despachar la interfaz gráfica de usuario y gestionar peticiones web en el ESP32-C3.

## Requirements

### Requirement: Despacho de Interfaz Web Táctil
El sistema DEBE (SHALL) responder en la ruta raíz (`/`) con una página HTML5 responsiva, adaptada a teléfonos móviles y navegadores de escritorio, que muestre el estado de los dispositivos y controles interactivos.

#### Scenario: Acceso desde el navegador móvil
- **WHEN** un usuario en la red local abre `http://192.168.1.38/` en su navegador
- **THEN** el servidor responde con código 200 y el documento HTML con los botones de control y el estado actual de los dispositivos

### Requirement: Seguridad en Peticiones de Acción (POST Only)
El sistema DEBE (SHALL) rechazar peticiones `GET` en las rutas de cambio de estado y DEBE aceptar únicamente peticiones `POST` para conmutar actuadores.

#### Scenario: Intento de conmutación mediante GET
- **WHEN** un cliente envía una petición `GET` a `/api/toggle`
- **THEN** el sistema responde con error 405 Method Not Allowed sin alterar ningún dispositivo

#### Scenario: Conmutación autorizada mediante POST
- **WHEN** el cliente envía una petición `POST` a `/api/toggle` indicando el identificador del dispositivo
- **THEN** el sistema procesa la conmutación y responde con código 200 y el nuevo estado en formato JSON

### Requirement: Consulta de Telemetría Local
El sistema DEBE (SHALL) ofrecer un endpoint de solo lectura para consultar la telemetría del microcontrolador (potencia de señal Wi-Fi, memoria libre y tiempo de actividad).

#### Scenario: Petición de telemetría por GET
- **WHEN** un cliente consulta la ruta `/api/status` mediante `GET`
- **THEN** el sistema devuelve un objeto JSON con el RSSI de la red, la IP asignada y el estado de los canales
