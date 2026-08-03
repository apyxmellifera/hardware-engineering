# Push Button (External Pull-Up)

## Demo Video
https://youtu.be/2klln0pTbxg

---

## Objective

* Learn how to read a digital input using a push button.
* Understand how an external pull-up resistor establishes a default input state.
* Observe how pressing a push button changes the voltage at the Arduino input pin.
* Control an LED using software based on the state of the push button.
* Understand the relationship between hardware inputs and software decision-making.

---

## Components

* Arduino Uno
* 1 LED
* 1 × 330 Ω resistor
* 1 Push button
* 1 × 10 kΩ resistor (external pull-up)
* Breadboard
* Jumper wires

---

## Engineering Procedure

### Circuit Connections

### LED Circuit

1. Connect the anode (+) of the LED to the Arduino digital output pin.
2. Connect the cathode (-) of the LED to one end of the 330 Ω resistor.
3. Connect the other end of the resistor to Arduino GND.

### Push Button Circuit

1. Connect one terminal of the push button to Arduino GND.
2. Connect the opposite terminal of the push button to the Arduino input pin.
3. Connect a 10 kΩ resistor between the Arduino input pin and the Arduino 5 V pin.

This creates an **external pull-up resistor** configuration.

---

## Physics

### Power Source

The Arduino receives electrical power from the USB connection.

When configured as an output, the Arduino pin supplies approximately **5 V** to the LED circuit.

The push button circuit also uses the Arduino's **5 V** supply through the external pull-up resistor.

---

### Push Button Operation

The push button is a **momentary switch**.

When the button is **not pressed**, the switch remains open.

The external 10 kΩ resistor connects the Arduino input pin to **5 V**, causing the input to read:

```text
HIGH
```

When the button is **pressed**, the switch closes and connects the input pin directly to **GND**.

The Arduino now reads:

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

When the button is **released**:

```text
5V
 │
10 kΩ
 │
Arduino Input
```

The resistor pulls the input to **HIGH**.

When the button is **pressed**:

```text
5V
 │
10 kΩ
 │
Arduino Input
 │
Push Button
 │
GND
```

The input is connected directly to ground and reads **LOW**.

---

### Why the Pull-Up Resistor Is Needed

Digital input pins require a defined voltage.

Without a pull-up or pull-down resistor, the input pin becomes **floating** and may randomly read HIGH or LOW due to electrical noise.

The external pull-up resistor ensures the Arduino always reads a stable **HIGH** whenever the button is not pressed.

---

### Why LED Polarity Is Important

An LED is a diode that allows current to flow primarily in one direction.

* The anode (+) should face the Arduino output.
* The cathode (-) should face the resistor and ground.

If the LED is connected in reverse, it becomes reverse-biased and does not illuminate under normal Arduino operating voltages.

---

## Observations

* The push button successfully controlled the Arduino input.
* The input pin read **HIGH** when the button was released.
* The input pin read **LOW** when the button was pressed.
* The LED responded according to the software logic.
* The external 10 kΩ resistor prevented the input pin from floating.
* The project demonstrated how software reacts to changes in hardware input.

---

## Software Engineering Insight

Unlike the previous LED projects, this program first reads an **input** before controlling an **output**.

The Arduino continuously checks the push button using:

```cpp
digitalRead(pushButton);
```

When the button is pressed:

```text
LOW → Execute program logic
```

The program then controls the LED using:

```cpp
digitalWrite(ledPin, HIGH);
digitalWrite(ledPin, LOW);
```

This project demonstrates one of the fundamental concepts of embedded systems:

**Read an input → Make a decision → Control an output.**

---

## Files

* `code.ino` — Arduino source code
* `push_button_external_pull_up.png` — Circuit screenshot
* `push_button_external_pull_up_schema.png` — Schematic view
* `note.md` — Detailed engineering and physics notes
* `README.md` — Project documentation
