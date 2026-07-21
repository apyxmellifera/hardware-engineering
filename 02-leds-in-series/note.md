# Engineering and Physics Notes

## 1. Ground and Voltage

a. Ground is the reference node connected to the negative terminal of the power supply.

b. The power supply creates a potential difference (voltage) between the positive and negative terminals. This voltage provides the energy required to move electric charge through a closed circuit.

c. Electrons move from the negative terminal toward the positive terminal, but only when a complete conducting path exists.

d. In this Arduino circuit:

* **Conventional current** flows:

```text
Arduino Pin 5 → LED 1 → LED 2 → Resistor → GND
```

* **Electron flow** is in the opposite direction:

```text
GND → Resistor → LED 2 → LED 1 → Arduino Pin 5
```

---

## 2. Series Circuit

A series circuit has only **one path** for current to flow.

Since there is only one path:

* The **same current** flows through every component.
* If one component is disconnected or fails open, the entire circuit stops conducting and both LEDs turn off.
* One resistor limits the current for the entire circuit.

---

## 3. Voltage Distribution

Unlike current, voltage is shared among the components connected in series.

During this experiment, the measured values were approximately:

* Arduino Pin 5 = **4.43 V**
* LED 1 = **1.93 V**
* LED 2 = **1.93 V**

The remaining voltage appears across the resistor.

---

## 4. Current Calculation

Voltage across the resistor:

```text
VR = 4.43 V − (1.93 V + 1.93 V)

VR = 0.57 V
```

Using Ohm's Law:

```text
I = V / R

I = 0.57 / 220

I = 0.00259 A

I ≈ 2.6 mA
```

Therefore, approximately **2.6 mA** flows through every component in the circuit.

---

## 5. LED Operation

An LED (Light Emitting Diode) contains a **PN junction** semiconductor.

The **longer lead** is the **anode (+)**.

The **shorter lead** is the **cathode (-)**.

When the LED is forward-biased:

* Electrons move from the N-type semiconductor toward the PN junction.
* Holes move from the P-type semiconductor toward the PN junction.
* Electrons recombine with holes.
* The energy released during recombination is emitted as photons (light).

The colour of the emitted light depends on the semiconductor material and its energy band gap.

* **Blue** → Short wavelength, high energy
* **Green** → Medium wavelength
* **Red** → Long wavelength, lower energy

---

## 6. Why Polarity Is Important

An LED is a diode and conducts current primarily in one direction.

For correct operation:

* The anode (+) should face the positive side of the circuit.
* The cathode (-) should face the resistor and ground.

If either LED is connected in reverse, current cannot flow through the series path, preventing both LEDs from lighting because the circuit is interrupted.

---

## 7. Engineering Observation

Although the Arduino program is identical to the single LED project, the electrical behaviour changes because the hardware has changed.

The software only switches digital pin 5 between HIGH and LOW.

The series circuit determines:

* How current flows.
* How voltage is distributed.
* How the LEDs behave.

This demonstrates that software controls the digital output, while the electrical characteristics are determined by the hardware connected to that output.
