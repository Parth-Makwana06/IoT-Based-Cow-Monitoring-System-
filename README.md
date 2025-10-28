# 🌐 IoT-Based Cow Monitoring System

An **IoT-Based Cow Monitoring System** designed to track the **temperature, humidity, movement, and location** of cows using **ESP32**, **DHT11**, **GPS NEO-6M**, and **MPU6050** sensors.  
This project helps farmers monitor the health and activity of cattle in real-time, improving livestock management and productivity.

---

## 🚀 Features

- 🌡️ Monitors **temperature and humidity** using DHT11 sensor  
- 📍 Tracks **real-time GPS location** using NEO-6M GPS module  
- 🧭 Detects **movement and orientation** with MPU6050 accelerometer & gyroscope  
- 📡 Uses **ESP32** for data processing and wireless connectivity  
- 🖥️ Data can be displayed on a dashboard, mobile app, or serial monitor  

---

## 🧩 Hardware Components

| Component | Description |
|------------|-------------|
| **ESP32** | Main microcontroller and Wi-Fi module |
| **DHT11** | Measures temperature and humidity |
| **GPS NEO-6M** | Tracks latitude and longitude of the cow |
| **MPU6050** | Detects motion and body orientation |
| **Jumper Wires** | For circuit connections |
| **Power Supply (Battery)** | To power the ESP32 and sensors |

---

## ⚙️ Circuit Overview

1. Connect **DHT11** data pin to `GPIO 4` of ESP32  
2. Connect **GPS NEO-6M** TX → `GPIO 16`, RX → `GPIO 17`  
3. Connect **MPU6050** SDA → `GPIO 21`, SCL → `GPIO 22`  
4. Power all modules with **3.3V / 5V** from the ESP32 board  
5. Common ground for all components  

---

## 💻 How to Use

1. Install the following Arduino libraries:
   - `DHT.h`
   - `Wire.h`
   - `TinyGPS++`
   - `MPU6050.h`  
2. Open the `.ino` file in **Arduino IDE**  
3. Select the correct board → **ESP32 Dev Module**  
4. Upload the code to the ESP32  
5. Open **Serial Monitor** to view:
   - Temperature & Humidity readings  
   - GPS coordinates  
   - Movement/orientation data  

---

## 📊 Future Enhancements

- Send real-time data to a **cloud dashboard (ThingSpeak / Firebase)**  
- Add **alert system** for abnormal temperature or motion  
- Include **health prediction** using ML models  

---

## 🧠 Learning Outcomes

- Integration of multiple IoT sensors with ESP32  
- Real-time data acquisition and monitoring  
- Basics of IoT communication and GPS interfacing  

---

## 📸 Project Overview

> *A smart and efficient IoT solution to monitor cow health and activity — bridging technology with agriculture.*

---

### 🧑‍💻 Developed by:
**Parth**  
✨ IoT | Embedded Systems | ESP32 | Arduino | Smart Farming Solutions

---

### 🏷️ Tags
`IoT` `ESP32` `DHT11` `GPS NEO-6M` `MPU6050` `Arduino` `Livestock Monitoring` `Smart Agriculture`
