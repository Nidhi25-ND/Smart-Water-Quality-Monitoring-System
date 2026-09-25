# Smart Water Quality Monitoring System

## Overview
This project implements a **Smart Water Quality Monitoring System** using **Arduino UNO, ESP32, and IoT technology**.  
It continuously measures **pH, turbidity, and temperature** of water, processes the data, and provides **LED safety indicators**, a **local web dashboard**, and **ThingSpeak cloud integration** for real‑time monitoring and analysis.

## Key Features
- **Real‑time monitoring** of pH, turbidity, and temperature  
- **Arduino UNO** for sensor data processing and LED control  
- **ESP32 Wi‑Fi module** for wireless communication  
- **LED indicators**:
  - Green → Safe water  
  - Yellow → Moderate quality  
  - Red → Unsafe water  
- **ThingSpeak cloud integration** for remote monitoring and visualization  
- **Local ESP32 web server** for offline dashboard access  
- **Portable, low‑cost, and scalable** design  

## Hardware Components
- Arduino UNO (sensor data processing + LED logic)  
- ESP32 Wi‑Fi module (IoT connectivity)  
- Sensors:
  - pH sensor  
  - Turbidity sensor  
  - DS18B20 temperature sensor  
- LEDs (Green, Yellow, Red) for safety indication  
- Breadboard, resistors, jumper wires, power supply  

## Software & Tools
- Arduino IDE (programming & uploading code)  
- ESP8266/ESP32 libraries (Wi‑Fi + IoT support)  
- ThingSpeak API (cloud visualization & storage)  
- Local Web Server (HTML + JSON for offline monitoring)  
- TinkerCAD (simulation & testing)  

## System Workflow
1. **Sensors** measure pH, turbidity, and temperature.  
2. **Arduino UNO** processes sensor data and controls LEDs.  
3. **ESP32** transmits data via Wi‑Fi.  
4. **ThingSpeak cloud** stores and visualizes readings.  
5. **Local web dashboard** displays real‑time values.  
6. **Alerts** are triggered if thresholds are exceeded.  

## Applications
- Drinking water safety monitoring  
- Industrial water treatment systems  
- Smart agriculture irrigation monitoring  
- Fish farms and aquaculture  
- Environmental monitoring of rivers and lakes  

## Advantages
- Continuous monitoring  
- Low cost and energy efficient  
- Portable and easy to use  
- Wireless data transmission  
- Accurate and reliable results  
- Reduces human effort  


