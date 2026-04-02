# Isolated UART Hardware Watchdog (ATtiny85)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A lightweight, highly reliable, galvanically isolated hardware watchdog for embedded systems and IoT devices (ESP32, Arduino, STM32, etc.). This watchdog operates independently of the target MCU, recovering it from kernel panics, endless loops, or network lock-ups.

Unlike complex supervisors, this project uses a minimalist approach: it requires no external crystals, runs entirely on the ATtiny85's internal oscillator, and uses a simple UART heartbeat mechanism.

## Table of Contents

- [Overview](#overview)
- [Hardware Requirements](#hardware-requirements)
- [Wiring & Pin Configuration](#wiring--pin-configuration)
- [Logic & Behavior](#logic--behavior)
- [Flashing the ATtiny85](#flashing-the-attiny85)
- [Target Device Code](#target-device-code)
- [License](#license)

## Overview

The ATtiny85 acts as an independent observer. It continuously listens to a SoftwareSerial RX pin at 9600 baud. The target device simply needs to print any serial data (e.g., "H") at regular intervals.

- **Healthy State**: When data is received, the ATtiny85 flashes a status LED and resets its internal 60-second countdown.
- **Failed State**: If the target hangs and fails to send data for ~60 seconds, the ATtiny85 triggers an isolated optocoupler to pull the target's RESET pin to ground, forcing a hard reboot.

## Hardware Requirements

- **Microcontroller**: ATtiny85
- **Isolation**: PC817 Optocoupler
- **Status Indicator**: 1x LED (e.g., Green or Blue)
- **Resistors**:
  - 1x 220Ω (For ATtiny85 Status LED)
  - 1x 220Ω (For PC817 Anode)
  - 1x 1kΩ (UART protection on RX line)
  - 1x 10kΩ (Pull-up for Target Reset pin)

## Wiring & Pin Configuration

### ATtiny85 Pinout

| ATtiny85 Pin | Code Variable | Connection |
|--------------|---------------|------------|
| PB0 (Pin 5) | rxPin | Target MCU TX (via 1kΩ Resistor) |
| PB1 (Pin 6) | RST | PC817 Pin 1 (Anode) (via 220Ω Resistor) |
| PB2 (Pin 7) | LED | Status LED Anode (via 220Ω Resistor) |
| Pin 4 | GND | Watchdog Ground |
| Pin 8 | VCC | 3.3V or 5V Power |

### PC817 Optocoupler Isolation

To completely isolate the watchdog from the target device, wire the PC817 output as follows:

- **Pin 3 (Emitter)**: Connect directly to Target Device GND.
- **Pin 4 (Collector)**: Connect directly to Target Device RESET pin.

**Note**: Ensure your target device has a 10kΩ pull-up resistor between its VCC and RESET pin.

## Logic & Behavior

- **Boot & Loop**: The watchdog loops continuously, incrementing a counter every 1 second.
- **Heartbeat Detection**: If serial data is available, it reads and clears the buffer, flashes the Status LED for 500ms, and resets the counter to 0.
- **Trigger Event**: If the counter reaches 60 seconds without receiving data, the RST pin goes HIGH for 1000ms. This activates the PC817, which pulls the target's Reset pin LOW.
- **Error Indication**: After a reset event, the watchdog triggers a rapid, flashing LED sequence (LED_P()) to visually indicate a crash recovery occurred.

## Flashing the ATtiny85

**Important Clock Note**: Because SoftwareSerial at 9600 baud relies on precise timing, the default 1MHz internal clock of a factory ATtiny85 will cause garbage data.

1. In the Arduino IDE, set your Board to **ATtiny25/45/85**.
2. Set the Clock to **Internal 8 MHz**.
3. **Crucial Step**: Click **"Burn Bootloader"** before uploading your sketch. This sets the internal fuses to run the chip at 8MHz, ensuring the 9600 baud rate reads perfectly.
4. Upload the provided `WatchDog.ino` firmware.

## Target Device Code

Add this simple snippet to your main IoT device (e.g., ESP32, Arduino) to keep the watchdog timer satisfied.

```cpp
void setup() {
  // Start serial communication at 9600 baud to match the Watchdog
  Serial.begin(9600);
}

void loop() {
  // Your main application code goes here...
  
  // Send the heartbeat character over TX
  Serial.print("H");
  
  // Delay or execute tasks (ensure the loop doesn't block for more than 60s)
  delay(1000);
}
```

## License

This project is open-source under the MIT License. Feel free to modify and adapt it for your own embedded reliability needs!