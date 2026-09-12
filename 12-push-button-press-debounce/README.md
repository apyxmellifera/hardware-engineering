# Push Button (Debouncing)

## Demo Video

https://youtu.be/rDfjrB1U_FQ

## Objective

Learn how to debounce a mechanical push button and convert an unstable physical signal into a reliable software state change.

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

* Button press → Arduino detects a raw state change.
* Program waits 50 ms to allow the signal to stabilize.
* Stable state → accepted as a valid button event.
* Button release is handled in the same way.
* LED responds only to the confirmed button state.

## Concepts

* Mechanical switch bounce
* Digital input
* `INPUT_PULLUP`
* Active-low logic
* Raw vs stable state
* Debouncing
* State validation
* `millis()`
* Non-blocking timing
* Event detection

## Files

* `code.ino` — Arduino source code
* `README.md` — Project overview
* `note.md` — Detailed engineering and physics notes
