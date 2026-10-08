# Potentiometer Button Mode Control

## 1. Overview

This project combines two previously learned methods of controlling LED brightness:

* Potentiometer control
* Two-button brightness control

A third push button is introduced to switch between the two control modes.

The LED remains connected to PWM pin 9, but the source controlling its brightness changes depending on the current mode.

The project therefore introduces the idea of **operating modes** and **program state**.

---

## 2. Project Objective

Learn how to:

* Use a potentiometer to control LED brightness.
* Use two push buttons to increase and decrease LED brightness.
* Use a third button to switch between control modes.
* Store the current mode in a variable.
* Use conditional logic to determine which control system is active.
* Maintain button state tracking for single-press detection.
* Convert analog and percentage values into PWM output.

---

## 3. Hardware

* Arduino Uno
* 1 × 10 kΩ potentiometer
* 3 × push buttons
* 1 × LED
* 1 × 330 Ω resistor
* Breadboard
* Jumper wires

---

## 4. Circuit

### Potentiometer

* Pin 1 → Arduino 5V
* Pin 2 (wiper) → Arduino A0
* Pin 3 → Arduino GND

The potentiometer provides a variable voltage between approximately 0 V and 5 V.

### Push Buttons

* Button 1 → Arduino pin 10
* Button 2 → Arduino pin 11
* Button 3 → Arduino pin 12
* Other leg of each button → Arduino GND

All three buttons use the Arduino's internal pull-up resistors with `INPUT_PULLUP`.

### LED

* Arduino pin 9 → LED anode
* LED cathode → 330 Ω resistor → Arduino GND

Pin 9 is a PWM-capable pin.

---

## 5. Control Modes

The program has two modes.

### Mode 1 — Button Control

Buttons 1 and 2 control brightness.

```text
Button 1 → Increase brightness
Button 2 → Decrease brightness
```

Brightness is represented as a percentage from 0–100%.

Each button press changes the brightness by 25%.

```text
0 → 25 → 50 → 75 → 100
```

The brightness is limited so that it cannot exceed 100% or fall below 0%.

The percentage is then converted to the PWM range:

```text
0–100% → 0–255
```

---

### Mode 2 — Potentiometer Control

The potentiometer directly controls the LED brightness.

```text
Potentiometer
      ↓
 analogRead()
      ↓
   0–1023
      ↓
    map()
      ↓
   0–255
      ↓
 analogWrite()
      ↓
    LED
```

The potentiometer position determines the PWM value.

---

## 6. Mode Switching

Button 3 controls the current mode.

The program stores the mode in:

```cpp
int mode = 1;
```

The program uses:

```text
1 = Button mode
2 = Potentiometer mode
```

Each single press of Button 3 increases the mode:

```text
1 → 2
```

When the value goes beyond 2, the program returns to mode 1:

```text
1 → 2 → 1 → 2 → 1
```

This creates a repeating two-mode system.

---

## 7. Program State

The `mode` variable represents the current state of the control system.

The Arduino does not simply read an input and immediately forget it. It stores information that determines how the program should behave.

For example:

```text
mode = 1
```

means the buttons are currently controlling brightness.

```text
mode = 2
```

means the potentiometer is currently controlling brightness.

The same physical inputs can therefore behave differently depending on the stored state.

---

## 8. Button State Detection

The buttons use:

```cpp
INPUT_PULLUP
```

With the internal pull-up resistor:

```text
Button not pressed → HIGH
Button pressed     → LOW
```

The program stores the previous button state and compares it with the current state.

A single press is detected when:

```text
Previous = HIGH
Current  = LOW
```

This is a `HIGH → LOW` transition.

The same method is used for all three buttons.

Button 3 therefore switches modes once per press rather than continuously switching modes while the button is held.

---

## 9. Brightness and PWM

In button mode, brightness is represented as a percentage:

```text
0–100%
```

Arduino PWM uses:

```text
0–255
```

Therefore the percentage must be mapped to the PWM range.

```cpp
int pwmValue = map(brightness, 0, 100, 0, 255);
```

Examples:

```text
0%   → 0
25%  → approximately 64
50%  → approximately 128
75%  → approximately 191
100% → 255
```

The PWM value is then sent to the LED using:

```cpp
analogWrite(led, pwmValue);
```

---

## 10. Potentiometer and ADC

The potentiometer is connected to analog pin A0.

`analogRead()` on the Arduino Uno produces a 10-bit ADC value:

```text
0–1023
```

This value represents the position of the potentiometer.

The value is mapped directly to the PWM range:

```cpp
int pwmValue = map(potValue, 0, 1023, 0, 255);
```

Therefore:

```text
Potentiometer
0 V        → ADC 0    → PWM 0
~2.5 V     → ADC ~512 → PWM ~127
5 V        → ADC 1023 → PWM 255
```

The LED brightness follows the potentiometer position.

---

## 11. Control Flow

The overall program follows this sequence:

```text
Start
  ↓
Initialize inputs and LED
  ↓
Read current button states
  ↓
Check Button 3
  ↓
Change mode if Button 3 was pressed
  ↓
Check current mode
  ↓
 ┌─────────────────────┐
 │                     │
Mode 1              Mode 2
 │                     │
 ↓                     ↓
Buttons             Potentiometer
 │                     │
 ↓                     ↓
Brightness           ADC value
 │                     │
 ↓                     ↓
PWM                  PWM
 │                     │
 └──────────┬──────────┘
            ↓
           LED
            ↓
Update previous button states
            ↓
          Repeat
```

Only the control system belonging to the active mode operates the LED.

---

## 12. Why Only One Control System Runs

The project avoids the problem of having two different inputs trying to control the LED at the same time.

Instead:

```text
Mode 1 → Buttons control LED
Mode 2 → Potentiometer controls LED
```

This gives the LED one active control source at a time.

The mode variable determines which control path is allowed to operate.

---

## 13. Important Concepts Learned

* Multiple inputs
* Analog input
* Digital input
* `analogRead()`
* ADC
* `digitalRead()`
* `INPUT_PULLUP`
* `HIGH → LOW` transition
* Previous and current button state
* Program state
* Operating mode
* Mode switching
* Conditional logic
* `if`
* `map()`
* PWM
* `analogWrite()`
* Shared output
* State-dependent behavior

---

## 14. Key Takeaway

The most important concept in this project is **mode-dependent control**.

The LED has one output, but different inputs can control it depending on the current mode.

```text
              Mode
               ↓
        ┌──────┴──────┐
        ↓             ↓
     Buttons          Pot
        ↓             ↓
   Brightness       Brightness
        ↓             ↓
        └──────┬──────┘
               ↓
              PWM
               ↓
              LED
```

The important programming pattern is:

> **Input → State/Mode → Decision → Output**
