# ESP32 Frequency Detector 🚀

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-blue.svg)](https://www.espressif.com/en/products/socs/esp32)

A professional-grade ESP32-based frequency counter that measures input signals from oscilloscopes or function generators and displays them in real-time on an LCD. It also features a PWM signal output that mirrors the input frequency.

## 🌟 Features
- **Accurate Measurement:** Uses hardware interrupts for precise pulse counting.
- **Real-time Display:** 16x2 I2C LCD shows the measured frequency in Hz.
- **Signal Mirroring:** Generates a PWM signal output at the same frequency as the input.
- **Serial Logging:** Real-time data streaming via USB Serial for debugging.

## 🛠️ Hardware Requirements
| Component | Quantity | Notes |
| :--- | :--- | :--- |
| ESP32 Dev Board | 1 | Any standard 30-pin or 38-pin module |
| 16x2 I2C LCD | 1 | With I2C Backpack module |
| Resistors | 2 | 4.7kΩ Pull-up resistors for I2C |
| Hookup Wires | - | Jumper wires |

## 🔌 Wiring Table
| ESP32 Pin | Component Pin | Description |
| :--- | :--- | :--- |
| **GPIO 27** | Signal Input | Input from CRO/Source |
| **GPIO 26** | Signal Output | PWM Mirror Output |
| **GPIO 21** | LCD SDA | I2C Data |
| **GPIO 22** | LCD SCL | I2C Clock |
| **3.3V** | LCD VCC | Power |
| **GND** | LCD GND | Common Ground |

## 📐 Schematic
![Project Schematic](docs/schematic.png)

## 🚀 Getting Started
1. **Prerequisites:** Install [Arduino IDE](https://www.arduino.cc/en/software).
2. **Board Manager:** Add ESP32 support (Preferences -> Board Manager URLs: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`).
3. **Libraries:** Install `LiquidCrystal_I2C` via the Library Manager.
4. **Flash:** Open `firmware/esp32_frequency_detector/esp32_frequency_detector.ino` and upload to your ESP32.

## 📂 Project Structure
- `firmware/`: Contains the Arduino sketch.
- `docs/`: Schematics and detailed code walkthrough.

## 📄 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
