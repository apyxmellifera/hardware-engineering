# Push Button (Long-Press LED)

## Demo Video

https://youtu.be/HUbjgMjUOfU

## Objective

Learn how to detect a long button press using `millis()` and use it to control an LED.

## Components

* Arduino Uno
* 1 LED
* 1 × 330 Ω resistor
* 1 push button
* Breadboard
* Jumper wires

## Circuit

* Push button → Arduino pin 8
* LED → Arduino pin 12
* Button uses Arduino's internal pull-up resistor
* LED connected through a 330 Ω current-limiting resistor

## Behavior

* Press and hold the button for 1 second → LED turns ON.
* Keep holding → LED remains ON.
* Release the button → LED turns OFF.

## Concepts

* Digital input
* `INPUT_PULLUP`
* Active-low logic
* State transition detection
* `millis()`
* Non-blocking timing
* Long-press detection
* LED control

## Files

* `code.ino` — Arduino source code
* `note.md` — Detailed engineering and physics notes
