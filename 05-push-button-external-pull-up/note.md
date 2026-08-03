# Engineering and Physics Notes

## Components

1. Arduino Uno
2. One LED
3. One 330 Ω resistor (LED current limiting)
4. One push button
5. One 10 kΩ resistor (external pull-up)
6. Breadboard
7. Jumper wires

---

## 1. Ground and Voltage

a. Ground (GND) is the reference node connected to the negative terminal of the power supply.

b. The power supply creates a potential difference (voltage) between the positive and negative terminals. This voltage provides the energy required to move electric charge through a closed circuit.

c. Electrons move from the negative terminal toward the positive terminal only when there is a complete conducting path.

d. This project contains two separate circuits:

* **LED Output Circuit**

```text
Arduino Output Pin → LED → 330 Ω Resistor → GND
```

* **Push Button Input Circuit**

```text
          +5V
           │
        10 kΩ
           │
Arduino Input Pin
           │
     Push Button
           │
          GND
```

e. Conventional current flows from the positive supply toward ground, while electrons flow in the opposite direction.

---

## 2. Push Button Operation

A push button is a **momentary switch**.

* When the button is **not pressed**, its internal contacts remain open.
* When the button is **pressed**, the contacts close and complete the circuit.
* When the button is **released**, the contacts open again, interrupting current flow.

Unlike an LED, a standard push button **has no polarity**, so it can be connected in either orientation as long as the correct terminals are used.

---

## 3. External Pull-Up Resistor

This project uses an **external pull-up resistor**.

The 10 kΩ resistor connects the Arduino input pin to the **5 V supply**.

```text
          +5V
           │
        10 kΩ
           │
           ●──────── Arduino Input
           │
     Push Button
           │
          GND
```

The connection point (●) is shared by:

* The Arduino input pin.
* One end of the 10 kΩ resistor.
* One terminal of the push button.

Because the resistor continuously connects the input pin to 5 V, the input has a known default state.

---

## 4. Button States

### Button Not Pressed

When the push button is released:

* The switch is open.
* The resistor pulls the input pin to +5 V.
* The Arduino reads:

```text
HIGH
```

This is called the **default state**.

---

### Button Pressed

When the button is pressed:

* The switch closes.
* The input pin is connected directly to ground.
* The Arduino reads:

```text
LOW
```

Although the resistor remains connected to +5 V, its large resistance (10 kΩ) limits the current, allowing the input voltage to fall to approximately 0 V.

---

## 5. Why the Pull-Up Resistor Is Needed

Digital input pins have very high impedance.

Without a pull-up or pull-down resistor, the input would be electrically floating.

A floating input has no defined voltage and may randomly read HIGH or LOW due to electrical noise.

The pull-up resistor prevents this by providing a stable default voltage of +5 V whenever the button is not pressed.

---

## 6. LED Operation

An LED (Light Emitting Diode) is a PN junction semiconductor.

* The **longer lead** is the **anode (+)**.
* The **shorter lead** is the **cathode (-)**.

When forward-biased:

* Electrons move toward the PN junction.
* Holes move toward the PN junction.
* Electrons recombine with holes.
* Energy is released as photons, producing visible light.

The 330 Ω resistor limits the current flowing through the LED and protects both the LED and the Arduino output pin.

---

## 7. Software and Hardware Interaction

The Arduino continuously checks the voltage on the push button input pin using:

```cpp
digitalRead(pushButton);
```

When the button is pressed, the input becomes **LOW**, causing the program to execute the desired action.

The Arduino then controls the LED by changing the voltage on the output pin using:

```cpp
digitalWrite(ledPin, HIGH);
digitalWrite(ledPin, LOW);
```

This demonstrates the interaction between:

* **Input devices** (push button)
* **Software logic** (decision making)
* **Output devices** (LED)

---

## 8. Engineering Observation

This project introduces **digital inputs**.

Previous projects focused on digital outputs by controlling LEDs.

In this project, the Arduino first receives information from an external device (the push button), makes a decision based on that input, and then controls the LED accordingly.

The external pull-up resistor ensures that the input pin always has a defined voltage, preventing unpredictable behaviour caused by floating inputs.

This project demonstrates that embedded systems combine hardware and software:

* The **hardware** determines the electrical state of the input pin.
* The **software** reads that state and decides how the output should respond.
