# Push Button (Long-Press Toggle)

## Demo Video

https://youtu.be/HUbjgMjUOfU

## Objective

Learn how to use a long button press as an event to toggle an LED's state.

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

* Short press → Nothing happens.
* Hold button for 1 second → LED toggles.
* Release → LED remains in its current state.
* Another long press → LED toggles again.

### Example

```text
LED OFF
   ↓
Long press
   ↓
LED ON
   ↓
Release
   ↓
LED ON
   ↓
Long press
   ↓
LED OFF
```

## Concepts

* Digital input
* `INPUT_PULLUP`
* Active-low logic
* State transition detection
* `millis()`
* Non-blocking timing
* Long-press detection
* Event handling
* Persistent state
* Toggle logic

## Files

* `code.ino` — Arduino source code
* `README.md` — Project overview
* `note.md` — Detailed engineering and physics notes
