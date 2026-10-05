# Engineering and Physics Notes

## 1. Project Overview

This project builds on the previous push-button and PWM projects.

Two push buttons are used to control the brightness of an LED:

* Button 1 increases brightness.
* Button 2 decreases brightness.
* LED brightness is controlled using PWM.
* Brightness is maintained as a program state.
* The brightness is limited between 0% and 100%.

The brightness changes in 25% steps:

```text
0% → 25% → 50% → 75% → 100%
```

and can be decreased:

```text
100% → 75% → 50% → 25% → 0%
```

---

## 2. Push Buttons With `INPUT_PULLUP`

Both buttons use the Arduino's internal pull-up resistor:

```cpp
pinMode(pushButton1, INPUT_PULLUP);
pinMode(pushButton2, INPUT_PULLUP);
```

Each button is connected between an Arduino input pin and GND.

The input behavior is:

| Button      | Input |
| ----------- | ----: |
| Not pressed |  HIGH |
| Pressed     |   LOW |

Therefore, pressing the button produces a `HIGH → LOW` transition.

---

## 3. Detecting a Single Press

Each button has its own previous state:

```text
lastButtonState1
lastButtonState2
```

The current states are read using:

```text
currentButtonState1
currentButtonState2
```

A press is detected when:

```text
HIGH → LOW
```

For example:

```cpp
if (lastButtonState1 == HIGH && currentButtonState1 == LOW)
```

This prevents the brightness from continuously changing while the button is held.

After processing the buttons, the current states become the previous states:

```text
last state = current state
```

This allows the program to detect the next transition.

---

## 4. Brightness as Program State

The current brightness is stored in:

```cpp
int brightness = 0;
```

The variable remembers the brightness between iterations of `loop()`.

Button 1 increases the state:

```text
0 → 25 → 50 → 75 → 100
```

Button 2 decreases the state:

```text
100 → 75 → 50 → 25 → 0
```

The brightness therefore acts as the central state controlled by both inputs.

```text
Increase button ──→ brightness ←── Decrease button
                         ↓
                       PWM
                         ↓
                        LED
```

---

## 5. Limiting Brightness

The brightness must remain between 0% and 100%.

### Upper limit

When increasing:

```cpp
brightness += 25;
```

If the value goes above 100:

```cpp
if (brightness > 100)
{
  brightness = 100;
}
```

This means the maximum brightness is 100%.

The sequence is:

```text
75 → 100 → 100 → 100
```

The value does not wrap back to 0%.

### Lower limit

When decreasing:

```cpp
if (brightness > 0)
{
  brightness -= 25;
}
```

When brightness reaches 0%, it cannot become negative.

The sequence is:

```text
25 → 0 → 0 → 0
```

This creates bounded state:

```text
0 ≤ brightness ≤ 100
```

---

## 6. Converting Brightness to PWM

The brightness state uses a percentage:

```text
0–100%
```

Arduino PWM uses:

```text
0–255
```

The two ranges are converted using:

```cpp
map(brightness, 0, 100, 0, 255);
```

The conversion is approximately:

| Brightness | PWM |
| ---------: | --: |
|         0% |   0 |
|        25% |  63 |
|        50% | 127 |
|        75% | 191 |
|       100% | 255 |

---

## 7. Mapping Calculation

The general mapping equation is:

```text
Output =
((Input - Input Min) /
(Input Max - Input Min))
×
(Output Max - Output Min)
+
Output Min
```

For this project:

```text
Input = brightness
Input range = 0–100
Output range = 0–255
```

Therefore:

```text
PWM = (brightness / 100) × 255
```

### 25%

```text
PWM = (25 / 100) × 255
PWM = 63.75
```

The integer result is approximately:

```text
63
```

### 50%

```text
PWM = (50 / 100) × 255
PWM = 127.5
```

Result:

```text
127
```

### 75%

```text
PWM = (75 / 100) × 255
PWM = 191.25
```

Result:

```text
191
```

### 100%

```text
PWM = (100 / 100) × 255
PWM = 255
```

---

## 8. PWM and LED Brightness

The PWM value controls the duty cycle of the output signal.

The approximate duty cycle is:

```text
Duty Cycle = (PWM Value / 255) × 100
```

Examples:

| Brightness | PWM | Approx. Duty Cycle |
| ---------: | --: | -----------------: |
|         0% |   0 |                 0% |
|        25% |  63 |              24.7% |
|        50% | 127 |              49.8% |
|        75% | 191 |              74.9% |
|       100% | 255 |               100% |

The Arduino rapidly switches the PWM pin between HIGH and LOW.

Changing the proportion of time the signal is HIGH changes the average power delivered to the LED, which produces the perception of different brightness levels.

---

## 9. `analogWrite()`

The PWM value is sent to the LED using:

```cpp
analogWrite(led, pwmValue);
```

On the Arduino Uno, pin 9 supports PWM.

`analogWrite()` does not produce a continuously variable analog voltage. It produces a PWM signal with a duty cycle determined by the value from 0–255.

```text
analogWrite()
      ↓
PWM signal
      ↓
Duty cycle
      ↓
LED brightness
```

---

## 10. Serial Monitor

The Serial Monitor displays the current brightness state and its corresponding PWM value.

Example:

```text
Brightness: 25% | PWM: 63
Brightness: 50% | PWM: 127
Brightness: 75% | PWM: 191
Brightness: 100% | PWM: 255
Brightness: 75% | PWM: 191
Brightness: 50% | PWM: 127
```

This makes the relationship between the program state and PWM output visible.

---

## 11. Complete Control Flow

```text
             ┌── Increase Button
             │
             ↓
        Button State
             │
             ↓
        HIGH → LOW?
             │
            YES
             ↓
       brightness += 25
             │
             ↓
       Limit to 100%
             │
             ├──────────────┐
             │              │
             ↓              ↓
        brightness      Decrease Button
             ↑              │
             │              ↓
             │         HIGH → LOW?
             │              │
             │             YES
             │              ↓
             │       brightness -= 25
             │              │
             │              ↓
             │         Limit to 0%
             │              │
             └──────┬───────┘
                    ↓
                  map()
                    ↓
                 PWM 0–255
                    ↓
              analogWrite()
                    ↓
                LED brightness
```

---

## 12. Key Takeaway

This project introduces **multiple inputs controlling the same program state**.

The two buttons perform opposite operations:

```text
Button 1 → increase brightness
Button 2 → decrease brightness
```

Both modify:

```text
brightness
```

The brightness state is then converted into a PWM value:

```text
Input
  ↓
Button state transition
  ↓
Change brightness state
  ↓
Limit state to 0–100%
  ↓
map()
  ↓
PWM 0–255
  ↓
analogWrite()
  ↓
LED brightness
```

The main programming concept is:

**Multiple inputs → shared state → processed output**
