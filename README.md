# 🤖 PS4-Controlled SumoRobot Car

This project is a **Bluetooth-controlled Sumo Robot** powered by an **ESP32 microcontroller** and a **PlayStation 4 controller**. The robot features dual motor control for agile movement and a toggleable attack weapon, making it ideal for sumo-style competitions.

---

## 🎮 Features

- ✅ **Wireless PS4 Controller Support** via Bluetooth
- 🎯 **Joystick-Based Directional Control** (forward, backward, turn left/right)
- ⚔️ **Toggleable Attack Mechanism** via the X (Cross) button
- 🛑 **Deadzone Filtering** to avoid accidental drift
- ⚡ **PWM Motor Speed Control** for smooth acceleration
- 🔒 **Failsafe Logic**: Motors and weapon stop if the controller disconnects

---

## 🛠️ Components

| Component             | Description                            |
|----------------------|----------------------------------------|
| ESP32 Board          | Main controller with Bluetooth support |
| PS4 Controller       | User input device                      |
| L298N Motor Driver   | Controls 2 DC motors                   |
| DC Gear Motors       | Drive system for movement              |
| Custom Weapon Motor  | Attack mechanism (servo or DC motor)   |
| Power Supply         | e.g., 2S Li-ion battery pack           |

---

## 📋 Controls

| PS4 Control | Function                  |
|-------------|---------------------------|
| Left Stick  | Move/turn the robot       |
| X Button    | Toggle attack mechanism   |

---

## 🔌 Pin Configuration

| Signal       | ESP32 Pin |
|--------------|-----------|
| Motor A IN1  | 14        |
| Motor A IN2  | 27        |
| Motor A EN   | 26 (PWM0) |
| Motor B IN3  | 25        |
| Motor B IN4  | 33        |
| Motor B EN   | 32 (PWM1) |
| Attack Motor | 22        |

---

## ⚙️ Setup Instructions

1. Wire the motors and weapon as per the pin configuration above.
2. Pair your PS4 controller with the ESP32 using its Bluetooth MAC address:
   ```cpp
   PS4.begin("94:54:C5:76:B2:84"); // Replace with your controller's MAC
