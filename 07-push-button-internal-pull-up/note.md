# Engineering and Physics Notes

## Components

1. Arduino Uno
2. One LED
3. One 330 Ω resistor (LED current limiting)
4. One push button
5. Breadboard
6. Jumper wires

---

## 1. Ground and Voltage

a. Ground (GND) is the node connected to the negative terminal of the power supply.

b. Ground is called **0 V** because it is chosen as the reference point for measuring electrical potential. Voltage is not an absolute quantity; it is always a difference in electric potential between two points. By convention, ground is assigned **0 V**, providing a common reference from which all other voltages in the circuit are measured.

c. The power supply creates the potential difference (voltage) between its positive and negative terminals. This voltage creates the electric field that moves electric charge through a closed circuit.

d. Electrons move from the negative terminal toward the positive terminal only when there is a complete conducting path. Conventional current flows in the opposite direction.

e. This project contains two separate circuits.

**LED Output Circuit**

```text
Arduino Output Pin → LED → 330 Ω Resistor → GND
```

**Push Button Input Circuit**

```text
             +5V
              │
     Internal Pull-up
              │
Arduino Input Pin
              │
        Push Button
              │
             GND
```

The connection between the input pin and +5 V is **inside the Arduino microcontroller**. No external resistor or wire to +5 V is required.

f. Conventional current flows from the positive supply toward ground, while electrons flow from ground toward the positive supply.

---

## 2. Arduino Digital Pins

Arduino digital pins can operate as either **outputs** or **inputs**.

### Digital Output Pin

When configured using:

```cpp
pinMode(led, OUTPUT);
```

the digital pin actively supplies an output voltage.

* When set **HIGH**, the pin outputs approximately **5 V**, allowing current to flow through the LED circuit.
* When set **LOW**, the pin outputs approximately **0 V**, stopping current flow.

The output pin therefore acts as the electrical source for devices such as LEDs (within the Arduino's current limits).

---

### Digital Input Pin

When configured using:

```cpp
pinMode(pushButton, INPUT_PULLUP);
```

the digital pin **does not become a power source**.

Instead, it measures the voltage present at the input node.

* Approximately **0 V** is interpreted as **LOW**.
* Approximately **5 V** is interpreted as **HIGH**.

The input pin has a very high input impedance, meaning it draws negligible current and behaves like a voltage sensor.

---

## 3. Push Button Operation

A push button is a **momentary switch**.

* When released, its contacts remain open.
* When pressed, its contacts close, completing the circuit.
* When released again, the circuit opens.

Unlike an LED, a push button has **no polarity**, so it may be connected in either orientation provided the correct terminals are used.

---

## 4. Internal Pull-Up Resistor

This project uses the Arduino's **internal pull-up resistor**.

When the following instruction is executed:

```cpp
pinMode(pushButton, INPUT_PULLUP);
```

the Arduino automatically connects an internal resistor between the input pin and the **+5 V supply**.

Conceptually, the circuit becomes:

```text
             +5V
              │
     Internal Pull-up
              │
Arduino Input Pin
              │
        Push Button
              │
             GND
```

Unlike the external pull-up project, **no external 10 kΩ resistor is required** because the resistor already exists inside the microcontroller.

The push button therefore connects **only** between the Arduino input pin and **ground**.

---

## 5. Button States

### Button Not Pressed

When the push button is released:

* The switch is open.
* The internal pull-up resistor connects the input node to approximately **5 V**.
* The Arduino input pin measures approximately **5 V**.
* The Arduino reads:

```text
HIGH
```

This is the default state.

Since the switch is open, there is essentially no current flowing because there is no complete path to ground.

---

### Button Pressed

When the push button is pressed:

* The switch closes.
* The input node becomes directly connected to ground.
* The Arduino input pin measures approximately **0 V**.
* The Arduino reads:

```text
LOW
```

A small current now flows from **+5 V**, through the internal pull-up resistor, through the closed push button, and finally to **ground**.

The internal resistor limits this current while allowing the input node to remain at approximately **0 V**.

---

## 6. Why the Internal Pull-Up Is Needed

Digital input pins have very high input impedance.

Without a pull-up or pull-down resistor, the input would float and could randomly read HIGH or LOW due to electrical noise.

The internal pull-up resistor prevents this by providing a stable default voltage of approximately **5 V** whenever the push button is not pressed.

---

## 7. LED Operation

An LED (Light Emitting Diode) is a PN junction semiconductor.

* The **longer lead** is the **anode (+)**.
* The **shorter lead** is the **cathode (-)**.

When forward biased:

* Electrons move toward the PN junction.
* Holes move toward the PN junction.
* Electrons recombine with holes.
* Energy is released as photons, producing visible light.

The **330 Ω resistor** limits the current flowing through the LED and protects both the LED and the Arduino output pin.

---

## 8. Software and Hardware Interaction

The Arduino continuously measures the voltage on the push button input using:

```cpp
digitalRead(pushButton);
```

It does **not** measure current.

It simply determines whether the measured voltage corresponds to a logical HIGH or LOW.

When the button is pressed, the measured voltage becomes **LOW**, causing the software to execute the programmed logic.

The Arduino then controls the LED by changing the output voltage using:

```cpp
digitalWrite(led, HIGH);
digitalWrite(led, LOW);
```

This demonstrates the interaction between:

* Input devices (push button)
* Software logic (decision making)
* Output devices (LED)

---

## 9. Engineering Observation

This project introduces the Arduino's **internal pull-up resistor**.

Unlike the external pull-up project, no external resistor is required because the pull-up resistor is built into the microcontroller.

This simplifies the hardware while maintaining the same electrical behaviour:

* Default state → **HIGH**
* Button pressed → **LOW**

This project reinforces that:

* The **hardware** determines the electrical state (voltage) of the input node.
* The **Arduino input pin** measures that voltage.
* The **software** interprets the measured voltage as HIGH or LOW and decides how the output should respond.
* The **Arduino output pin** supplies the output voltage required to drive the LED.

Comparing the three push-button configurations:

| Configuration | Default State | Pressed State | Resistor |
|--------------|--------------|---------------|-----------|
| External Pull-Up | HIGH | LOW | External 10 kΩ |
| External Pull-Down | LOW | HIGH | External 10 kΩ |
| Internal Pull-Up | HIGH | LOW | Internal (inside the Arduino) |

Although the hardware implementation differs, all three configurations achieve the same objective: ensuring the Arduino input pin always has a well-defined logic level and never floats.

### Why Use `INPUT_PULLUP`?

Using `INPUT_PULLUP` provides several practical advantages over using an external pull-up resistor:

* Fewer components are needed because the pull-up resistor is built into the Arduino microcontroller.
* Simpler wiring since there is no need to connect an external resistor to the 5 V supply.
* Saves space on the breadboard by reducing the number of components and jumper wires.
* Reduces wiring mistakes, making the circuit easier to assemble and troubleshoot.
* Suitable for many push-button applications where the exact value of the pull-up resistor is not critical.

The primary trade-off is that the internal pull-up resistor has a fixed resistance determined by the microcontroller (typically between **20 kΩ and 50 kΩ** on many Arduino boards). If a circuit requires a specific pull-up resistance for electrical or timing reasons, an external resistor may be preferred.