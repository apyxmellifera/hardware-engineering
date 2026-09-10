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

Ground (GND) is the node connected to the negative terminal of the power supply.

Ground is called **0 V** because it is chosen as the reference point for measuring electrical potential. Voltage is not an absolute quantity; it is always a difference in electric potential between two points. By convention, ground is assigned **0 V**, providing a common reference from which other voltages in the circuit are measured.

The power supply creates the potential difference (voltage) between its positive and negative terminals. This voltage establishes an electric field that drives the movement of electric charge through a closed circuit.

Electrons move from the negative side toward the positive side when a complete conducting path exists. Conventional current flows in the opposite direction.

### LED circuit

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

```text
Approximately 0 V → LOW

Approximately 5 V → HIGH
```

The input pin has very high impedance, so it draws very little current from the external circuit.

---

## 3. Internal Pull-Up

This project uses the Arduino's **internal pull-up resistor**.

```cpp
pinMode(pushButton, INPUT_PULLUP);
```

When `INPUT_PULLUP` is enabled, the Arduino internally connects the input pin to its positive supply through an internal pull-up resistor.

Therefore, no external pull-up resistor is required.

The button is connected between the input pin and GND.

### Button Released

When the button is not pressed, the switch is open.

The internal pull-up keeps the input node at approximately +5 V:

```text
Input ≈ 5 V
    ↓
  HIGH
```

### Button Pressed

When the button is pressed, the switch closes and connects the input node to ground:

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

The Arduino program can respond to either:

1. the button's **current state**, or
2. a **transition between states**.

For reliable press-event detection, the program detects the transition from released to pressed:

```text
HIGH → LOW
```

This transition represents the moment the button is pressed.

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

## 6. One Physical Press Can Become Many Logical Actions

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
...
```

The condition can therefore remain true across many executions of `loop()`.

This means one physical action can cause the program to perform the same logical action repeatedly if the software does not distinguish between a **state** and an **event**.

The important distinction is:

```text
Button state
     ↓
"Is the button currently pressed?"

Press event
     ↓
"Did the button just become pressed?"
```

The press-event condition:

```cpp
lastButtonState == HIGH && currentButtonState == LOW
```

only becomes true during the transition.

At the end of the loop:

```cpp
lastButtonState = currentButtonState;
```

the current state becomes the previous state for the next iteration.

This prevents a continuously held button from being interpreted as a new press event on every loop.

---

## 7. From Button State to Time-Based Input

Previous projects established how to detect a button press.

This project introduces another dimension:

```text
BUTTON STATE + TIME
```

A normal press can be represented as:

```text
HIGH → LOW
```

A long press adds duration:

```text
HIGH → LOW
      ↓
   keep LOW
      ↓
  1000 ms
```

Therefore, a long press is not a special electrical signal produced by the button.

It is a **software interpretation of how long the button remains pressed**.

---

## 8. Starting the Timer

When the button is first pressed, the program records the current time:

```cpp
pressStartTime = currentTime;
```

This happens when the transition:

```text
HIGH → LOW
```

is detected.

For example:

```text
Button pressed
      ↓
pressStartTime = 5000 ms
```

The recorded time becomes the reference point for measuring the duration of the press.

The timer must not be continuously reset while the button is held.

If it were:

```text
pressStartTime = currentTime
```

on every loop iteration, then the difference between the current time and start time would remain close to zero.

The program therefore starts the timer **once**, at the beginning of the press.

---

## 9. The `millis()` Function

Arduino provides the `millis()` function for measuring elapsed time.

```cpp
millis()
```

It returns the number of milliseconds that have passed since the Arduino program started.

For example:

```text
Arduino starts
     ↓
   0 ms

After 1 second
     ↓
  1000 ms

After 2 seconds
     ↓
  2000 ms
```

The return value is stored in an `unsigned long`:

```cpp
unsigned long currentTime = millis();
```

An `unsigned long` is appropriate because the value returned by `millis()` can become large during program execution.

---

## 10. Measuring How Long the Button Is Held

Once the starting time has been recorded, the program can calculate the duration of the button press:

```cpp
elapsedTime = currentTime - pressStartTime;
```

For example:

```text
Button pressed at:

pressStartTime = 5000 ms
```

Later:

```text
currentTime = 5800 ms
```

Therefore:

```text
5800 ms - 5000 ms
= 800 ms
```

The button has been held for 800 milliseconds.

As long as the button remains pressed, subsequent executions of `loop()` continue updating the elapsed time.

```text
800 ms
801 ms
802 ms
803 ms
...
```

The timer therefore represents the **duration of the current button press**.

---

## 11. Counter vs Timer

A counter answers:

> **How many times did something happen?**

A timer answers:

> **How much time has passed?**

The previous double-press project required both:

```text
Counter → HOW MANY PRESSES?

Timer   → HOW FAR APART WERE THEY?
```

The long-press project changes the role of the timer.

Here, the timer answers:

```text
HOW LONG HAS THIS PRESS BEEN HELD?
```

Therefore:

```text
Double press → time between events

