# IOT-BASED-WEATHER-MONITORING-SYSTEM

- **NAME:** ANURAG KUMAR
- **INSTITUTE:** National Institute of Technology (NIT) Delhi
- **DOMAIN:** Embedded Systems & Internet of Things (IoT)
- **MICROCONTROLLER:** NodeMCU (ESP8266)
- **PROGRAMMING LANGUAGE:** Embedded C / C++ (Arduino IDE)
- **CLOUD PLATFORM:** Blynk IoT (Web & Mobile Dashboard)

---

## -----DESCRIPTION-----

### Objective
The objective of this project is to design and implement a real-time, IoT-enabled Weather Monitoring System using the NodeMCU (ESP8266) microcontroller. The system continuously acquires five key environmental parameters—**Temperature, Humidity, Barometric Pressure, Rainfall, and Ambient Light Intensity**—and displays live readings simultaneously on a local **16x2 I2C LCD** as well as remotely on the **Blynk IoT** dashboard.

### Introduction & System Overview
Real-time environmental monitoring plays a vital role in smart agriculture, weather forecasting, and industrial automation. In this project, multiple digital and analog sensors are interfaced with the ESP8266 Wi-Fi SoC on a breadboard setup. The controller processes the raw sensor data, formats it for local human-readable output via an I2C-interfaced 16x2 LCD module, and transmits real-time telemetry over Wi-Fi to the Blynk IoT cloud platform (accessible via both laptop web dashboard and smartphone app).

### Hardware Components & Specifications
- **Microcontroller:** NodeMCU (ESP8266 ESP-12E Wi-Fi Module)
- **Temperature & Humidity Sensor:** DHT11 (Digital Single-Wire Interface)
- **Barometric Pressure Sensor:** BMP180 (I2C Interface)
- **Rainfall Detection:** Raindrop Sensor Module
- **Light Intensity Detection:** LDR (Light Dependent Resistor) Sensor Module
- **Local Display:** 16x2 Alphanumeric LCD (16 Columns × 2 Rows) with PCF8574 I2C Adapter Module
- **Prototyping & Connections:** Breadboard and Male-to-Male / Male-to-Female Jumper Wires

### Key Features & Working Principle
1. **Multi-Sensor Data Acquisition:** Reads ambient temperature (°C) and relative humidity (%) from DHT11, atmospheric pressure (hPa/mbar) from BMP180 over the I2C bus, rainfall status/intensity from the rain sensor, and light levels from the LDR module.
2. **Dual-Mode Live Visualization:**
   - **Local Display:** Real-time scrolling/periodic parameter updates on the 16x2 LCD using only two GPIO pins (SDA & SCL) via the I2C module.
   - **Cloud Telemetry:** Live sensor gauges and status indicators streamed over Wi-Fi to the **Blynk IoT** dashboard for remote monitoring on PC or mobile.
3. **Low-Pin-Count I2C Bus Sharing:** Both the BMP180 sensor and the 16x2 LCD share the I2C communication bus (`D1/SCL` and `D2/SDA`), optimizing GPIO utilization on the ESP8266.

---

## -----OUTPUT & HARDWARE SETUP-----

### Hardware Circuit & LCD Output
![Hardware Setup](hardware_setup.jpg)

### Blynk IoT Live Dashboard
![Blynk Dashboard](blynk_dashboard.png)
