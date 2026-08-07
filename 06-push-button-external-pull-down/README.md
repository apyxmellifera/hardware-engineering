# Push Button (External Pull-Down)

## Demo Video

https://youtu.be/2klln0pTbxg

---

## Objective

* Learn how to read a digital input using a push button.
* Understand how an external pull-down resistor establishes a stable default input state.
* Understand how an Arduino digital input pin detects voltage rather than supplying power.
* Observe how pressing a push button changes the voltage at the Arduino input pin.
* Control an LED using software based on the state of the push button.
* Understand the relationship between hardware inputs and software decision-making.

---

## Components

* Arduino Uno
* 1 LED
* 1 × 330 Ω resistor
* 1 Push button
* 1 × 10 kΩ resistor (external pull-down)
* Breadboard
* Jumper wires

---

## Engineering Procedure

### Circuit Connections

#### LED Circuit

1. Connect the anode (+) of the LED to the Arduino digital output pin.
2. Connect the cathode (-) of the LED to one end of the 330 Ω resistor.
3. Connect the other end of the resistor to Arduino GND.

#### Push Button Circuit

1. Connect one terminal of the push button to the Arduino **5 V** pin.
2. Connect the opposite terminal of the push button to the Arduino input pin.
3. Connect a **10 kΩ resistor** between the Arduino input pin and **Arduino GND**.

This creates an **external pull-down resistor** configuration.

---

## Physics

### Power Source

The Arduino receives electrical power from the USB connection.

The digital output pin supplies approximately **5 V** to the LED circuit whenever it is set **HIGH**.

The push button circuit also uses the Arduino's **5 V** supply, while the external pull-down resistor provides a stable default voltage for the input pin.

---

### Arduino Digital Input

The Arduino input pin does **not** provide electrical power.

Instead, it measures the voltage present at the node to which it is connected.

* Approximately **0 V** is interpreted as **LOW**.
* Approximately **5 V** is interpreted as **HIGH**.

Because the input pin has a very high input impedance, it draws negligible current and behaves like a voltage sensor.

---

### Push Button Operation

The push button is a **momentary switch**.

When the button is **not pressed**, the switch remains open.

The 10 kΩ resistor connects the input node to **ground (0 V)**, causing the Arduino to read:

```text
LOW
```

When the button is **pressed**, the switch closes and connects the same input node directly to **+5 V**.

The Arduino now reads:

```text
HIGH
```

---

### Current Flow

#### LED Circuit

Conventional current flows:

```text
Arduino Output → LED → 330 Ω Resistor → GND
```

The resistor limits the current flowing through the LED, protecting both the LED and the Arduino output pin.

---

#### Push Button Circuit

**Button Released**

```text
Arduino Input
 │
10 kΩ
 │
GND
```

The resistor keeps the input node at approximately **0 V**.

Since the switch is open, there is essentially **no current flow** because there is no complete path from **5 V** to **GND**.

---

**Button Pressed**

```text
5V
 │
Push Button
 │
Arduino Input
 │
10 kΩ
 │
GND
```

A small current now flows from **5 V**, through the closed push button, through the **10 kΩ resistor**, and finally to **ground**.

The resistor limits this current while the input node rises to approximately **5 V**, causing the Arduino to read **HIGH**.

---

### Why the Pull-Down Resistor Is Needed

Digital input pins require a defined voltage.

Without a pull-up or pull-down resistor, the input pin becomes **floating**, meaning its voltage is undefined and electrical noise may cause random HIGH or LOW readings.

The external pull-down resistor ensures the Arduino always measures a stable **LOW** whenever the push button is not pressed.

---

### Why LED Polarity Is Important

An LED is a diode that conducts current primarily in one direction.

* The anode (+) should face the Arduino output pin.
* The cathode (-) should face the resistor and ground.

If the LED is connected in reverse, it becomes reverse-biased and does not illuminate under normal Arduino operating voltages.

---

## Observations

* The push button successfully controlled the Arduino input.
* The input pin measured **LOW** when the button was released.
* The input pin measured **HIGH** when the button was pressed.
* The LED responded according to the software logic.
* The external **10 kΩ pull-down resistor** prevented the input pin from floating.
* The Arduino input pin detected voltage levels rather than supplying power.
* The project demonstrated how software reacts to changes in hardware input.

---

## Software Engineering Insight

Unlike the previous LED projects, this program first reads an **input** before controlling an **output**.

The Arduino continuously measures the voltage on the push button input using:

```cpp
digitalRead(pushButton);
```

When the measured voltage becomes **HIGH**, the software executes the programmed logic.

The Arduino then controls the LED using:

```cpp
digitalWrite(ledPin, HIGH);
digitalWrite(ledPin, LOW);
```

This project demonstrates one of the most fundamental concepts of embedded systems:

```text
Read an Input → Make a Decision → Control an Output
```

The hardware determines the electrical state of the input node, the Arduino measures that state, and the software decides how the output should respond.

---

## Files

* `code.ino` — Arduino source code
* `push-button-external-pull-down.png` — Circuit screenshot
* `push-button-external-pull-down-schema.png` — Schematic view
* `note.md` — Detailed engineering and physics notes
* `README.md` — Project documentation
