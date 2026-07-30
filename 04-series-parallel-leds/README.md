# LEDs in Series-Parallel

## Demo Video

https://youtu.be/VfD9pBlYGwQ

---

## Objective

* Learn how LEDs behave in a series-parallel circuit.
* Understand how the principles of series and parallel circuits work together.
* Observe that the same current flows through LEDs connected in series within a branch.
* Observe that the total current supplied by the source is the sum of the currents in all parallel branches.
* Verify theoretical calculations using a digital multimeter.

---

## Components

* Arduino Uno
* 6 LEDs
* 3 × 330 Ω resistors
* Breadboard
* Jumper wires

---

## Engineering Procedure

### Circuit Connections

1. Divide the six LEDs into **three pairs**.
2. Connect each pair of LEDs **in series**.
3. Connect a **330 Ω resistor** to the cathode of the second LED in each pair.
4. Connect the other end of each resistor to the **Arduino GND** pin.
5. Connect the anode of the first LED in each pair to **Arduino digital pin 5**, placing the three series branches in parallel.

---

## Physics

### Power Source

The Arduino receives electrical power from the USB connection.

When digital pin 5 is configured as an output and set **HIGH**, it attempts to provide approximately **5 V**. During this experiment, the measured output voltage while driving the circuit was approximately **4.03 V**.

### Current Flow

Conventional current flows through three independent branches:

```text
                    Branch 1
Arduino Pin 5 → LED 1 → LED 2 → 330 Ω → GND

                    Branch 2
Arduino Pin 5 → LED 3 → LED 4 → 330 Ω → GND

                    Branch 3
Arduino Pin 5 → LED 5 → LED 6 → 330 Ω → GND
```

Within each branch:

* The **same current** flows through both LEDs and the resistor because they are connected in series.

Across the branches:

* The **total current** supplied by the Arduino is divided among the three parallel branches.

If one LED in a branch is disconnected or fails open, that branch stops conducting, while the remaining branches continue to operate.

---

### Voltage Distribution

Measured voltages:

| Component     | Measured Voltage |
| ------------- | ---------------: |
| Arduino Pin 5 |           4.03 V |
| LED 1         |           1.89 V |
| LED 2         |           1.89 V |

Voltage across both LEDs:

```text
VLED = 1.89 V + 1.89 V

VLED = 3.78 V
```

Voltage across the resistor:

```text
VR = 4.03 V − 3.78 V

VR = 0.25 V
```

---

### Current Calculation

Using **Ohm's Law**:

```text
I = V / R

I = 0.25 / 330

I = 0.000758 A

I ≈ 0.76 mA
```

Current in each branch:

* Branch 1 ≈ **0.76 mA**
* Branch 2 ≈ **0.76 mA**
* Branch 3 ≈ **0.76 mA**

Total current supplied by the Arduino:

```text
IT = I1 + I2 + I3

IT = 0.76 + 0.76 + 0.76

IT ≈ 2.27 mA
```

---

### Why One Resistor Is Used Per Branch

Each branch contains two LEDs connected in series.

Since the same current flows through every component in a series path, only **one resistor** is required to limit the current in that branch.

However, because there are three parallel branches, **each branch requires its own resistor**.

---

### Why Polarity Is Important

An LED is a **Light Emitting Diode**, which conducts current primarily in one direction.

* The **anode (+)** should face the Arduino output pin.
* The **cathode (-)** should face the resistor and ground.

If one LED is connected in reverse, that entire series branch stops conducting, while the remaining branches continue operating.

---

## Observations

* Six LEDs were successfully arranged as **three series branches connected in parallel**.
* Each LED had a measured forward voltage of approximately **1.89 V**.
* The Arduino output pin measured approximately **4.03 V** while supplying the circuit.
* One **330 Ω resistor** successfully limited the current in each series branch.
* The same current flowed through both LEDs within each branch.
* The total current supplied by the Arduino was the sum of the currents in the three parallel branches.

---

## Software Engineering Insight

The Arduino program remained exactly the same as in the previous LED projects.

Only the hardware configuration changed.

```text
HIGH → All six LEDs ON

LOW  → All six LEDs OFF
```

This demonstrates that software controls the digital output pin, while the electrical behaviour of the circuit is determined by the hardware connected to that output.

---

## Files

* `code.ino` — Arduino source code
* `leds_in_series_parallel.png` — Circuit screenshot
* `leds_in_series_parallel_schema.png` — Schematic view
* `note.md` — Detailed engineering and physics notes
* `README.md` — Project documentation
