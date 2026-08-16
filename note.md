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

b. Ground is called **0 V** because it is chosen as the reference point for measuring electrical potential. Voltage is not an absolute quantity; it is always a difference in electric potential between two points. By convention, ground is assigned **0 V**, providing a common reference from which other voltages in the circuit are measured.

c. The power supply creates the potential difference (voltage) between its positive and negative terminals. This voltage creates the electric field that moves electric charge through a closed circuit.

d. Electrons move from the negative side toward the positive side when a complete conducting path exists. Conventional current flows in the opposite direction.

e. In the LED circuit:

```text
Arduino Output Pin → LED → 330 Ω Resistor → GND
```

Conventional current flows:

```text
Arduino Output Pin → LED → Resistor → GND
```

Electrons actually move in the opposite direction:

```text
GND → Resistor → LED → Arduino Output Pin
```

---

## 2. Arduino Digital Input

When the Arduino digital pin is configured as an input:

```cpp
pinMode(pushButton, INPUT_PULLUP);
```

the pin is used to detect the voltage at the input node.

It does not behave like the digital output pin that drives the LED.

The input pin interprets the voltage as a digital logic state:

* Approximately **0 V** → `LOW`
* Approximately **5 V** → `HIGH`

The input pin has very high impedance, so it draws very little current from the external circuit.

---

## 3. Internal Pull-Up

This project uses the Arduino's **internal pull-up resistor**.

```cpp
pinMode(pushButton, INPUT_PULLUP);
```

When `INPUT_PULLUP` is enabled, the Arduino internally connects the input pin to its positive supply through an internal pull-up resistor.

Therefore, no external 10 kΩ pull-up resistor is required.

The circuit is:

```text
                 Arduino

        Internal Pull-Up
              │
             +5V
              │
              R
              │
              ●──── Input Pin 8
              │
         Push Button
              │
             GND
```

### Button Released

When the button is not pressed, the switch is open.

The internal pull-up keeps the input node at approximately +5 V:

```text
Input ≈ 5 V
       ↓
     HIGH
```

### Button Pressed

When the button is pressed, the switch closes and connects the input node to ground.

```text
Input ≈ 0 V
       ↓
      LOW
```

Therefore, `INPUT_PULLUP` produces **active-low** button logic:

```text
Released → HIGH
Pressed  → LOW
```

---

## 4. Push Button Operation

A push button is a **momentary switch**.

* When released, its contacts are open.
* When pressed, its contacts close.
* When released again, its contacts open.

Unlike an LED, a standard push button has no polarity.

The important distinction in this project is that the Arduino program is interested in the **transition** from released to pressed rather than simply observing that the button is currently pressed.

---

## 5. Detecting a Press Event

The program keeps track of two button states:

```cpp
int lastButtonState = HIGH;
int currentButtonState = digitalRead(pushButton);
```

`lastButtonState` represents the previous observation.

`currentButtonState` represents the current observation.

A new button press is detected when:

```text
Previous state → HIGH
Current state  → LOW
```

In code:

```cpp
if(lastButtonState == HIGH && currentButtonState == LOW)
```

This means:

> The button was previously released and has now become pressed.

This is a **press event**.

---

## 6. One Physical Press Can Become Many Logical Presses

A very important observation was made while experimenting with the Serial Monitor.

The Arduino continuously executes:

```cpp
loop()
```

very rapidly.

If the program only checks:

```cpp
if(currentButtonState == LOW)
```

then holding the button down produces:

```text
LOW
LOW
LOW
LOW
LOW
LOW
LOW
...
```

The Arduino can therefore interpret one physical press as many logical presses.

> **The Arduino can interpret one physical press as many logical presses if the program reacts to the button's current state instead of detecting the transition between states.**

This was confirmed experimentally using `Serial.println()`.

When `lastButtonState` was not updated, a single physical press caused the serial output to change repeatedly because the condition remained true across many executions of `loop()`.

Updating the previous state prevents this:

```cpp
lastButtonState = currentButtonState;
```

After the first press:

```text
lastButtonState = LOW
currentButtonState = LOW
```

The press condition is no longer true while the button remains held.

The Arduino therefore treats the physical action as **one press event** rather than many.

---

## 7. LED State

The LED has two possible states:

```cpp
bool ledState = false;
```

The boolean represents the logical state of the LED:

```text
false → LED OFF
true  → LED ON
```

The button does not directly represent the LED state.

Instead, each valid press **changes** the LED state.

```text
Press event
     ↓
Check LED state
     ↓
OFF → ON
ON  → OFF
```

This is called **toggling**.

---

## 8. Single-Press Toggle Algorithm

The algorithm is:

```text
Read current button state
        ↓
Was the previous state HIGH
and the current state LOW?
        ↓
       YES
        ↓
   Press detected
        ↓
 Is LED currently OFF?
      /       \
    YES        NO
     ↓          ↓
  Turn ON     Turn OFF
     ↓          ↓
 Update LED state
        ↓
Remember current button state
```

The implementation is:

```cpp
if(lastButtonState == HIGH && currentButtonState == LOW){

    if(ledState == false) {
        digitalWrite(led, HIGH);
        ledState = true;
    }
    else {
        digitalWrite(led, LOW);
        ledState = false;
    }
}

lastButtonState = currentButtonState;
```

---

## 9. LED Operation

An LED (Light Emitting Diode) contains a semiconductor PN junction.

* The **longer lead** is the anode (+).
* The **shorter lead** is the cathode (-).

When forward biased:

* Electrons from the N-type region move toward the PN junction.
* Holes from the P-type region move toward the PN junction.
* Electrons recombine with holes.
* The energy difference is released as photons, producing light.

The wavelength and color of the emitted light depend on the semiconductor material and its energy gap:

* **Blue** → shorter wavelength, higher energy
* **Green** → medium wavelength
* **Red** → longer wavelength, lower energy

The 330 Ω resistor limits the current through the LED.

---

## 10. Why LED Polarity Is Important

An LED is a diode, meaning it allows conventional current to flow primarily in one direction.

For this circuit:

* The anode (+) faces the Arduino output pin.
* The cathode (-) connects toward the resistor and GND.

If the LED is reversed, it becomes reverse-biased and normally does not illuminate under the Arduino's operating voltage.

---

## 11. Software and Hardware Interaction

This project demonstrates a complete input → logic → output cycle:

```text
Push Button
     ↓
Electrical state
     ↓
Arduino digital input
     ↓
Software detects press event
     ↓
Software changes LED state
     ↓
Arduino digital output
     ↓
LED
```

The hardware establishes the electrical state of the button.

The Arduino input pin detects the voltage.

The software interprets the voltage transition as a press event.

The software then changes the stored LED state and controls the output pin.

---

## 12. Engineering Observation

This project builds directly on the previous push-button projects.

The previous projects established:

* Digital input voltage detection.
* `HIGH` and `LOW` logic.
* Pull-up and pull-down resistors.
* Internal pull-up configuration.
* Previous and current button states.

This project adds an important software concept:

> **State changes should be triggered by events, rather than repeatedly by a continuously observed state.**

The project also introduces **stateful behavior**.

Instead of simply saying:

```text
Button pressed → LED ON
```

the program remembers the LED's previous state:

```text
LED OFF + press → LED ON

LED ON + press → LED OFF
```

Therefore, every valid press toggles the output state.

This provides a foundation for more advanced input handling, including **multiple-press detection, double-click detection, timing, debouncing, and event-driven embedded systems**.
