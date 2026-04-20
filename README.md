# PlantSync: Smart Indoor Plant Care System

[![IoT](https://img.shields.io/badge/IoT-ESP--NOW-blue.svg)](https://github.com/PrangshuPS/PlantSync)
[![Hardware](https://img.shields.io/badge/Hardware-ESP32-green.svg)](https://github.com/PrangshuPS/PlantSync)
[![Cloud](https://img.shields.io/badge/Cloud-ThingSpeak-orange.svg)](https://github.com/PrangshuPS/PlantSync)

## Project Overview
**PlantSync** is a decentralized IoT ecosystem designed to automate and optimize indoor plant maintenance. By utilizing a **Master-Slave architecture** via the **ESP-NOW protocol**, the system provides energy-efficient, real-time monitoring and centralized irrigation for urban homes and commercial spaces.

---

## The Problem
Inconsistent manual watering is the leading cause of indoor plant mortality. Urban environments (offices, apartments) often lack the consistent attention plants need, resulting in:
* **Water Wastage** due to overwatering.
* **Plant Stress** due to neglect.
* **Impracticality** of monitoring 5+ plants individually.

## The Solution
PlantSync offers a scalable, data-driven approach to plant care:
1.  **Distributed Sensing:** Multiple "Slave" nodes monitor soil health.
2.  **Low-Power Communication:** ESP-NOW allows nodes to talk without needing a Wi-Fi router.
3.  **Centralized Control:** A "Master" hub processes data and triggers a servo-powered pump.
4.  **Cloud Integration:** Real-time logging to **ThingSpeak** for remote health tracking.

---

## System Architecture
The project follows a modular project lifecycle (Design → Build → Test → Deploy):

* **Sensing Nodes (Slaves):** Equipped with Capacitive Soil Moisture sensors and DHT11 (Temp/Humidity) sensors.
* **Control Hub (Master):** Receives data from all slaves, evaluates thresholds, and manages the MG90 Servo-based irrigation system.
* **Telemetry:** Data is uploaded via Wi-Fi to ThingSpeak every 15 minutes for visualization.

---

## Tech Stack
| Category | Technology |
| :--- | :--- |
| **Microcontrollers** | ESP32 Wroom 32 (Master & Slaves) |
| **Sensors** | Capacitive Soil Moisture, DHT11 (Temp/Humidity) |
| **Actuators** | MG90S Servo, Submersible DC Pump |
| **Protocols** | ESP-NOW (Local Mesh), Wi-Fi (Cloud Upload) |
| **Cloud Platform** | ThingSpeak |

---

## Business & Societal Impact
* **Scalability:** Easily expanded to 5-10+ nodes for large office green-walls.
* **Sustainability:** Reduces water consumption by ensuring precise delivery only when required.
* **Modern Living:** Integrates seamlessly into the Smart Home ecosystem.

---
