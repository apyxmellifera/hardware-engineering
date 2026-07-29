# Engineering and Physics Notes

## 1. Ground and Voltage

a. Ground is the reference node connected to the negative terminal of the power supply.

b. The power supply creates a potential difference (voltage) between the positive and negative terminals. This voltage provides the energy required to move electric charge through a closed circuit.

c. Electrons move from the negative terminal toward the positive terminal, but only when a complete conducting path exists.

d. In this Arduino circuit:

* **Conventional current** flows through three independent branches:

```text
                    ┌── LED 1 ── 330 Ω ── GND
Arduino Pin 5 ──────┼── LED 2 ── 330 Ω ── GND
                    └── LED 3 ── 330 Ω ── GND
```

* **Electron flow** is in the opposite direction:

```text
GND ── 330 Ω ── LED 1 ─┐
GND ── 330 Ω ── LED 2 ─┼── Arduino Pin 5
GND ── 330 Ω ── LED 3 ─┘
```

---

## 2. Parallel Circuit

A parallel circuit provides **multiple paths** for current to flow.

In this experiment:

* Three LEDs are connected in parallel.
* Each LED has its own current-limiting resistor.
* The voltage across each branch is approximately the same.
* The total current supplied by the Arduino is the sum of the currents flowing through all three branches.
* If one LED is removed or fails open, the other LEDs continue operating because their current paths remain complete.

---

## 3. Voltage Distribution

Unlike a series circuit, every branch in a parallel circuit receives approximately the same voltage.

### Initial Measurements (220 Ω Resistors)

* Arduino Pin 5 ≈ **3.77 V**
* LED 1 ≈ **1.96 V**
* LED 2 ≈ **1.96 V**
* LED 3 ≈ **1.96 V**

The Arduino simulator displayed an overload warning.

### Final Measurements (330 Ω Resistors)

* Arduino Pin 5 ≈ **4.04 V**
* LED 1 ≈ **1.94 V**
* LED 2 ≈ **1.94 V**
* LED 3 ≈ **1.94 V**

The overload warning disappeared after increasing each resistor to **330 Ω**.

---

## 4. Current Calculation

Using the final measurements:

Voltage across each resistor:

```text
VR = 4.04 V − 1.94 V

VR = 2.10 V
```

Using Ohm's Law:

```text
I = V / R

I = 2.10 / 330

I = 0.00636 A

I ≈ 6.36 mA
```

Since there are three identical branches:

```text
Total Current

IT = I1 + I2 + I3

IT = 6.36 mA + 6.36 mA + 6.36 mA

IT ≈ 19.08 mA
```

Therefore, the Arduino output pin supplies approximately **19.08 mA** to the entire circuit.

---

## 5. LED Operation

An LED (Light Emitting Diode) contains a **PN junction** semiconductor.

* The **longer lead** is the **anode (+)**.
* The **shorter lead** is the **cathode (-)**.

When the LED is forward-biased:

* Electrons move from the N-type semiconductor toward the PN junction.
* Holes move from the P-type semiconductor toward the PN junction.
* Electrons recombine with holes.
* The energy released during recombination is emitted as photons (light).

The colour of the emitted light depends on the semiconductor material and its energy band gap:

* **Blue** → Short wavelength, higher energy
* **Green** → Medium wavelength
* **Red** → Longer wavelength, lower energy

---

## 6. Why Each LED Requires Its Own Resistor

Although the LEDs are connected in parallel, **each LED should have its own current-limiting resistor**.

This is because no two LEDs are perfectly identical. Small differences in forward voltage can cause one LED to draw more current than another if they share a single resistor.

Using one resistor per LED provides:

* Better current sharing.
* More consistent brightness.
* Improved reliability.
* Protection for both the LEDs and the Arduino output pin.

---

## 7. Why Polarity Is Important

An LED is a diode and conducts current primarily in one direction.

For correct operation:

* The anode (+) should be connected toward the Arduino output pin.
* The cathode (-) should be connected toward the resistor and ground.

If one LED is connected in reverse, only that branch stops conducting. The remaining correctly connected branches continue operating because each branch is electrically independent.

---

## 8. Engineering Observation

Initially, each of the three LED branches used a **220 Ω resistor**.

Measurements:

* Arduino output ≈ **3.77 V**
* Each LED ≈ **1.96 V**

Although all three LEDs blinked correctly, Tinkercad displayed an overload warning on the Arduino output pin.

Each resistor was then increased to **330 Ω**.

New measurements:

* Arduino output ≈ **4.04 V**
* Each LED ≈ **1.94 V**

After increasing the resistor values, the overload warning disappeared while all three LEDs continued to blink normally.

This demonstrates that increasing the resistance reduced the total current drawn from the Arduino output pin while still supplying enough current for each LED to operate.

This experiment also confirms two important characteristics of a parallel circuit:

* The voltage across each branch is approximately the same.
* The total current supplied by the source is the sum of the currents in all branches.

Finally, the Arduino program remained exactly the same as in the previous projects. Only the hardware configuration changed, demonstrating that software controls the output pin, while the electrical behaviour of the circuit is determined by the hardware connected to it.
