# Potentiometer LED Threshold

## Demo Video
https://youtu.be/-N9G-PK-4kA

## Objective

Learn how to read an analog voltage from a potentiometer and use that value to control a digital output based on a voltage threshold.

## Components

* Arduino Uno
* 1 potentiometer (10 kΩ)
* 1 LED
* 1 × 330 Ω resistor
* Breadboard
* Jumper wires

## Circuit

### Potentiometer

* Pin 1 → Arduino 5V
* Pin 2 (wiper) → Arduino A0
* Pin 3 → Arduino GND

### LED

* Arduino pin 12 → 330 Ω resistor → LED anode
* LED cathode → GND

## Behavior

* The potentiometer produces a variable voltage between approximately 0 V and 5 V.
* Arduino reads the voltage through analog pin A0.
* The 10-bit ADC converts the input into a value from 0–1023.
* The program converts the ADC reading into an approximate voltage.
* If the voltage is **2.6 V or higher**, the LED turns ON.
* If the voltage is **below 2.6 V**, the LED turns OFF.

## Concepts

* Potentiometer
* Variable voltage
* Voltage divider
* Analog input
* ADC
* 10-bit resolution
* `analogRead()`
* ADC values (0–1023)
* Voltage conversion
* `if / else`
* Threshold-based control
* Digital output
* `digitalWrite()`

## Files

* `code.ino` — Arduino source code
* `README.md` — Project overview
* `note.md` — Detailed engineering and physics notes
