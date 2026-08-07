# Push Button (Internal Pull-Up)

## Demo Video

https://youtu.be/2klln0pTbxg

---

## Objective

* Learn how to read a digital input using a push button.
* Understand how the Arduino's internal pull-up resistor establishes a stable default input state.
* Understand the difference between Arduino digital input pins and output pins.
* Observe how pressing a push button changes the voltage at the Arduino input pin.
* Control an LED using software based on the state of the push button.
* Compare the internal pull-up configuration with external pull-up and pull-down circuits.

---

## Components

* Arduino Uno
* 1 LED
* 1 × 330 Ω resistor
* 1 Push button
* Breadboard
* Jumper wires

> **Note:** No external pull-up resistor is required because the Arduino provides one internally.

---

## Engineering Procedure

### LED Circuit

1. Connect the anode (+) of the LED to Arduino digital pin **12**.
2. Connect the cathode (-) of the LED to one end of the **330 Ω resistor**.
3. Connect the other end of the resistor to **Arduino GND**.

### Push Button Circuit

1. Connect one terminal of the push button to **Arduino digital pin 8**.
2. Connect the opposite terminal of the push button to **Arduino GND**.
3. Configure the input pin using:

```cpp
pinMode(pushButton, INPUT_PULLUP);
```

The Arduino automatically enables its internal pull-up resistor.

---

## Physics

### Power Source

The Arduino receives electrical power from the USB connection.

When configured as an output, the Arduino digital output pin supplies approximately **5 V** to the LED circuit whenever it is set **HIGH**.

For the push button circuit, the Arduino internally connects the input pin to **+5 V** through an internal pull-up resistor.

---

### Arduino Digital Input

When configured with:

```cpp
pinMode(pushButton, INPUT_PULLUP);
```

the Arduino input pin does **not** supply power.

Instead, it measures the voltage present at the input node.

* Approximately **5 V** is interpreted as **HIGH**.
* Approximately **0 V** is interpreted as **LOW**.

The internal pull-up resistor simply provides the input with a stable default voltage.

---

### Push Button Operation

The push button is a **momentary switch**.

When the button is **released**:

```text
HIGH
```

When the button is **pressed**, it connects the input directly to **ground**, causing the Arduino to read:

```text
LOW
```

---

### Current Flow

#### LED Circuit

Conventional current flows:

```text
Arduino Output → LED → 330 Ω Resistor → GND
```

The resistor limits the LED current and protects both the LED and the Arduino output pin.

---

#### Push Button Circuit

**Button Released**

```text
      +5V
       │
Internal Pull-up
       │
Arduino Input
```

The Arduino measures approximately **5 V**.

---

**Button Pressed**

```text
      +5V
       │
Internal Pull-up
       │
Arduino Input
       │
 Push Button
       │
      GND
```

The button connects the input node directly to **ground**.

The Arduino therefore measures approximately **0 V**.

---

### Why the Internal Pull-Up Is Needed

Digital input pins have a very high input impedance.

Without a pull-up or pull-down resistor, the input pin would float, allowing electrical noise to produce unpredictable HIGH and LOW readings.

The Arduino's internal pull-up resistor prevents this by keeping the input at a stable **HIGH** whenever the push button is not pressed.

---

### Why LED Polarity Is Important

An LED is a diode that allows current to flow primarily in one direction.

* The anode (+) should face the Arduino output pin.
* The cathode (-) should face the resistor and ground.

If connected in reverse, the LED becomes reverse-biased and will not illuminate under normal Arduino operating voltages.

---

## Observations

* The push button successfully controlled the Arduino input.
* The Arduino input measured **HIGH** when the button was released.
* The Arduino input measured **LOW** when the button was pressed.
* The LED responded according to the software logic.
* No external pull-up resistor was required.
* The internal pull-up resistor prevented the input from floating.
* The project demonstrated how software reacts to changes in hardware input.

---

## Software Engineering Insight

Unlike the previous LED projects, this program first reads an **input** before controlling an **output**.

The Arduino continuously measures the voltage on the push button input using:

```cpp
digitalRead(pushButton);
```

When the measured voltage becomes **LOW**, the software executes the programmed logic.

The Arduino then controls the LED using:

```cpp
digitalWrite(led, HIGH);
digitalWrite(led, LOW);
```

This project demonstrates one of the fundamental concepts of embedded systems:

```text
Read an Input → Make a Decision → Control an Output
```

---

## Why Use `INPUT_PULLUP`?

Using `INPUT_PULLUP` provides several practical advantages:

* Fewer components are needed because the pull-up resistor is built into the Arduino.
* Simpler wiring since no external resistor is required.
* Saves space on the breadboard.
* Reduces wiring mistakes.
* Suitable for many push-button applications.

The trade-off is that the internal pull-up resistor has a fixed resistance determined by the microcontroller (typically **20 kΩ–50 kΩ**), whereas an external resistor allows a specific resistance value to be chosen when needed.

---

## Files

* `code.ino` — Arduino source code
* `push-button-internal-pull-up.png` — Circuit screenshot
* `push-button-internal-pull-up-schema.png` — Schematic view
* `note.md` — Detailed engineering and physics notes
* `README.md` — Project documentation