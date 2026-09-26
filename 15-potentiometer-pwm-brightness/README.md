# Potentiometer PWM Brightness

## Demo Video
https://youtu.be/fsPSmA-ev7w

## Objective

Learn how to use a potentiometer to control the apparent brightness of an LED by converting an analog input value into a PWM output value.

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

* Arduino pin 9 (PWM) → LED anode

* LED cathode → 330 Ω resistor → Arduino GND

## Behavior

* The potentiometer produces a variable voltage between approximately 0 V and 5 V.

* Arduino reads the voltage through analog pin A0.

* The 10-bit ADC converts the input into a value from 0–1023.

* The program maps the ADC value from the 0–1023 range to the PWM range of 0–255.

* `analogWrite()` uses the PWM value to control the apparent brightness of the LED.

* The Serial Monitor displays the ADC value and its corresponding PWM value.

## Concepts

* Potentiometer

* Variable voltage

* Analog input

* ADC

* 10-bit resolution

* `analogRead()`

* ADC values (0–1023)

* Range mapping

* `map()`

* PWM

* PWM values (0–255)

* `analogWrite()`

* Duty cycle

* LED brightness control

* Serial Monitor

## Files

* `code.ino` — Arduino source code

* `README.md` — Project overview

* `note.md` — Detailed engineering and physics notes
