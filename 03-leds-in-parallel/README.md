# LEDs in Parallel

## Demo Video

https://youtu.be/WfZMlgeA2-g

---

## Objective

* Learn how LEDs behave when connected in a parallel circuit.
* Understand that each branch in a parallel circuit receives approximately the same voltage.
* Observe that the total current supplied by the source is the sum of the currents in each branch.
* Verify theoretical calculations using a digital multimeter.

---

## Components

* Arduino Uno
* 3 LEDs
* 3 × 330 Ω resistors
* Breadboard
* Jumper wires

> **Note:** The circuit was initially built using three **220 Ω** resistors. They were later replaced with **330 Ω** resistors after Tinkercad indicated an overload warning on the Arduino output pin.

---

## Engineering Procedure

### Circuit Connections

1. Connect the anode (+) of each LED to **Arduino digital pin 5**.
2. Connect the cathode (-) of each LED to its own **330 Ω resistor**.
3. Connect the other end of each resistor to the **Arduino GND** pin.

---

## Physics

### Power Source

The Arduino receives electrical power from the USB connection.

When digital pin 5 is configured as an output and set **HIGH**, it attempts to provide approximately **5 V**. During this experiment, the measured output voltage depended on the current drawn by the circuit.

### Current Flow

Conventional current flows through three independent branches:

```text
                    ┌── LED 1 ── 330 Ω ── GND
Arduino Pin 5 ──────┼── LED 2 ── 330 Ω ── GND
                    └── LED 3 ── 330 Ω ── GND
```

Because this is a **parallel circuit**:

* Each LED has its own current path.
* The voltage across each branch is approximately the same.
* The total current supplied by the Arduino is the sum of the currents flowing through all three branches.

If one LED is disconnected, the remaining LEDs continue operating because their branches remain complete.

### Voltage Distribution

#### Initial Measurements (220 Ω Resistors)

| Component     | Measured Voltage |
| ------------- | ---------------: |
| Arduino Pin 5 |           3.77 V |
| LED 1         |           1.96 V |
| LED 2         |           1.96 V |
| LED 3         |           1.96 V |

The Arduino simulator displayed an overload warning.

#### Final Measurements (330 Ω Resistors)

| Component     | Measured Voltage |
| ------------- | ---------------: |
| Arduino Pin 5 |           4.04 V |
| LED 1         |           1.94 V |
| LED 2         |           1.94 V |
| LED 3         |           1.94 V |

After replacing each **220 Ω resistor** with a **330 Ω resistor**, the overload warning disappeared.

Voltage across each resistor:

```text
VR = 4.04 V − 1.94 V

VR = 2.10 V
```

### Current Calculation

Using **Ohm's Law**:

```text
I = V / R

I = 2.10 / 330

I = 0.00636 A

I ≈ 6.36 mA
```

Current in each branch:

* LED 1 branch ≈ **6.36 mA**
* LED 2 branch ≈ **6.36 mA**
* LED 3 branch ≈ **6.36 mA**

Total current supplied by the Arduino:

```text
IT = I1 + I2 + I3

IT = 6.36 + 6.36 + 6.36

IT ≈ 19.08 mA
```

### Why Each LED Needs Its Own Resistor

Although the LEDs are connected in parallel, each LED should have its own current-limiting resistor.

This ensures:

* Proper current limiting.
* Uniform brightness.
* Improved reliability.
* Protection of both the LEDs and the Arduino output pin.

### Why Polarity Is Important

An LED is a **Light Emitting Diode**, which conducts current primarily in one direction.

* The **anode (+)** must face the Arduino output pin.
* The **cathode (-)** must face the resistor and ground.

If one LED is connected in reverse, only that branch stops conducting while the remaining branches continue to operate normally.

---

## Observations

* Three LEDs blinked simultaneously using the same Arduino program as the previous projects.
* Each LED had a measured forward voltage of approximately **1.94 V** after replacing the resistors.
* The Arduino output voltage increased from approximately **3.77 V** to **4.04 V** after changing the resistors from **220 Ω** to **330 Ω**.
* The overload warning disappeared after increasing the resistor values.
* Each LED required its own resistor to limit the branch current.
* The voltage across each branch remained approximately the same, while the total current was the sum of the branch currents.

---

## Software Engineering Insight

The Arduino program did **not** require any modification from the previous projects.

Only the hardware configuration changed.

```text
HIGH → All LEDs ON

LOW  → All LEDs OFF
```

This demonstrates that the software controls the state of the output pin, while the electrical behaviour of the circuit is determined by the hardware connected to that pin.

---

## Files

* `code.ino` — Arduino source code
* `leds_in_parallel.png` — Circuit screenshot
* `leds_in_parallel_schema.png` — Schematic view
* `note.md` — Detailed engineering and physics notes
* `README.md` — Project documentation
