# Push Button (Double-Press Toggle)

## Demo Video
https://youtu.be/HOribXXF5BA

---

## Objective

* Learn how to detect individual button press events using a digital input.

* Understand the Arduino's internal pull-up resistor.

* Understand active-low button logic.

* Detect a **state transition** rather than continuously reacting to a button's current state.

* Count multiple button press events.

* Use `millis()` to measure elapsed time.

* Detect a **double press** when two valid press events occur within a defined time interval.

* Use a double press to toggle an LED ON and OFF.

* Understand non-blocking timing.

* Understand timeout handling when the second press occurs too late.

* Understand how software can combine multiple physical events into a higher-level event.

---

## Components

* Arduino Uno

* 1 LED

* 1 × 330 Ω resistor

* 1 Push button

* Breadboard

* Jumper wires

---

## Engineering Procedure

### LED Circuit

1. Connect the anode (+) of the LED to Arduino digital output pin 12.

2. Connect the cathode (-) of the LED to one end of the 330 Ω resistor.

3. Connect the other end of the resistor to Arduino GND.

### Push Button Circuit

1. Connect one terminal of the push button to Arduino GND.

2. Connect the opposite terminal to Arduino digital input pin 8.

3. Configure the input pin using:

```cpp
pinMode(pushButton, INPUT_PULLUP);
```

The Arduino's internal pull-up resistor provides the default HIGH state, so no external pull-up resistor is required.

---

## Circuit Behavior

The button uses **active-low logic** because the internal pull-up keeps the input HIGH when the button is released.

### Button Released

When the button is released, the switch is open.

```text
Internal Pull-Up
       │
      +5V
       │
       R
       │
Input Pin ──── Push Button ──── GND
                  OPEN
```

The input is pulled toward +5 V.

```text
Input → HIGH
```

### Button Pressed

When the button is pressed, the switch closes and connects the input to ground.

```text
Internal Pull-Up
       │
      +5V
       │
       R
       │
Input Pin
       │
   Push Button
       │
      GND
```

The input becomes approximately 0 V.

```text
Input → LOW
```

Therefore:

```text
Released → HIGH
Pressed  → LOW
```

---

## Press Event Detection

The program detects a new press by comparing the **previous button state** with the **current button state**.

```cpp
int lastButtonState = HIGH;

int currentButtonState = digitalRead(pushButton);
```

A press occurs when:

```text
HIGH → LOW
```

The condition is:

```cpp
if(lastButtonState == HIGH && currentButtonState == LOW)
```

This represents one **press event**.

After processing the current state, the program stores it:

```cpp
lastButtonState = currentButtonState;
```

This allows the program to distinguish between:

```text
Button remains pressed
```

and:

```text
Button has just been pressed
```

---

## Why State Tracking Is Important

The Arduino continuously executes `loop()`.

If the program only checked:

```cpp
if(currentButtonState == LOW)
```

then holding the button down would produce:

```text
LOW
LOW
LOW
LOW
LOW
LOW
...
```

The Arduino could therefore interpret one physical press as many logical presses.

> **The Arduino can interpret one physical press as many logical presses if the program reacts to the button's current state instead of detecting the transition between states.**

Tracking `lastButtonState` ensures that only the transition:

```text
HIGH → LOW
```

is recognized as a new press event.

---

## Press Counting

A double press requires two separate press events.

The program keeps track of how many valid presses have occurred:

```cpp
int pressCount = 0;
```

The counter represents the current sequence:

```text
0 → No press

1 → First press detected

2 → Second press detected
```

When a press event occurs:

```cpp
pressCount++;
```

The program can then determine whether it has received the first or second press.

---

## Measuring Time with `millis()`

Counting two presses is not enough to detect a double press.

The program must also determine **how much time passed between the two presses**.

Arduino provides:

```cpp
millis()
```

which returns the number of milliseconds that have passed since the program started.

The current time can be stored as:

```cpp
unsigned long currentTime = millis();
```

When the first press occurs, its time is stored:

```cpp
firstPressTime = currentTime;
```

