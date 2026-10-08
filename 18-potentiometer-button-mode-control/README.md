# Potentiometer Button Mode Control

## Demo Video

https://youtu.be/n57AbiJ9yug

## Objective

Learn how to use three push buttons and a potentiometer to control an LED through two different control modes.

## Components

* Arduino Uno
* 3 push buttons
* 1 potentiometer (10 kΩ)
* 1 LED
* 1 × 330 Ω resistor
* Breadboard
* Jumper wires

## Circuit

### Push Buttons

* Button 1 → Arduino pin 10
* Button 2 → Arduino pin 11
* Button 3 → Arduino pin 12
* Other leg of each button → Arduino GND
* Arduino uses the internal pull-up resistors with `INPUT_PULLUP`

### Potentiometer

* Pin 1 → Arduino 5V
* Pin 2 (wiper) → Arduino A0
* Pin 3 → Arduino GND

### LED

* Arduino pin 9 (PWM) → LED anode
* LED cathode → 330 Ω resistor → Arduino GND

## Behavior

* The program has two brightness control modes.
* Button 3 switches between the two modes.
* Button Mode allows Button 1 to increase brightness and Button 2 to decrease brightness.
* Brightness is controlled in steps of 25%.
* Brightness is limited between 0% and 100%.
* Potentiometer Mode uses the potentiometer to control the LED brightness.
* The potentiometer produces an analog value from 0–1023.
* The ADC value is mapped to the PWM range of 0–255.
* Only the active mode controls the LED.
* The Serial Monitor displays the current control mode and output values.

## Concepts

* Push buttons
* Internal pull-up resistor
* `INPUT_PULLUP`
* Digital input
* `digitalRead()`
* Button state
* State transition
* `HIGH → LOW`
* Multiple inputs
* Program state
* Control modes
* Mode switching
* Potentiometer
* Analog input
* ADC
* ADC values (0–1023)
* `analogRead()`
* PWM
* PWM values (0–255)
* `analogWrite()`
* `map()`
* LED brightness control
* Serial Monitor

## Files

* `code.ino` — Arduino source code
* `README.md` — Project overview
* `note.md` — Detailed engineering and physics notes
