# Engineering and Physics Notes

## Components

1. Arduino Uno
2. One LED
3. One 330 Ω resistor (LED current limiting)
4. One push button
5. Breadboard
6. Jumper wires

---

## 1. Project Context

This project builds directly on the previous push-button projects.

Project 10 introduced **long-press detection**:

```text
Press → Hold → 1 second → Long Press
```

Project 11 uses that long press as an **event that toggles the LED state**.

The main new concept is the separation between:

```text
Input state
      ↓
Event
      ↓
Output state
```

---

## 2. Button Input

The button uses the Arduino's internal pull-up resistor:

```cpp
pinMode(pushButton, INPUT_PULLUP);
```

Therefore:

```text
Released → HIGH
Pressed  → LOW
```

The button is active-low because pressing it connects the input pin to GND.

The program detects the beginning of a press using the state transition:

```text
HIGH → LOW
```

This distinguishes a new press from a button that is already being held.

---

## 3. Detecting the Long Press

When the button transitions from HIGH to LOW, the program records the starting time.

```text
HIGH → LOW
      ↓
Start timer
```

While the button remains LOW, the program measures how much time has passed.

Conceptually:

```text
elapsedTime = currentTime - pressStartTime
```

The long-press threshold is:

```text
1000 ms = 1 second
```

Therefore:

```text
Button LOW
    +
elapsedTime ≥ 1000 ms
    ↓
LONG PRESS EVENT
```

The long press is not a special electrical signal.

It is a **software interpretation of the button remaining pressed for a defined period of time**.

---

## 4. Long Press as an Event

The important change from Project 10 is what happens after the long press is detected.

Project 10:

```text
Long press → LED ON
Release    → LED OFF
```

Project 11:

```text
Long press → Toggle LED
Release    → LED keeps its state
```

The long press is therefore treated as a **discrete event** rather than simply a condition that directly controls the LED.

---

## 5. Toggle Logic

A toggle changes a Boolean state to its opposite value.

```text
false → true
true  → false
```

This can be represented logically as:

```text
ledState = !ledState;
```

Therefore:

```text
LED OFF
   ↓
Long press
   ↓
LED ON
```

and:

```text
LED ON
   ↓
Long press
   ↓
LED OFF
```

Each valid long press produces one state change.

---

## 6. Persistent LED State

The LED state is independent of the button's current state.

For example:

```text
Button pressed
      ↓
Long press detected
      ↓
Toggle LED state
      ↓
Button released
      ↓
LED remains in new state
```

This is different from Project 10, where the LED directly followed the button interaction.

The program therefore maintains two separate concepts:

```text
Button state
    ↓
What is the user doing?

LED state
    ↓
What state should the output remain in?
```

This separation is an important software design concept.

---

## 7. Preventing Repeated Toggles

The Arduino executes `loop()` continuously.

Once the button has been held for one second, the long-press condition can remain true:

```text
LONG PRESS
LONG PRESS
LONG PRESS
LONG PRESS
...
```

If the program toggled the LED every time the condition was checked, one physical long press could toggle the LED repeatedly.

The desired behavior is:

```text
Hold
 ↓
1 second reached
 ↓
ONE long-press event
 ↓
ONE toggle
 ↓
Keep holding
 ↓
No additional toggle
```

Therefore, the program must distinguish between:

```text
Long press has just occurred
```

and:

```text
Button is still being held after the long press
```

This is the same fundamental distinction between a **state** and an **event** introduced in the earlier projects.

---

## 8. Long-Press Toggle Algorithm

```text
Read button
     ↓
Detect HIGH → LOW
     ↓
Start timer
     ↓
Keep holding
     ↓
Measure elapsed time
     ↓
1 second reached?
     ↓
    YES
     ↓
Long press event
     ↓
Toggle LED state
     ↓
Keep holding
     ↓
LED remains in new state
     ↓
Release
     ↓
LED remains unchanged
```

A later long press repeats the same process.

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

---

## 9. Current State vs Output State

This project demonstrates that an input state and an output state do not have to be directly coupled.

The button provides:

```text
HIGH / LOW
```

The software interprets that information together with time:

```text
HIGH → LOW
     +
1 second held
     ↓
LONG PRESS
```

The long press then changes the independent LED state:

```text
LED OFF → LED ON
```

or:

```text
LED ON → LED OFF
```

This gives the system the structure:

```text
INPUT
  ↓
EVENT
  ↓
STATE CHANGE
  ↓
OUTPUT
```

---

## 10. Software and Hardware Interaction

The complete interaction is:

```text
Physical button press
        ↓
Electrical state changes
        ↓
Arduino reads LOW
        ↓
Press transition detected
        ↓
Timer starts
        ↓
Button remains LOW
        ↓
Elapsed time reaches 1 second
        ↓
Long-press event
        ↓
LED state toggles
        ↓
Arduino output changes
        ↓
LED changes state
```

The hardware provides the physical input and output.

The software provides the interpretation, timing, event detection, and state management.

---

## 11. LED Circuit

The LED is connected through a 330 Ω current-limiting resistor.

```text
Arduino Output Pin → LED → 330 Ω Resistor → GND
```

Conventional current flows from the Arduino output toward GND.

The LED is polarity-sensitive:

```text
Longer lead → Anode (+)
Shorter lead → Cathode (-)
```

The resistor limits the current flowing through the LED.

---

## 12. Engineering Observation

The physical button is still only a simple binary device:

```text
HIGH / LOW
```

However, software can turn that simple signal into a higher-level interaction:

```text
Button state
     ↓
Press event
     ↓
Time measurement
     ↓
Long-press event
     ↓
State transition
     ↓
LED output
```

This demonstrates how embedded systems create sophisticated behavior by combining **state, timing, and event processing**.

---

## 13. Project Progression

```text
08 — Single-Press Toggle
      ↓
Press event + persistent LED state

09 — Double-Press Toggle
      ↓
Multiple events + timing

10 — Long-Press LED
      ↓
Press duration + long-press detection

11 — Long-Press Toggle
      ↓
Long-press event + persistent state change
```

Project 11 combines the concepts learned so far into a more complete event-driven interaction.

---

## 14. Key Engineering Lesson

A button does not directly mean "turn the LED on" or "turn the LED off."

The software decides what a physical action means.

In this project:

```text
Physical action
      ↓
Button state
      ↓
Time measurement
      ↓
Long-press event
      ↓
Toggle persistent state
      ↓
Output changes
```

The key idea is:

> **A long press can be treated as a discrete event that changes an independent output state.**

This separation between **input state**, **event detection**, and **output state** is a fundamental pattern in embedded systems and interactive software.