Long press   → duration of one continuous event
```

This is an important difference between the two projects.

---

## 12. Why `millis()` Is Stored Outside `loop()`

The press start time must survive between executions of `loop()`.

Therefore, the variable is declared outside the function:

```cpp
unsigned long pressStartTime = 0;
```

If it were declared inside `loop()`:

```cpp
void loop()
{
    unsigned long pressStartTime = millis();
}
```

the variable would be recreated during each loop iteration.

The program would therefore lose the previously stored starting point.

The distinction is:

```text
Outside loop
     ↓
State persists between loop iterations

Inside loop
     ↓
Local variable is recreated during each iteration
```

This is another example of **state persistence** in embedded software.

---

## 13. Non-Blocking Timing

`millis()` allows the Arduino to measure elapsed time without stopping the entire program.

For example:

```cpp
unsigned long currentTime = millis();
```

simply reads the current elapsed time.

It does not pause the Arduino.

This is different from:

```cpp
delay(1000);
```

`delay()` blocks the program for approximately one second.

With `millis()`:

```text
Read time
   ↓
Continue executing loop
   ↓
Read time again
   ↓
Calculate elapsed time
   ↓
Continue executing loop
```

Therefore, `millis()` is useful for building responsive, time-dependent embedded systems.

---

## 14. Long-Press Threshold

The project defines a long press as a button being held for at least one second:

```cpp
const unsigned long longPressInterval = 1000;
```

This means:

```text
1000 milliseconds
      =
1 second
```

The program checks whether:

```text
elapsedTime >= longPressInterval
```

Conceptually:

```text
elapsedTime < 1000 ms
        ↓
   Still waiting

elapsedTime >= 1000 ms
        ↓
 Long press detected
```

The `>=` condition is important because the long press should be recognized once the elapsed time reaches the defined threshold.

---

## 15. Detecting the Long Press

The button must satisfy two conditions:

```text
Button is currently pressed
        +
Enough time has elapsed
        ↓
   LONG PRESS
```

In logical form:

```text
currentButtonState == LOW

AND

elapsedTime >= 1000 ms
```

This produces the higher-level event:

```text
LONG PRESS
```

The physical button itself only provides the electrical state.

The software creates the concept of a long press.

---

## 16. Long Press vs Normal Press

A normal press can happen quickly:

```text
PRESS
  ↓
RELEASE
```

A long press requires the button to remain pressed:

```text
PRESS
  ↓
HOLD
  ↓
HOLD
  ↓
HOLD
  ↓
1000 ms reached
  ↓
LONG PRESS
```

Therefore, the difference is not the button hardware.

The difference is the **duration of the button state**.

---

## 17. Long-Press Behavior

The behavior of this project is:

```text
Single short press
       ↓
Nothing happens
```

A button held for less than one second does not activate the LED.

A button held for at least one second:

```text
PRESS
  ↓
HOLD for ≥ 1 second
  ↓
LONG PRESS
  ↓
LED ON
```

When the button is released:

```text
RELEASE
  ↓
LED OFF
```

Therefore:

```text
Hold for 1 second → LED ON
Release           → LED OFF
```

This is different from a toggle.

The LED does not permanently change state after the long press.

Instead, the LED is controlled by the long-press interaction.

---

## 18. Current State vs Press Duration

The project now combines two different types of information.

### Current state

```text
currentButtonState == LOW
```

answers:

> Is the button currently being held?

### Elapsed time

```text
currentTime - pressStartTime
```

answers:

> How long has it been held?

Together:

```text
Current button state
        +
Elapsed duration
        ↓
Long-press decision
```

This is a more advanced form of input processing than simply reading `HIGH` or `LOW`.

---

## 19. Long-Press Algorithm

The complete algorithm can be represented as:

```text
Read current button state
        ↓
Detect HIGH → LOW transition
        ↓
      Press
        ↓
   Start timer
        ↓
     HOLDING
        ↓
Is button still LOW?
     /       \
   NO         YES
   ↓           ↓
Release    Calculate elapsed time
               ↓
       Has 1 second elapsed?
          /          \
        NO            YES
        ↓              ↓
   Keep waiting    LONG PRESS
                       ↓
                    LED ON
                       ↓
                    HOLDING
                       ↓
                    RELEASE
                       ↓
                    LED OFF
```

The key sequence is:

```text
PRESS
  ↓
START TIMER
  ↓
HOLD
  ↓
MEASURE DURATION
  ↓
REACH THRESHOLD
  ↓
LONG PRESS
  ↓
LED ON
  ↓
RELEASE
  ↓
LED OFF
```

---

## 20. Why the LED Should Not Turn On Immediately

The purpose of the project is to distinguish a short press from a long press.

Therefore, turning the LED on immediately when:

```text
HIGH → LOW
```

would defeat the purpose of the timing logic.

The program first records the press:

```text
HIGH → LOW
```

and then waits while the button remains:

```text
LOW
```

Only after:

```text
elapsedTime >= 1000 ms
```

does the program interpret the action as a long press.

---

## 21. Release Detection

Because `INPUT_PULLUP` is being used:

```text
Pressed  → LOW

