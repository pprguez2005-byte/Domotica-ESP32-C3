# 🏠 Sistema de Domótica con ESP32-C3 Super Mini

Proyecto de domótica modular para el hogar desarrollado sobre el microcontrolador **ESP32-C3 Super Mini**, orientado a un desarrollo guiado paso a paso con especificaciones asistidas por IA ([OpenSpec](https://github.com/Fission-AI/OpenSpec)).

---

## 🎯 Hoja de Ruta del Proyecto

- [x] **Puesta en marcha:** Recuperación de la placa, configuración de entorno y conexión Wi-Fi local.
- [ ] **Hito 1:** Servidor Web interactivo en el ESP32 para control desde el móvil (`http://192.168.1.38`).
- [ ] **Hito 2:** Control de carga física (Módulo relé / LED externo).
- [ ] **Hito 3:** Telemetría y lectura de sensores ambientales (DHT11/DHT22 o BME280).
- [ ] **Hito 4:** Domótica avanzada con control por voz (Alexa) o notificaciones por Telegram.

---

## 🔌 Hardware y Entorno

- **Microcontrolador:** ESP32-C3 Super Mini (RISC-V a 160 MHz, 4 MB Flash DIO).
- **Conectividad:** Wi-Fi 2.4 GHz + BLE 5.
- **FQBN Arduino:** `esp32:esp32:esp32c3:CDCOnBoot=cdc,FlashMode=dio`
- **Puerto Serie:** `COM5`

Para consultar todas las normas técnicas, directrices de seguridad y flujo de desarrollo, revisa:
👉 **[PROJECT_RULES.md](PROJECT_RULES.md)**
