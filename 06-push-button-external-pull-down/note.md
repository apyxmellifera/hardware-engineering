# Engineering and Physics Notes

## Components

1. Arduino Uno
2. One LED
3. One 330 Ω resistor (LED current limiting)
4. One push button
5. One 10 kΩ resistor (external pull-down)
6. Breadboard
7. Jumper wires

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
     Push Button
           │
Arduino Input Pin
           │
        10 kΩ
           │
          GND
```

f. Conventional current flows from the positive supply toward ground, while electrons flow from ground toward the positive supply.

---

## 2. Arduino Digital Input Pin

When an Arduino digital pin is configured as an **input** using:

```cpp
pinMode(pushButton, INPUT);
```

it does **not** supply electrical power. Instead, it measures the voltage present at the node to which it is connected.

* Approximately **0 V** is interpreted as **LOW**.
* Approximately **5 V** is interpreted as **HIGH**.

The input pin has a very high input impedance, meaning it draws negligible current and behaves as a voltage sensor rather than a power source.

If the input pin is left floating, electrical noise can cause unpredictable HIGH and LOW readings.

Pull-up and pull-down resistors prevent this by providing a stable default voltage.

---

## 3. Push Button Operation

A push button is a **momentary switch**.

* When the button is **not pressed**, its internal contacts remain open.
* When the button is **pressed**, the contacts close and complete the circuit.
* When the button is **released**, the contacts open again.

Unlike an LED, a push button has **no polarity**, so it may be connected in either orientation provided the correct terminals are used.

---

## 4. External Pull-Down Resistor

This project uses an **external pull-down resistor**.

The **10 kΩ resistor** connects the Arduino input node to **ground (0 V)**.

```text
          +5V
           │
     Push Button
           │
           ●──────── Arduino Input
           │
        10 kΩ
           │
          GND
```

The connection point (●) is shared by:

* The Arduino input pin.
* One end of the 10 kΩ resistor.
* One terminal of the push button.

Because the resistor continuously connects the input node to ground, the input has a stable default voltage of approximately **0 V** whenever the push button is not pressed.

---

## 5. Button States

### Button Not Pressed

When the push button is released:

* The switch is open.
* The resistor pulls the input node to ground.
* The Arduino input pin measures approximately **0 V**.
* The Arduino reads:

```text
LOW
```

This is the **default state**.

Since the switch is open, essentially no current flows because there is no complete path between +5 V and ground.

---

### Button Pressed

When the push button is pressed:

* The switch closes.
* The input node becomes electrically connected to **+5 V**.
* The Arduino input pin measures approximately **5 V**.
* The Arduino reads:

```text
HIGH
```

A small current now flows from the positive supply through the closed switch and the **10 kΩ resistor** to ground.

The resistor limits this current, protecting the circuit while allowing the input node to remain at approximately **5 V**.

---

## 6. Why the Pull-Down Resistor Is Needed

Digital input pins have very high input impedance.

Without a pull-down or pull-up resistor, the input would float and could randomly read HIGH or LOW due to electrical noise.

The pull-down resistor prevents this by providing a stable default voltage of **0 V** whenever the push button is not pressed.

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

The Arduino continuously checks the voltage on the push button input pin using:

```cpp
digitalRead(pushButton);
```

It does **not** measure current. It simply determines whether the voltage at the input node corresponds to a logical HIGH or LOW.

When the button is pressed, the input becomes **HIGH**, causing the program to execute the desired action.

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

## 9. Engineering Observation

This project demonstrates the use of an **external pull-down resistor**.

The resistor keeps the Arduino input pin at a stable default voltage of **0 V (LOW)** whenever the push button is not pressed.

Pressing the push button connects the input node to **+5 V**, causing the Arduino to detect a **HIGH** logic level.

This project reinforces that:

* The **hardware** determines the electrical state (voltage) of the input node.
* The **Arduino input pin** measures that voltage.
* The **software** interprets the measured voltage as HIGH or LOW and decides how the output should respond.
* The **Arduino output pin** then supplies the appropriate output voltage to control the LED.

Comparing this project with the external pull-up circuit shows that both achieve the same goal of preventing floating inputs. The only difference is the default logic state:

* **External pull-up:** Default **HIGH**, pressed **LOW**.
* **External pull-down:** Default **LOW**, pressed **HIGH**.
