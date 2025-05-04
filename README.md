# 🧪 Arduino Multimeter Project

This is my school project where I designed, built, and programmed a fully functional digital multimeter using an Arduino Uno and a custom PCB designed in KiCad.

📄 [Click here to read the full report (PDF)](docs/P2-Multimeter-Report.pdf)

---

## ✅ Features

- 🟢 **Voltage Measurement**
  - Low voltage: 0–5V (direct to ADC)
  - High voltage: 5–33.7V (voltage divider)

- 🟠 **Resistance Measurement**
  - Low resistance: 0–1kΩ
  - High resistance: 1–100kΩ

- 🔋 **Battery Monitoring**
  - Detects 9V and 12V sources
  - Low battery and no battery warnings

- 🎛️ **Rotary Switch Mode Selection**
  - Modes detected via 4-bit digital input

- 🔊 **Visual & Audio Feedback**
  - Green/Yellow/Red LEDs
  - Buzzer for continuity and battery alerts

- 🔢 **3-Digit 7-Segment Display**
  - Controlled via CD74HCT4511 BCD driver
  - Efficient multiplexing with decimal control

---

## 📷 Preview

### PCB Design
![PCB Design](docs/pcb-design.png)

### Assembled Multimeter
![Assembled Multimeter](docs/assembled-multimeter.png)

---

## 🛠️ Tools Used

- Arduino Uno R3
- KiCad 7+
- LTspice (simulation)
- Fluke multimeter (verification)
- Soldering station, protoboard, and banana connectors

---
