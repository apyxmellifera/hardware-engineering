# Push Button PWM Control

## Demo Video

[Add demo video link]

## Objective

Learn how to use a push button to change the brightness of an LED in fixed percentage steps using PWM.

## Components

* Arduino Uno
* 1 push button
* 1 LED
* 1 × 330 Ω resistor
* Breadboard
* Jumper wires

## Circuit

### Push Button

* One button leg → Arduino pin 11
* Other button leg → Arduino GND
* Arduino uses the internal pull-up resistor with `INPUT_PULLUP`

### LED

* Arduino pin 9 (PWM) → LED anode
* LED cathode → 330 Ω resistor → Arduino GND

## Behavior

* The push button uses `INPUT_PULLUP`.
* When the button is not pressed, the input reads `HIGH`.
* When the button is pressed, the input reads `LOW`.
* The program detects a single press by checking for a `HIGH → LOW` transition.
* Each button press increases the LED brightness by 25%.
* The brightness cycles through 25%, 50%, 75%, 100%, and 0%.
* The brightness percentage is mapped to the PWM range of 0–255.
* `analogWrite()` uses the PWM value to control the apparent brightness of the LED.
* The Serial Monitor displays the current brightness percentage and PWM value.

## Concepts

* Push button
* Internal pull-up resistor
* `INPUT_PULLUP`
* Digital input
* `digitalRead()`
* Button state
* State transition
* `HIGH → LOW`
* PWM
* PWM values (0–255)
* `analogWrite()`
* `map()`
* LED brightness control
* State
* Serial Monitor

## Files

* `code.ino` — Arduino source code
* `README.md` — Project overview
* `note.md` — Detailed engineering and physics notes