When the second press occurs, the elapsed time is calculated:

```cpp
currentTime - firstPressTime
```

For example:

```text
First press  → 2500 ms
Second press → 3100 ms

3100 - 2500 = 600 ms
```

The two presses were therefore 600 milliseconds apart.

---

## Double-Press Time Window

The program defines how much time is allowed between the two presses:

```cpp
const unsigned long doublePressInterval = 1000;
```

This creates a 1000 ms double-press window.

```text
First press
    │
    │<--------- 1000 ms --------->│
    │                              │
    └────── Double-press window ──┘
```

If the second press occurs within the window:

```text
First press → Second press
       < 1000 ms
            ↓
     Double press detected
```

If the second press occurs after the window:

```text
First press →────────────→ Second press
             > 1000 ms
                    ↓
              Too late
```

The second press is not considered part of the original double press.

---

## Non-Blocking Timing

The project uses `millis()` rather than `delay()` to measure time.

`delay()` pauses the program:

```cpp
delay(1000);
```

During the delay, normal program execution is blocked.

With `millis()`, the Arduino can continue executing its loop while checking whether enough time has passed.

```text
Read input
    ↓
Check events
    ↓
Check elapsed time
    ↓
Update output
    ↓
Repeat
```

This is called **non-blocking timing**.

Non-blocking timing is important when an embedded system needs to remain responsive while waiting for an event.

---

## Double-Press Detection

The complete sequence is:

```text
Button press
     ↓
Detect HIGH → LOW
     ↓
First press
     ↓
Record time
     ↓
Wait for another press
     ↓
Second press
     ↓
Calculate elapsed time
     ↓
Within double-press interval?
       /          \
     YES           NO
      ↓             ↓
Double press    Too late
      ↓             ↓
Toggle LED      Reset sequence
      ↓
Reset counter
```

A double press is therefore a **software-defined event** created from two individual press events and a time constraint.

---

## LED Toggle Logic

The LED has a stored state:

```cpp
bool ledState = false;
```

The two possible states are:

```text
false → LED OFF

true  → LED ON
```

The LED only changes state after a valid double press.

```text
              Double Press
                   ↓
            ┌──────────────┐
            │  LED state?  │
            └──────────────┘
              ↓          ↓
            OFF          ON
              ↓          ↓
           Turn ON    Turn OFF
              ↓          ↓
             ON          OFF
```

The expected behavior is:

```text
Initial state → LED OFF

Single press
             → LED OFF

Double press
             → LED ON

Single press
             → LED ON

Double press
             → LED OFF
```

---

## Timeout Handling

The first press cannot remain pending forever.

If the second press does not occur within the allowed interval, the current sequence is cancelled.

```text
First press
     ↓
Start timer
     ↓
Wait for second press
     ↓
Time limit exceeded
     ↓
Reset press count
     ↓
Wait for a new first press
```

The program resets:

```cpp
pressCount = 0;
```

This creates a **timeout**.

Timeout handling prevents an old press from being incorrectly combined with a much later press.

---

## Software

```cpp
int led = 12;
int pushButton = 8;

int lastButtonState = HIGH;
bool ledState = false;

unsigned long firstPressTime = 0;
const unsigned long doublePressInterval = 1000;

int pressCount = 0;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop()
{
  int currentButtonState = digitalRead(pushButton);
  unsigned long currentTime = millis();

  // Detect button press: HIGH -> LOW
  if (lastButtonState == HIGH && currentButtonState == LOW)
  {
    pressCount++;
    Serial.println("Button pressed");

    if (pressCount == 1)
    {
      // First press
      firstPressTime = currentTime;

      Serial.println("First press");
    }
    else if (pressCount == 2)
    {
      // Second press
      if (currentTime - firstPressTime <= doublePressInterval)
      {
        // Double press detected
        ledState = !ledState;
        digitalWrite(led, ledState ? HIGH : LOW);

        Serial.println("DOUBLE PRESS");
        Serial.println(ledState ? "LED ON" : "LED OFF");

        pressCount = 0;
      }
      else
      {
        // First press was too long ago.
        // Treat this as a new first press.
        firstPressTime = currentTime;
      }
    }
  }

  // If the second press doesn't happen within the time limit,
  // reset the counter.
  if (pressCount == 2 &&
      currentTime - firstPressTime > doublePressInterval)
  {
    pressCount = 0;
    Serial.println("Double press timeout");
  }

  lastButtonState = currentButtonState;
}
```

