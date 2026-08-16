# Push Button (Single-Press Toggle)

## Demo Video

https://youtu.be/QJy8_zyChto

---

## Objective

* Learn how to detect a button press using a digital input.
* Understand the Arduino's internal pull-up resistor.
* Understand active-low button logic.
* Learn how to detect a **state transition** rather than continuously reacting to a button's current state.
* Use a push button to toggle an LED ON and OFF.
* Understand how software maintains and changes state.
* Understand how one physical press can otherwise become multiple logical presses.

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

The switch is open, so the input is pulled toward +5 V.

```text
Input → HIGH
```

### Button Pressed

When the button is pressed, the switch closes and connects the input directly to ground.

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

The program does not simply check whether the button is currently LOW.

Instead, it compares the **previous button state** with the **current button state**.

```cpp
int lastButtonState = HIGH;
int currentButtonState = digitalRead(pushButton);
```

A press is detected when the state changes:

```text
HIGH → LOW
```

The condition is:

```cpp
if(lastButtonState == HIGH && currentButtonState == LOW)
```

This represents a single **press event**.

After processing the current state, the program stores it as the previous state:

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

then a button that remains pressed would cause the condition to be true repeatedly:

```text
LOW
LOW
LOW
LOW
LOW
LOW
...
```

The Arduino could therefore interpret **one physical press as many logical presses**.

> **The Arduino can interpret one physical press as many logical presses if the program reacts to the button's current state instead of detecting the transition between states.**

Tracking `lastButtonState` prevents this behavior.

The program only recognizes:

```text
HIGH → LOW
```

as a new press.

---

## LED Toggle Logic

The LED has its own stored state:

```cpp
bool ledState = false;
```

The two possible states are:

```text
false → LED OFF
true  → LED ON
```

When a press event occurs, the program checks the current LED state.

```text
             Press
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

The result is a toggle:

```text
1st press → LED ON
2nd press → LED OFF
3rd press → LED ON
4th press → LED OFF
...
```

---

## Software

```cpp
int led = 12;
int pushButton = 8;

int lastButtonState = HIGH;
bool ledState = false;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop()
{
  int currentButtonState = digitalRead(pushButton);

  if(lastButtonState == HIGH && currentButtonState == LOW){

    if(ledState == false) {
      digitalWrite(led, HIGH);
      ledState = true;
      Serial.println(ledState);
      Serial.println("---High---");
    }
    else {
      digitalWrite(led, LOW);
      ledState = false;
      Serial.println(ledState);
      Serial.println("---Low---");
    }
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
* The Arduino detected the transition from HIGH to LOW as a press event.
* The LED changed state once per physical press.
* Holding the button did not repeatedly toggle the LED.
* The `lastButtonState` variable prevented one physical press from becoming multiple logical presses.
* The `ledState` variable allowed the program to remember whether the LED was currently ON or OFF.
* The Serial Monitor was useful for observing the state changes during debugging.

---

## Software Engineering Insight

This project introduces an important programming concept: **state**.

The program maintains two pieces of state:

```text
Button state
LED state
```

The button state allows the program to detect an event:

```text
HIGH → LOW = Press
```

The LED state allows the program to remember what should happen next:

```text
OFF + Press → ON
ON  + Press → OFF
```

This is different from simply reacting to the current button state.

The project therefore follows:

```text
Read Input
     ↓
Detect State Transition
     ↓
Recognize Press Event
     ↓
Read Stored LED State
     ↓
Change LED State
     ↓
Control Output
     ↓
Store New Button State
```

This pattern is an important foundation for more advanced embedded-system behavior such as **double-click detection, multiple-press detection, debouncing, timers, and event-driven systems**.

---

## Key Engineering Lesson

> **A physical action and a software event are not necessarily the same thing.**

A human may press the button once, but the Arduino executes its loop thousands of times while that button remains physically pressed.

Therefore, software must decide **what constitutes an event**.

In this project:

```text
HIGH → LOW
```

is defined as one press event.

That distinction between a **continuous state** and a **discrete event** is one of the most important concepts introduced by this project.

---

## Files

* `code.ino` — Arduino source code
* `push-button-single-press-toggle.png` — Circuit screenshot
* `push-button-single-press-toggle-schema.png` — Schematic view
* `note.md` — Detailed engineering and physics notes
* `README.md` — Project documentation
