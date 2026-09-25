# PWM Brightness

## Demo Video

https://youtu.be/n9HHHaSPgoQ

## Objective

Learn how to use PWM (Pulse Width Modulation) to control the apparent brightness of an LED.

## Components

* Arduino Uno

* 1 LED

* 1 × 330 Ω resistor

* Breadboard

* Jumper wires

## Circuit

### LED

* Arduino pin 9 (PWM) → LED anode
* LED cathode → 330 Ω resistor → Arduino GND

## Behavior

* Arduino pin 9 generates a PWM signal.
* `analogWrite()` controls the PWM value from 0–255.
* The PWM value determines the duty cycle of the signal.
* A higher duty cycle makes the LED appear brighter.
* A lower duty cycle makes the LED appear dimmer.
* A PWM value of 0 turns the LED OFF.
* A PWM value of 255 produces 100% duty cycle.

## PWM Values

The duty cycle can be calculated using:

$$
\text{Duty Cycle} = \frac{\text{PWM Value}}{255} \times 100
$$

| PWM Value | Duty Cycle |
| --------: | ---------: |
|         0 |         0% |
|        64 |      25.1% |
|       128 |      50.2% |
|       192 |      75.3% |
|       255 |       100% |

For example:

```cpp
int brightness = 128;
analogWrite(led, brightness);
```

This produces approximately a **50.2% duty cycle**.

> `analogWrite()` on the Arduino Uno produces a PWM signal rather than a steady analog voltage.

## Concepts

* PWM (Pulse Width Modulation)

* Duty cycle

* `analogWrite()`

* PWM values (0–255)

* PWM-capable pins

* LED brightness control

* Digital output

## Files

* `code.ino` — Arduino source code

* `README.md` — Project overview

* `note.md` — Detailed engineering and physics notes