---

## Physics

### LED Current

When the LED is ON, conventional current flows:

```text
Arduino Output Pin
        ↓
       LED
        ↓
   330 Ω Resistor
        ↓
       GND
```

The 330 Ω resistor limits the current flowing through the LED and protects the LED and Arduino output pin.

### LED Polarity

The LED is a diode and therefore conducts primarily in one direction.

* Anode (+) → Arduino output
* Cathode (-) → resistor → GND

Reversing the LED causes it to become reverse-biased, so it normally does not illuminate under the Arduino's operating voltage.

---

## Observations

* The internal pull-up established a default HIGH input state.

* Pressing the button changed the input to LOW.

* The Arduino detected the HIGH → LOW transition as a press event.

* Individual presses were counted by the program.

* The time of the first press was stored using `millis()`.

* The elapsed time between presses was used to determine whether two presses formed a double press.

* A double press toggled the LED.

* A single press did not toggle the LED.

* A second press occurring after the time window caused the pending sequence to time out.

* The `lastButtonState` variable prevented one physical press from becoming multiple logical presses.

* The `ledState` variable allowed the program to remember whether the LED was currently ON or OFF.

* The Serial Monitor was useful for observing press events, double presses, and timeout behavior during debugging.

---

## Software Engineering Insight

This project extends the concept of **state** introduced in the previous project.

The program now maintains several pieces of state:

```text
Button state
LED state
Press count
First press time
```

Each piece of state answers a different question:

```text
lastButtonState
→ What was the button doing previously?

pressCount
→ How many presses are currently in the sequence?

firstPressTime
→ When did the sequence begin?

ledState
→ Is the LED currently ON or OFF?
```

The program combines these pieces of information to determine what the user is doing.

```text
Current Input
      +
Previous State
      +
Press Count
      +
Elapsed Time
      +
LED State
      ↓
System Behavior
```

This is an important step toward **event-driven embedded systems**.

---

## Key Engineering Lesson

> **A higher-level software event can be created by combining multiple lower-level physical events with time.**

A physical button produces electrical state changes.

The Arduino detects those state changes.

The software converts the transitions into individual press events.

The program then combines two press events that occur within a defined time window:

```text
HIGH → LOW
     ↓
Press 1
     ↓
Time window
     ↓
HIGH → LOW
     ↓
Press 2
     ↓
Double Press
```

Therefore, a **double press is not a special electrical state produced by the button**.

It is a higher-level event created by software.

This distinction between:

```text
Physical state
     ↓
Software event
     ↓
Higher-level event
```

is an important foundation for more advanced embedded systems.

---

## Project Progression

This project builds directly on the previous projects:

```text
Digital Input
     ↓
Pull-Up / Pull-Down
     ↓
Internal Pull-Up
     ↓
State Detection
     ↓
Press Event Detection
     ↓
Single-Press Toggle
     ↓
Press Counting
     ↓
Time Measurement
     ↓
Double-Press Detection
     ↓
Timeout Handling
```

The project therefore introduces a new dimension to the previous state-based logic:

> **State + Events + Time**

These concepts provide a foundation for more advanced input handling such as:

* Debouncing
* Long-press detection
* Triple-click detection
* Multiple-press detection
* Menu navigation
* Timers
* State machines
* Event-driven systems

---

## Files

* `code.ino` — Arduino source code

* `push-button-double-press-toggle.png` — Circuit screenshot

* `push-button-double-press-toggle-schema.png` — Schematic view

* `note.md` — Detailed engineering and physics notes

* `README.md` — Project documentation
