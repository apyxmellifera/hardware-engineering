# Engineering and Physics Notes

## 1. Ground and Voltage

a. Ground (GND) is the node connected to the negative terminal of the power supply.

b. Ground is called **0 V** because it is chosen as the **reference point** for measuring electrical potential. Voltage is not an absolute quantity; it is always a **difference in electric potential between two points**. By convention, ground is assigned **0 V**, providing a common reference from which all other voltages in the circuit are measured.

c. The power supply as a whole creates the **potential difference (voltage)** between its positive and negative terminals. This voltage creates the electric field that moves electric charge through a closed circuit.

d. Electrons move from the negative terminal toward the positive terminal only when there is a complete conducting path. Conventional current is defined in the opposite direction.

e. In this Arduino LED circuit:

**Conventional current**

```text
Arduino Output Pin → LED → Resistor → GND
```

**Electron flow**

```text
GND → Resistor → LED → Arduino Output Pin
```

---

## 2. Arduino Digital Pins

An Arduino digital pin can operate in two different modes.

### Output Mode

When configured using:

```cpp
pinMode(pin, OUTPUT);
```

the digital pin acts as an electrical output.

* When set **HIGH**, the pin supplies approximately **5 V**, allowing current to flow through an external circuit.
* When set **LOW**, the pin is connected internally toward ground, removing the voltage supplied to the external circuit.

This enables the Arduino to control output devices such as LEDs, buzzers, relays, and other electronic components.

### Input Mode

When configured using:

```cpp
pinMode(pin, INPUT);
```

the digital pin does **not** supply power.

Instead, it measures the voltage present at the node to which it is connected.

* Approximately **0 V** is interpreted as **LOW**.
* Approximately **5 V** is interpreted as **HIGH**.

The input pin has a very high input impedance, meaning it draws negligible current and functions primarily as a voltage sensor.

---

## 3. Resistors

A resistor limits the flow of electric current because of the electrical properties of the material from which it is made.

Many resistors use carbon-based materials or metal films that have a much higher electrical resistance than copper.

As conduction electrons move through the resistor, they frequently collide with atoms in the resistive material. These collisions oppose the movement of the electrons and convert part of the electrical energy into thermal (heat) energy.

This opposition to electron flow is called **electrical resistance**.

According to **Ohm's Law**:

```text
I = V / R
```

Increasing the resistance reduces the current flowing through the circuit for a given voltage.

In LED circuits, the resistor limits the current to protect both the LED and the Arduino output pin from excessive current.

---

## 4. Conductors (Copper Wires)

Electrical wires are commonly made from **copper** because it is an excellent electrical conductor.

Copper atoms contain loosely bound outer (valence) electrons that become **delocalized**, allowing them to move freely throughout the metal.

When a voltage is applied across the wire, the electric field causes these free electrons to drift through the conductor, allowing electric current to flow with very little resistance.

Because copper has a low electrical resistance, very little electrical energy is converted into heat compared with a resistor.

This is why copper is used for connecting components, while resistive materials are used for limiting current.

---

## 5. LED Operation

An LED (Light Emitting Diode) contains a semiconductor **PN junction**.

* The **longer lead** is the **anode (+)**.
* The **shorter lead** is the **cathode (-)**.

When the LED is forward biased:

* Electrons from the N-type semiconductor move toward the PN junction.
* Holes from the P-type semiconductor move toward the PN junction.
* Electrons recombine with holes.
* As an electron transitions to a lower energy state, the energy difference is released as a **photon (light)**.

The wavelength and colour of the emitted light depend on the semiconductor material and its energy band gap.

* Blue light → shorter wavelength, higher energy.
* Green light → medium wavelength.
* Red light → longer wavelength, lower energy.

---

## 6. Why Polarity Is Important

An LED is a diode, meaning it allows current to flow primarily in one direction.

* The **anode (+)** should be connected toward the positive side of the circuit (the Arduino output pin when it is HIGH).
* The **cathode (-)** should be connected toward the current-limiting resistor and ground.

If the LED is connected in reverse, it becomes **reverse-biased**.

Under normal Arduino operating voltages (approximately 5 V), almost no current flows through the LED, so it does not emit light.

This is because the PN junction permits current to flow readily in the forward direction while blocking current in the reverse direction under normal operating conditions.
