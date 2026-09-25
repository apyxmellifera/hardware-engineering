# PWM Brightness

## Goal

Use **PWM (Pulse Width Modulation)** to control the apparent brightness of an LED.

Unlike Project 13, where the LED was only **ON or OFF**, PWM allows different brightness levels.

## `analogWrite()`

On an Arduino Uno:

```cpp
analogWrite(led, value);
```

The PWM value ranges from:

```text
0 → 255
```

### Duty Cycle

The duty cycle is:

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

> `analogWrite()` on the Arduino Uno produces a **PWM signal**, not a steady analog voltage.

## Circuit

```text
Pin 9 (PWM)
     ↓
    LED
     ↓
  330 Ω
     ↓
    GND
```

## Key Takeaway

```text
PWM value
    ↓
Duty cycle
    ↓
LED brightness
```
