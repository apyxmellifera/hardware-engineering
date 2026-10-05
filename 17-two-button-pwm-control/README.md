# Two-Button PWM Control

## Demo Video

https://youtu.be/R8Ita5D4Yi4

## Objective

Learn how to use two push buttons to increase and decrease the apparent brightness of an LED using PWM.

## Components

* Arduino Uno
* 2 push buttons
* 1 LED
* 1 × 330 Ω resistor
* Breadboard
* Jumper wires

## Circuit

### Push Buttons

* Button 1 → Arduino pin 10
* Button 2 → Arduino pin 11
* Other leg of each button → Arduino GND
* Arduino uses the internal pull-up resistors with `INPUT_PULLUP`

### LED

* Arduino pin 9 (PWM) → LED anode
* LED cathode → 330 Ω resistor → Arduino GND

## Behavior

* Both push buttons use `INPUT_PULLUP`.
* When a button is not pressed, its input reads `HIGH`.
* When a button is pressed, its input reads `LOW`.
* The program detects a single press by checking for a `HIGH → LOW` transition.
* Button 1 increases the LED brightness by 25%.
* Button 2 decreases the LED brightness by 25%.
* Brightness is limited between 0% and 100%.
* The brightness percentage is mapped to the PWM range of 0–255.
* `analogWrite()` uses the PWM value to control the apparent brightness of the LED.
* The Serial Monitor displays the current brightness percentage and PWM value.

## Concepts

* Push buttons
* Internal pull-up resistor
* `INPUT_PULLUP`
* Digital input
* `digitalRead()`
* Button state
* State transition
* `HIGH → LOW`
* Program state
* Multiple inputs
* PWM
* PWM values (0–255)
* `analogWrite()`
* `map()`
* Duty cycle
* LED brightness control
* Serial Monitor

## Files

* `code.ino` — Arduino source code
* `README.md` — Project overview
* `note.md` — Detailed engineering and physics notes
