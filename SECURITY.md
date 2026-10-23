# 🛡️ Política de Seguridad y Privacidad: Domótica ESP32-C3

> **ESTÁNDAR DE SEGURIDAD PARA AUTOMATIZACIÓN DOMÉSTICA REAL**  
> Este proyecto controla dispositivos físicos en una vivienda real. La seguridad cibernética, la privacidad y la integridad física del hogar son prioritarias.

---

## 1. 🌐 Seguridad de Red y Conectividad

### A. Prohibición de Apertura de Puertos (No Port Forwarding / No DMZ)
- **Regla Estricta:** NUNCA abrir puertos directos en el router hacia la IP del ESP32 (`192.168.1.38`). 
- Exponer un microcontrolador directamente a internet mediante redirección de puertos (*port forwarding*) permite que escáneres automáticos de red y bots ataquen la placa o la saturen con ataques de denegación de servicio (DoS).
- **Acceso remoto seguro:**
  - Si en el futuro se requiere control fuera de casa, se implementará a través de **conexiones salientes seguras** (el ESP32 se conecta hacia afuera a un servidor cifrado como Telegram Bot API o SinricPro mediante TLS/HTTPS) o mediante una red privada virtual cifrada doméstica (**WireGuard / Tailscale**).

### B. Segmentación Wi-Fi y Aislamiento
- Se recomienda conectar el ESP32 preferentemente a una red Wi-Fi de invitados o una VLAN de IoT aislada del resto de equipos personales (PCs, móviles con banca electrónica, etc.), si el router lo permite.
- La comunicación local se mantendrá estrictamente contenida en la subred doméstica.

---

## 2. 🔒 Autenticación y Protección del Servidor Web (HTTP/Web)

### A. Control de Acceso y Credenciales
- Los paneles de control web y los endpoints que accionen relés o actuadores deberán contar con mecanismos de autenticación (contraseña de acceso / tokens locales) para evitar que visitas conectadas a la red Wi-Fi puedan accionar dispositivos sin permiso.
- Las contraseñas de acceso al panel web no se almacenarán en texto plano accesible públicamente ni se versionarán en Git.

### B. Verificación de Métodos HTTP
- **GET:** Reservado exclusivamente para lectura de estado y telemetría (consultar temperatura, estado actual del relé, etc.). Nunca una petición `GET` debe modificar el estado de un dispositivo físico.
- **POST:** Obligatorio para cualquier acción que altere el estado físico (encender/apagar luces, conmutar relés). Esto previene ejecuciones accidentales por precarga de enlaces o navegadores.

### C. Prevención contra Inyecciones y DoS Local
- **Rate Limiting (Límite de frecuencia):** El firmware limitará la frecuencia con la que un actuador o relé puede conmutarse para evitar que un bucle malintencionado desgaste los contactos mecánicos del relé o sobrecaliente el circuito.
- **Sanitización de entradas:** Todo parámetro recibido en peticiones HTTP se valida en tamaño y tipo antes de procesarse, evitando desbordamientos de búfer en memoria (*buffer overflow*).

---

## 3. 🔐 Cifrado en Comunicaciones Externas (TLS / HTTPS)

- Cualquier petición hacia servicios externos (APIs cloud, Telegram, asistentes de voz) debe realizarse obligatoriamente mediante canales cifrados utilizando **`WiFiClientSecure`** con TLS 1.2 o superior.
- Queda prohibida la transmisión de datos sensibles en texto plano (HTTP sin cifrar) a través de internet público.

---

## 4. ⚡ Estado Seguro por Defecto y Protección Física (Fail-Safe)

- **Principio Fail-Safe (Fallo Seguro):**
  - Si el ESP32 se reinicia inesperadamente, sufre una caída de tensión o pierde la conexión Wi-Fi, todos los relés y actuadores conectados deben configurarse automáticamente en **estado apagado / seguro** (`LOW` o circuito abierto).
  - Jamás un fallo de software o un reinicio debe dejar un aparato de alta potencia encendido sin control.
- **Protección de Watchdog (WDT):**
  - El procesador mantendrá activo el temporizador de vigilancia (*Watchdog*) para reiniciarse limpiamente en caso de bloqueo, restaurando el hardware a su estado seguro.

---

## 5. 👁️ Privacidad Absoluta de Datos (Zero Telemetry Leak)

- **Datos locales soberanos:** Las lecturas ambientales (temperatura, humedad, horas de actividad o presencia) pertenecen exclusivamente al usuario.
- **Cero telemetría externa:** El firmware no incluye librerías de seguimiento, analíticas de terceros ni telemetría oculta hacia servidores externos.

---

## 6. 🚨 Reporte y Corrección de Vulnerabilidades

Cualquier debilidad detectada en el código o en la configuración de la placa será priorizada de inmediato antes de continuar con la adición de nuevas funcionalidades en la hoja de ruta.
