# 🧪 Arduino Multimeter Project

This is my school project where I designed, built, and programmed a fully functional digital multimeter using an Arduino Uno and a custom PCB designed in KiCad.

📄 [Click here to read the full report (PDF)](docs/P2-Multimeter-Report.pdf)

---

## ✅ Features

- 🟢 **Voltage Measurement**
  - Low voltage: 0–5V (direct to ADC)
  - High voltage: 5–33.7V (via voltage divider)

- 🟠 **Resistance Measurement**
  - Low resistance: 0–1kΩ
  - High resistance: 1–100kΩ

- 🔋 **Battery Monitoring**
  - Detects 9V and 12V sources
  - Provides low battery and no battery warnings

- 🎛️ **Rotary Switch Mode Selection**
  - Modes detected via 4-bit digital input

- 🔊 **Visual & Audio Feedback**
  - Green/Yellow/Red LEDs for status indication
  - Buzzer for continuity and battery alerts

- 🔢 **3-Digit 7-Segment Display**
  - Controlled via CD74HCT4511 BCD driver
  - Efficient multiplexing with decimal control

---

## 📷 Preview

### Schematic
![Schematic](docs/schematic.png)

### Top Layer
![Top Layer](docs/top-layer.png)

### Bottom Layer
![Bottom Layer](docs/bottom-layer.png)

### PCB Design
![PCB Design](docs/pcb.jpg)

### Assembled Multimeter
![Assembled Multimeter](docs/multimeter.jpg)

---

## 🛠️ Tools Used

- Arduino Uno R3
- KiCad 7+
- LTspice (for simulation)
- Fluke multimeter (for verification)
- Soldering station, protoboard, and banana connectors

---
