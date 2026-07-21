# LEDs in Series

## Demo Video

https://youtu.be/YoH39R6h-Ko

---

## Objective

* Learn how LEDs behave when connected in a series circuit.
* Understand that the same current flows through every component in a series circuit.
* Observe how the supply voltage is shared among the LEDs and the resistor.
* Verify theoretical calculations using a digital multimeter.

---

## Components

* Arduino Uno
* 2 LEDs
* 220 Ω resistor
* Breadboard
* Jumper wires

---

## Engineering Procedure

### Circuit Connections

1. Connect the anode (+) of **LED 1** to **Arduino digital pin 5**.
2. Connect the cathode (-) of **LED 1** to the anode (+) of **LED 2**.
3. Connect the cathode (-) of **LED 2** to one end of the **220 Ω resistor**.
4. Connect the other end of the resistor to the **Arduino GND** pin.

---

## Physics

### Power Source

The Arduino receives electrical power from the USB connection.

When digital pin 5 is configured as an output and set **HIGH**, it outputs approximately **5 V**. During this experiment, the measured voltage at the output pin while driving the circuit was approximately **4.43 V**.

### Current Flow

Conventional current flows through the circuit in one continuous path:

```text
Arduino Pin 5
     │
     ▼
   LED 1
     │
     ▼
   LED 2
     │
     ▼
220 Ω Resistor
     │
     ▼
    GND
```

Because this is a **series circuit**, the **same current** flows through both LEDs and the resistor.

If any component is disconnected or fails open, the circuit becomes incomplete and both LEDs turn off.

### Voltage Distribution

Measured voltages:

| Component     | Measured Voltage |
| ------------- | ---------------: |
| Arduino Pin 5 |           4.43 V |
| LED 1         |           1.93 V |
| LED 2         |           1.93 V |

The voltage across the resistor is therefore:

```text
VR = 4.43 V − (1.93 V + 1.93 V)

VR = 0.57 V
```

### Current Calculation

Using **Ohm's Law**:

```text
I = V / R

I = 0.57 / 220

I = 0.00259 A

I ≈ 2.6 mA
```

Therefore, approximately **2.6 mA** flows through every component in the circuit.

### Why One Resistor Is Enough

Since all components are connected in a single current path, only **one resistor** is required.

The resistor limits the current flowing through the entire series circuit.

### Why Polarity Is Important

An LED is a **Light Emitting Diode**, which allows current to flow primarily in one direction.

* The **anode (+)** must face the Arduino output.
* The **cathode (-)** must face the resistor and ground.

If either LED is connected in reverse, current cannot flow through the series circuit, so neither LED will illuminate.

---

## Observations

* Both LEDs blinked simultaneously using the same Arduino program as the single LED project.
* Each LED had a measured forward voltage of approximately **1.93 V**.
* The Arduino output pin measured approximately **4.43 V** while supplying current.
* One **220 Ω resistor** successfully limited the current for both LEDs.
* The same current flowed through every component in the circuit because they were connected in series.

---

## Software Engineering Insight

The Arduino program did **not** require any modification from the previous project.

Only the hardware configuration changed.

```text
HIGH → Both LEDs ON

LOW  → Both LEDs OFF
```

This demonstrates that the software controls the state of the output pin, while the electrical behaviour is determined by the hardware connected to that pin.

---

## Files

* `code.ino` — Arduino source code
* `leds_in_series.png` — Circuit screenshot
* `leds_in_series_schema.png` — Schematic view
* `note.md` — Detailed engineering and physics notes
* `README.md` — Project documentation
