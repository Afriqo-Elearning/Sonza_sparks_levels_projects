# Sonza Sparks Arduino Projects ⚡

This repository is a collection of Arduino and ESP32 source codes developed under **Sonza Sparks**.  
It includes projects from **beginner-friendly experiments** (like LED chasers) to **advanced IoT systems** (like smart irrigation using ESP32 with Blynk IoT).

---

## 📂 Project Structure

Each folder contains a self-contained Arduino sketch (`.ino` file) with wiring instructions and notes.  
Here’s a quick overview:

- **01-LED-Chaser/**  
  Simple LED running light using basic digital outputs.

- **02-Buzzer-Alarm/**  
  Motion detection with ultrasonic sensor + buzzer.

- **03-Hand-Wash-Machine/**  
  Automatic hand wash pump using ultrasonic sensor + relay.

- **04-Smart-Watering-Arduino/**  
  Soil moisture–based watering system using relay + pump.

- **05-Smart-Irrigation-ESP32-Blynk/**  
  IoT irrigation control with ESP32 + Blynk Cloud integration.

*(...add more projects as the repo grows)*

---

## 🚀 Getting Started

### Requirements
- **Arduino IDE** (latest version) or [PlatformIO](https://platformio.org/)  
- Supported boards:  
  - Arduino Uno / Nano  
  - ESP32-DevKit / ESP32-WROOM  
  - NodeMCU (ESP8266) for IoT projects  
- Libraries (depending on project):  
  - [Blynk](https://github.com/blynkkk/blynk-library)  
  - [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)  
  - [DHT sensor library](https://github.com/adafruit/DHT-sensor-library)  
  - [WiFi.h](https://github.com/espressif/arduino-esp32) (for ESP32 IoT)  

### Uploading a Project
1. Open the desired project folder in **Arduino IDE**.  
2. Select the correct **Board** and **Port** in `Tools`.  
3. Connect your board via USB and click **Upload**.  
4. Follow the wiring diagram inside the project folder (if provided).  

---

## 🛠️ Example Projects

### 1. LED Chaser
- Board: Arduino Uno  
- Components: 6 LEDs, resistors, breadboard  
- Demonstrates: `digitalWrite()`, `for` loops  

### 2. Hand Wash Machine
- Board: Arduino Uno  
- Components: Ultrasonic sensor, relay module, pump  
- Demonstrates: Ultrasonic distance measurement + relay control  

### 3. Smart Irrigation with ESP32 + Blynk
- Board: ESP32  
- Components: Soil moisture sensor, relay, pump  
- Features: IoT monitoring and control from Blynk mobile app  

---

## 📖 Contributing

Got improvements or new project ideas?  
- Fork the repo  
- Add your project inside a new folder  
- Submit a pull request  

---

## 📜 License
This repository is shared under the **MIT License** — free to use, modify, and share.  

---

## 🌟 Credits
Developed by **Sonza Sparks**  
> "From blinking LEDs to full IoT automation — learning by building."
