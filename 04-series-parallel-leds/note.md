# Engineering and Physics Notes

## 1. Ground and Voltage

a. Ground is the reference node connected to the negative terminal of the power supply.

b. The power supply creates a potential difference (voltage) between the positive and negative terminals. This voltage provides the energy required to move electric charge through a closed circuit.

c. Electrons move from the negative terminal toward the positive terminal, but only when a complete conducting path exists.

d. In this Arduino circuit:

* **Conventional current** flows through three parallel branches.

* Within each branch, current flows through two LEDs connected in series before passing through a current-limiting resistor to ground.

```text
                 Branch 1
Arduino Pin 5 → LED 1 → LED 2 → 330 Ω → GND

                 Branch 2
Arduino Pin 5 → LED 3 → LED 4 → 330 Ω → GND

                 Branch 3
Arduino Pin 5 → LED 5 → LED 6 → 330 Ω → GND
```

* **Electron flow** occurs in the opposite direction:

```text
GND → 330 Ω → LED → LED → Arduino Pin 5
```

for each branch.

---

## 2. Series-Parallel Circuit

A series-parallel circuit combines the characteristics of both series and parallel circuits.

In this experiment:

* Three branches are connected in parallel.
* Each branch contains two LEDs connected in series.
* Each branch has one 330 Ω current-limiting resistor.
* The same current flows through the two LEDs within each branch.
* The total current supplied by the Arduino is the sum of the currents in all three branches.
* If one LED fails in a branch, that branch stops conducting, but the remaining branches continue to operate.

---

## 3. Voltage Distribution

The measured values during the experiment were approximately:

* Arduino Pin 5 = **4.03 V**
* LED 1 = **1.89 V**
* LED 2 = **1.89 V**

Since the LEDs are connected in series within each branch:

```text
Voltage across LEDs

VLED = 1.89 V + 1.89 V

VLED = 3.78 V
```

Therefore, the voltage across the resistor is:

```text
VR = 4.03 V − 3.78 V

VR = 0.25 V
```

Each parallel branch receives approximately the same supply voltage from the Arduino output pin.

---

## 4. Current Calculation

Using Ohm's Law:

```text
I = V / R

I = 0.25 / 330

I = 0.000758 A

I ≈ 0.76 mA
```

Therefore, approximately **0.76 mA** flows through each branch.

Since the two LEDs are connected in series, they both carry the same current.

Total current supplied by the Arduino:

```text
IT = I1 + I2 + I3

IT = 0.76 + 0.76 + 0.76

IT ≈ 2.27 mA
```

Thus, the Arduino supplies approximately **2.27 mA** to the entire circuit.

---

## 5. LED Operation

An LED (Light Emitting Diode) contains a **PN junction** semiconductor.

The **longer lead** is the **anode (+)**.

The **shorter lead** is the **cathode (-)**.

When forward-biased:

* Electrons move from the N-type region toward the PN junction.
* Holes move from the P-type region toward the PN junction.
* Electrons recombine with holes.
* Energy is released as photons, producing visible light.

The wavelength of the emitted light depends on the semiconductor material.

* **Blue** → Short wavelength, higher energy.
* **Green** → Medium wavelength.
* **Red** → Long wavelength, lower energy.

---

## 6. Why One Resistor Is Used Per Branch

Each pair of LEDs is connected in series, so only one resistor is required to limit the current flowing through that branch.

However, because there are three parallel branches, each branch requires its own resistor.

Using one resistor per branch:

* Limits the branch current.
* Helps maintain balanced operation.
* Protects the LEDs and the Arduino output pin.

---

## 7. Why Polarity Is Important

An LED is a diode and conducts current primarily in one direction.

For correct operation:

* The anode (+) should face the Arduino output.
* The cathode (-) should face the resistor and ground.

If one LED is reversed, the current path in that branch is interrupted and both LEDs in that series branch stop conducting. The other two branches continue to operate because they are connected in parallel.

---

## 8. Engineering Observation

This experiment combines the principles of both series and parallel circuits.

Within each branch:

* The same current flows through both LEDs.
* The supply voltage is shared between the LEDs and the resistor.

Across the three branches:

* Each branch receives approximately the same supply voltage.
* The total current supplied by the Arduino is the sum of the currents in all branches.

The Arduino program remained identical to the previous LED projects.

Only the circuit configuration changed, demonstrating that software controls the output state of the digital pin, while the electrical characteristics are determined by the hardware connected to it.

This project reinforces the relationship between software, circuit design, and electrical behaviour by combining the concepts learned from both series and parallel LED circuits.
