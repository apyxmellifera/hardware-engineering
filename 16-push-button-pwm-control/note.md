# Push Button PWM Control — Engineering and Physics Notes

## 1. Project Overview

This project combines concepts from previous projects:

* Push button input
* `INPUT_PULLUP`
* Button state detection
* State transitions
* PWM
* `map()`
* LED brightness control

The push button is used to change the LED brightness each time it is pressed.

The brightness cycles through:

```text
0% → 25% → 50% → 75% → 100% → 0%
```

---

## 2. Push Button With `INPUT_PULLUP`

The button is connected between Arduino pin 11 and GND.

The Arduino uses its internal pull-up resistor:

```cpp
pinMode(pushButton, INPUT_PULLUP);
```

This produces the following behavior:

| Button      | Input |
| ----------- | ----: |
| Not pressed |  HIGH |
| Pressed     |   LOW |

The logic is inverted compared with using an external pull-down resistor.

---

## 3. Detecting a Single Press

The program stores the previous button state:

```text
lastButtonState
```

and reads the current state:

```text
currentButtonState
```

A button press is detected when the state changes from:

```text
HIGH → LOW
```

The condition is:

```cpp
if (lastButtonState == HIGH && currentButtonState == LOW)
```

This is called detecting a **state transition**.

After checking the button:

```cpp
lastButtonState = currentButtonState;
```

The current state becomes the previous state for the next loop.

### State sequence

```text
Not pressed
HIGH
  ↓
Button pressed
LOW
  ↓
HIGH → LOW detected
  ↓
Brightness changes
```

This allows one physical press to produce one brightness change without using `delay()`.

---

## 4. Brightness as State

The program needs to remember the current brightness.

That is why it uses:

```cpp
int brightness = 0;
```

The variable maintains its value between loop iterations.

Each detected button press increases the brightness:

```cpp
brightness += 25;
```

The sequence becomes:

```text
0
↓
25
↓
50
↓
75
↓
100
```

After 100%, the next press resets it:

```cpp
if (brightness > 100)
{
  brightness = 0;
}
```

Therefore:

```text
0% → 25% → 50% → 75% → 100% → 0%
```

---

## 5. Converting Percentage to PWM

Arduino's PWM output uses a value from:

```text
0–255
```

The project uses brightness percentages:

```text
0–100%
```

Therefore, the percentage must be converted to the PWM range.

The program uses:

```cpp
int pwmValue = map(brightness, 0, 100, 0, 255);
```

The mapping is:

```text
Brightness       PWM
0%       →       0
25%      →       63
50%      →       127
75%      →       191
100%     →       255
```

---

## 6. Mapping Calculation

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

So:

```text
PWM =
(brightness / 100) × 255
```

### 25%

```text
PWM = (25 / 100) × 255
PWM = 63.75
```

Arduino's integer result is approximately:

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

## 7. PWM and LED Brightness

The PWM output controls the average amount of power delivered to the LED.

The duty cycle is approximately:

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

The LED appears dimmer or brighter because the PWM signal changes how long the LED is ON during each cycle.

---

## 8. `analogWrite()`

The PWM value is sent to the LED using:

```cpp
analogWrite(led, pwmValue);
```

On the Arduino Uno, pin 9 supports PWM.

The important distinction is:

```text
analogRead()
    ↓
Reads an analog voltage
    ↓
0–1023
```

while:

```text
analogWrite()
    ↓
Outputs PWM
    ↓
0–255
```

This project therefore connects a digital button input to a PWM output.

---

## 9. Serial Monitor

The Serial Monitor allows the internal values of the program to be observed.

For example:

```text
Brightness: 25% | PWM: 63
Brightness: 50% | PWM: 127
Brightness: 75% | PWM: 191
Brightness: 100% | PWM: 255
Brightness: 0% | PWM: 0
```

This makes the relationship between the brightness state and PWM value visible.

---

## 10. Complete Control Flow

```text
Push Button
    ↓
digitalRead()
    ↓
Current button state
    ↓
Compare with previous state
    ↓
HIGH → LOW ?
    ↓
   YES
    ↓
Increase brightness by 25%
    ↓
0 → 25 → 50 → 75 → 100 → 0
    ↓
map()
    ↓
0–100 → 0–255
    ↓
analogWrite()
    ↓
PWM output
    ↓
LED brightness
```

---

## 11. Key Takeaway

The main new concept in this project is **state**.

The Arduino continuously runs `loop()`, so it needs variables to remember information between iterations.

In this project:

```text
Button state
    ↓
Detect transition
    ↓
Change brightness state
    ↓
Map percentage to PWM
    ↓
Control LED brightness
```

The project combines previously learned concepts into a larger control flow:

**Input → State Detection → State Change → Mapping → PWM Output**
