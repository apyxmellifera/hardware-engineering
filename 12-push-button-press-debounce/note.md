# Engineering and Physics Notes

## Components

1. Arduino Uno
2. One LED
3. One 330 Ω resistor
4. One push button
5. Breadboard
6. Jumper wires

---

## 1. Project Context

This project builds on the previous push-button projects.

Previous projects taught the Arduino how to interpret:

```text
Button state
     ↓
Press event
     ↓
Timing
     ↓
Long press
     ↓
Output state
```

Project 12 introduces a new problem:

> **A physical button can produce an unstable electrical signal when its contacts change state.**

The purpose of debouncing is to make sure the software interprets one physical action as one reliable logical event.

---

## 2. Mechanical Button Behavior

A push button is a mechanical switch.

Ideally, when the button is pressed, the electrical signal would change directly:

```text
HIGH ──────────────────┐
                       │
                       └──────── LOW
```

However, the mechanical contacts can briefly make and break contact while moving together.

Conceptually, the Arduino could see:

```text
HIGH ─────────┐
              ↓
              LOW
              ↑
              HIGH
              ↓
              LOW
              ↑
              HIGH
              ↓
              LOW ───────────────
```

These rapid changes are called **switch bounce**.

The user performed only one physical press, but the Arduino may temporarily observe multiple electrical transitions.

---

## 3. Raw Button Reading

The Arduino continuously reads the button using:

```text
digitalRead()
```

The reading is a **raw state**.

With the internal pull-up configuration:

```text
Released → HIGH
Pressed  → LOW
```

The raw reading may change rapidly during a mechanical transition.

Therefore:

```text
Raw reading ≠ automatically confirmed state
```

The program needs a way to determine when the signal has become stable.

---

## 4. The Debounce Problem

The fundamental problem is:

```text
One physical press
        ↓
Possibly multiple electrical transitions
        ↓
Arduino reads several changes
        ↓
Software may interpret them as several events
```

Without debouncing:

```text
Physical press
     ↓
LOW → HIGH → LOW → HIGH → LOW
     ↓
Potentially multiple logical events
```

With debouncing:

```text
Physical press
     ↓
Unstable signal
     ↓
Wait for stability
     ↓
Stable LOW
     ↓
ONE confirmed press
```

The purpose of debouncing is therefore not to change the button's electrical behavior.

It changes how the **software interprets the signal**.

---

## 5. Detecting a Raw State Change

The program keeps track of the previous raw reading.

Conceptually:

```text
previous raw state
        ↓
current raw state
        ↓
are they different?
```

If:

```text
currentButtonState != lastButtonState
```

the raw signal has changed.

This does not immediately mean that the button has produced a valid event.

It means:

> **"Something changed. Start observing it."**

---

## 6. Starting the Debounce Timer

When a raw state change is detected, the program records the current time.

```text
State change detected
        ↓
record current time
        ↓
start debounce period
```

The timestamp represents the beginning of the period during which the program waits for the signal to stabilize.

The debounce interval used in this project is:

```text
50 ms
```

Therefore:

```text
State change
     ↓
wait 50 ms
     ↓
check whether the signal remained stable
```

---

## 7. Why `millis()` Is Used

The program uses `millis()` to measure the debounce interval without stopping the main program.

Conceptually:

```text
currentTime - lastDebounceTime
```

When the result reaches:

```text
50 ms
```

the program can evaluate whether the new state has remained stable.

This is **non-blocking timing**.

The Arduino continues executing `loop()` while the debounce period passes.

---

## 8. Confirming a Stable State

After the debounce interval has elapsed, the program checks whether the current raw reading represents a new stable state.

Conceptually:

```text
Raw state changed
       ↓
Start timer
       ↓
Wait 50 ms
       ↓
Has the signal remained stable?
       ↓
YES
       ↓
Confirm new state
```

Only after this confirmation does the program treat the change as meaningful.

This prevents short-lived fluctuations from being interpreted as valid button events.

---

## 9. Raw State vs Stable State

This project introduces an important distinction between two types of state.

### Raw state

The state currently being read directly from the input pin:

```text
HIGH / LOW
```

It may temporarily fluctuate.

### Stable state

The state that the software has accepted after the debounce period.

```text
RAW INPUT
    ↓
debounce
    ↓
STABLE INPUT
```

The program therefore maintains:

```text
lastButtonState
        ↓
previous raw reading

stableButtonState
        ↓
confirmed button state
```

These variables have different responsibilities.

---

## 10. Confirmed Press

When the new stable state becomes:

```text
LOW
```

the program can conclude:

```text
A valid button press occurred.
```

The sequence becomes:

```text
HIGH
 ↓
raw change detected
 ↓
start debounce timer
 ↓
wait 50 ms
 ↓
still LOW
 ↓
confirm LOW
 ↓
VALID PRESS
```

The LED can then respond to this confirmed state.

---

## 11. Confirmed Release

Debouncing applies to both directions of the switch.

The program must also handle:

```text
LOW → HIGH
```

when the button is released.

The process is the same:

```text
LOW
 ↓
raw change detected
 ↓
start debounce timer
 ↓
wait 50 ms
 ↓
still HIGH
 ↓
confirm HIGH
 ↓
VALID RELEASE
```

Therefore, both pressing and releasing the button can be debounced.

---

## 12. Preventing Repeated Events

The Arduino's `loop()` executes continuously.

Once a button state has been confirmed, the program should not repeatedly generate the same event on every loop iteration.

For example:

```text
Button pressed
      ↓
confirm LOW
      ↓
ONE valid press
      ↓
button remains LOW
      ↓
no additional press events
```

The stable state acts as a record of what the program has already accepted.

This prevents one continuous button state from being interpreted as multiple events.

---

## 13. Software and Hardware Interaction

The complete process is:

```text
Physical button
      ↓
Mechanical contacts move
      ↓
Electrical signal changes
      ↓
Arduino reads raw signal
      ↓
Possible bounce
      ↓
Software detects change
      ↓
Start debounce timer
      ↓
Wait 50 ms
      ↓
Check stability
      ↓
Confirm stable state
      ↓
Generate valid event
      ↓
Control LED
```

The hardware produces the physical signal.

The software determines whether that signal is stable enough to trust.

---

## 14. Tinkercad Limitation

This project is primarily about understanding how real mechanical buttons behave.

Tinkercad may not reproduce realistic mechanical contact bounce exactly as a physical push button does.

Therefore, the simulation may appear to produce a clean:

```text
HIGH → LOW
```

transition without visibly showing:

```text
HIGH → LOW → HIGH → LOW
```

However, the debounce algorithm is still useful because it models how embedded software handles unstable physical inputs.

The physical Arduino button can make the effect more apparent.

---

## 15. Engineering Observation

A digital input is not automatically a perfect logical event.

The Arduino receives an electrical signal, while the software needs to interpret that signal.

This creates an important boundary:

```text
Physical world
      ↓
Electrical signal
      ↓
Raw software reading
      ↓
Signal validation
      ↓
Logical event
```

Debouncing is an example of software compensating for imperfections in the physical world.

---

## 16. Project Progression

```text
08 — Single-Press Toggle
        ↓
Press event + persistent state

09 — Double-Press Toggle
        ↓
Multiple events + timing

10 — Long-Press LED
        ↓
Press duration + event detection

11 — Long-Press Toggle
        ↓
Long-press event + persistent state

12 — Push Button Debouncing
        ↓
Raw input + signal stabilization + confirmed state
```

Project 12 adds an important layer between **reading an input** and **trusting an input**.

---

## 17. Key Engineering Lesson

A physical input is not always a clean software event.

The program must sometimes validate the signal before accepting it.

The key idea is:

> **Debouncing converts an unstable physical switch transition into a reliable logical state change.**

The overall pattern is:

```text
RAW INPUT
    ↓
DETECT CHANGE
    ↓
WAIT
    ↓
VERIFY STABILITY
    ↓
CONFIRM STATE
    ↓
VALID EVENT
    ↓
OUTPUT
```

This pattern is fundamental to embedded systems because software often has to deal with imperfect signals produced by real physical hardware.