Released → HIGH
```

Therefore, release can be detected using:

```cpp
if(currentButtonState == HIGH)
```

When the button is released, the LED is turned off.

This gives the project its final behavior:

```text
Button released → LED OFF

Button pressed
     ↓
Hold < 1 second
     ↓
LED OFF

Button pressed
     ↓
Hold ≥ 1 second
     ↓
LED ON

Release
     ↓
LED OFF
```

---

## 22. LED Operation

An LED (Light Emitting Diode) contains a semiconductor PN junction.

* The **longer lead** is the anode (+).
* The **shorter lead** is the cathode (-).

When forward biased:

* Electrons from the N-type region move toward the PN junction.
* Holes from the P-type region move toward the PN junction.
* Electrons recombine with holes.
* The energy difference is released as photons, producing light.

The wavelength and color of the emitted light depend on the semiconductor material and its energy gap.

```text
Blue  → shorter wavelength, higher energy

Green → medium wavelength

Red   → longer wavelength, lower energy
```

The 330 Ω resistor limits the current through the LED.

---

## 23. Why LED Polarity Is Important

An LED is a diode, meaning it allows conventional current to flow primarily in one direction.

For this circuit:

```text
Arduino output pin
       ↓
    Anode (+)
       ↓
      LED
       ↓
   Cathode (-)
       ↓
   330 Ω resistor
       ↓
      GND
```

If the LED is reversed, it becomes reverse-biased and normally does not illuminate under the Arduino's operating voltage.

---

## 24. Software and Hardware Interaction

This project demonstrates a complete:

```text
hardware
   ↓
input
   ↓
state
   ↓
event
   ↓
timing
   ↓
logic
   ↓
output
```

cycle.

More specifically:

```text
Push Button
     ↓
Electrical state
     ↓
Arduino digital input
     ↓
Detect HIGH → LOW transition
     ↓
Press event
     ↓
Start timer
     ↓
Measure button duration
     ↓
Compare duration with threshold
     ↓
Determine LONG PRESS
     ↓
Arduino digital output
     ↓
LED
```

The hardware establishes the electrical state of the button.

The Arduino input pin detects the voltage.

The software interprets the voltage transition as a press event.

The software then uses elapsed time to determine whether the physical press qualifies as a long press.

---

## 25. Engineering Observation

This project builds directly on the previous push-button projects.

The previous projects established:

* Digital input voltage detection.
* `HIGH` and `LOW` logic.
* Pull-up and pull-down resistors.
* Internal pull-up configuration.
* Previous and current button states.
* Press-event detection.
* Stateful LED control.
* Single-press toggling.
* Press counting.
* Time measurement with `millis()`.

This project adds:

* Measuring the duration of one continuous button press.
* Long-press detection.
* Time thresholds.
* Continuous-state monitoring.
* Release detection.
* Duration-based output control.

The conceptual progression is:

```text
Button state
     ↓
State transition
     ↓
Press event
     ↓
Start timer
     ↓
Continuous state
     ↓
Measure duration
     ↓
Compare against threshold
     ↓
Higher-level event
     ↓
Long press
```

A long press is therefore not a special physical property of the button.

It is a **software interpretation of a button remaining in a particular electrical state for a defined period of time**.

---

## 26. Stateful Event Processing

The project now contains several pieces of state:

```cpp
int lastButtonState = HIGH;

bool ledState = false;

unsigned long pressStartTime = 0;

unsigned long elapsedTime = 0;
```

Each variable remembers something about the system.

Conceptually:

```text
lastButtonState
      ↓
What was the button doing previously?

pressStartTime
      ↓
When did the current press begin?

elapsedTime
      ↓
How long has the current press lasted?

ledState
      ↓
What is the current logical LED state?
```

The program therefore combines:

```text
Current input
      +
Previous state
      +
Start time
      +
Elapsed time
      +
Output state
      ↓
Current system behavior
```

This is a foundation for more advanced embedded software such as:

* Button debouncing
* Long-press detection
* Double-click detection
* Triple-click detection
* Menu navigation
* Timers
* State machines
* Event-driven systems
* User-interface input handling
* Non-blocking control systems

---

## 27. Key Engineering Lesson

The main lesson from this project is:

> **A long press is not a different electrical signal. It is a normal button press whose duration is measured by software.**

The Arduino detects:

```text
LOW
```

The software determines:

```text
LOW for ≥ 1000 ms
```

and interprets that as:

```text
LONG PRESS
```

This demonstrates how embedded software turns simple electrical signals into meaningful user interactions.

The complete concept is:

```text
Physical action
      ↓
Electrical state
      ↓
Digital input
      ↓
State transition
      ↓
Time measurement
      ↓
Software interpretation
      ↓
Higher-level event
      ↓
Output action
```

This is one of the fundamental ideas behind embedded user interfaces: **simple hardware signals can become sophisticated interactions through software state and timing.**
