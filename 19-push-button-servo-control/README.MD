# Push Button Servo Control

## Demo Video

https://youtu.be/GtyPOn2Yx5E

## Objective

Learn how to use a push button to control a positional servo motor, switching its target position between 0° and 90° with each press.

## Components

* Arduino Uno
* 1 positional servo motor (SG90)
* 1 push button
* Breadboard
* Jumper wires

## Circuit

### Push Button

* One side → Arduino pin 12
* Opposite side → Arduino GND
* Arduino uses the internal pull-up resistor with `INPUT_PULLUP`

### Servo Motor

* Signal wire → Arduino pin 9
* Power wire → Arduino 5V
* Ground wire → Arduino GND

## Behavior

* The push button uses `INPUT_PULLUP`.
* When the button is released, its input reads `HIGH`.
* When the button is pressed, its input reads `LOW`.
* The program detects a single press using a `HIGH → LOW` transition.
* Each press switches the servo's target position between 0° and 90°.
* The Servo library sends the position command to the servo.
* The Serial Monitor displays the commanded angle.

## Concepts

* Servo motor
* DC motor
* Gearbox
* Position feedback
* Positional control
* Servo library
* `Servo` object
* `attach()`
* `write()`
* Push button
* `INPUT_PULLUP`
* `digitalRead()`
* Button state
* State transition
* `HIGH → LOW`
* Program state
* Conditional logic
* Serial Monitor

## Files

* `code.ino` — Arduino source code
* `README.md` — Project overview
* `note.md` — Engineering and physics notes
