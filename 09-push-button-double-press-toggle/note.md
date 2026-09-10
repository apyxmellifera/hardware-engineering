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

c. The power supply creates the potential difference (voltage) between its positive and negative terminals. This voltage establishes an electric field that drives the movement of electric charge through a closed circuit.

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

The important distinction is that the Arduino program can respond to either:

1. the button's **current state**, or
2. a **transition between states**.

For reliable press-event detection, the program should detect the transition from released to pressed.

```text
HIGH → LOW
```

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

Instead, a valid event changes the LED state.

For a single-press toggle:

```text
Press event
     ↓
Check LED state
     ↓
OFF → ON
ON  → OFF
```

This is called **toggling**.

The same idea is used in this project, except the event is now a **double press** rather than a single press.

---

## 8. From Single-Press Detection to Double-Press Detection

The previous project detected one event:

```text
HIGH → LOW
     ↓
Press
     ↓
Toggle LED
```

This project introduces a more complex event:

```text
HIGH → LOW
     ↓
First press
     ↓
Wait for another press
     ↓
HIGH → LOW
     ↓
Second press
     ↓
Check time between presses
     ↓
Double press?
     ↓
YES → Toggle LED
```

Therefore, a double press is not simply a button state.

It is a **sequence of two press events occurring within a certain amount of time**.

---

## 9. Press Counting

The program needs to remember how many valid presses have occurred.

```cpp
int pressCount = 0;
```

The counter represents the current stage of the double-press detection:

```text
0 → No press waiting

1 → First press detected

2 → Two presses detected
```

When a new press event occurs:

```cpp
pressCount++;
```

The program can then determine what to do based on the number of presses.

```text
First press
    ↓
pressCount = 1

Second press
    ↓
pressCount = 2
```

However, counting alone is not enough.

The program also needs to know **how far apart the two presses were**.

---

## 10. Counter vs Timer

A counter answers:

> **How many times did something happen?**

A timer answers:

> **How much time has passed?**

For double-press detection, both are required.

```text
Counter → HOW MANY PRESSES?

Timer   → HOW FAR APART WERE THEY?
```

The counter identifies the first and second press.

The timer determines whether the second press occurred soon enough to be considered part of the same double press.

---

## 11. The `millis()` Function

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

An `unsigned long` is appropriate because `millis()` can grow to a large value during program execution.

---

## 12. Why the First Press Time Must Be Stored

When the first press occurs, the program records the current time:

```cpp
firstPressTime = currentTime;
```

For example:

```text
First press
    ↓
firstPressTime = 2500 ms
```

When the second press occurs:

```text
Second press
    ↓
currentTime = 3100 ms
```

The program can calculate how much time passed:

```cpp
currentTime - firstPressTime
```

Therefore:

```text
3100 ms - 2500 ms
= 600 ms
```

The two presses were 600 milliseconds apart.

---

## 13. Measuring Elapsed Time

The important pattern is:

```cpp
currentTime - firstPressTime
```

This gives the elapsed time since the first press.

For example:

```cpp
unsigned long currentTime = millis();

if (currentTime - firstPressTime <= doublePressInterval)
{
    // Double press occurred within the allowed interval
}
```

If:

```cpp
firstPressTime = 2500;
currentTime = 3100;
```

then:

```text
3100 - 2500 = 600 ms
```

If the allowed double-press interval is 1000 ms:

```text
600 ms <= 1000 ms
```

so the second press is considered part of the double press.

---

## 14. Why `millis()` Is Stored Outside `loop()`

The first press time must survive between executions of `loop()`.

Therefore:

```cpp
unsigned long firstPressTime = 0;
```

is declared outside `loop()`.

If it were declared inside:

```cpp
void loop()
{
    unsigned long firstPressTime = millis();
}
```

the variable would be recreated every time `loop()` executes.

The program would therefore lose the previous value.

The important distinction is:

```text
Outside loop
    ↓
State persists between loop iterations

Inside loop
    ↓
Local variable is recreated during each loop iteration
```

This is another example of **state persistence** in embedded software.

---

## 15. Non-Blocking Timing

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

During that delay, the Arduino cannot normally perform the rest of the loop's logic.

With `millis()`:

```text
Read time
   ↓
Continue executing loop
   ↓
Read time again
   ↓
Compare elapsed time
```

Therefore, `millis()` is useful for building responsive, time-dependent embedded systems.

---

## 16. Double-Press Time Window

The program defines an allowed interval:

```cpp
const unsigned long doublePressInterval = 1000;
```

This means the second press must occur within 1000 milliseconds of the first press.

Conceptually:

```text
First press
    │
    │<--------- 1000 ms --------->│
    │                              │
    └────── Double-press window ──┘
```

If the second press occurs inside this window:

```text
First press → Second press
       < 1000 ms
             ↓
      Double press
```

If it occurs after the window:

```text
First press →──────────────→ Second press
             > 1000 ms
                    ↓
              Too late
```

The exact interval can be adjusted depending on how quickly two presses should be performed.

---

## 17. Double-Press Algorithm

The complete algorithm is:

```text
Read current button state
        ↓
Detect HIGH → LOW transition
        ↓
     Press event
        ↓
    Increment count
        ↓
Is this the first press?
      /       \
    YES        NO
     ↓          ↓
Record time   Is this second press?
                ↓
              YES
                ↓
       Calculate elapsed time
                ↓
       Is elapsed time within
       double-press interval?
             /       \
           YES        NO
            ↓          ↓
      Double press   Too late
            ↓          ↓
       Toggle LED   Start new
                    first press
            ↓
       Reset count
```

---

## 18. Double-Press Toggle Behavior

The intended behavior is:

```text
Single press
     ↓
Nothing happens

Double press
     ↓
LED toggles

Another double press
     ↓
LED toggles again
```

Therefore:

```text
Initial state
LED OFF

Single press
LED OFF

Double press
LED ON

Single press
LED ON

Double press
LED OFF
```

The button is therefore being used as a **two-event input device**.

---

## 19. Timeout Handling

A first press cannot remain pending forever.

Suppose:

```text
First press
    ↓
Wait...
    ↓
Wait...
    ↓
Wait...
    ↓
No second press
```

After the allowed interval has expired, the first press is no longer considered part of a possible double press.

The program resets the counter:

```cpp
pressCount = 0;
```

Conceptually:

```text
First press
    ↓
Start timer
    ↓
Wait for second press
    ↓
Time limit exceeded
    ↓
Cancel pending double press
    ↓
Return to waiting state
```

This is called a **timeout**.

Timeouts are an important concept in embedded systems because software often needs to wait for an event without waiting forever.

---

## 20. Resetting the Double-Press Sequence

When a valid double press is detected:

```cpp
pressCount = 0;
```

The program returns to its initial state:

```text
No pending press
```

The sequence therefore becomes:

```text
0 presses
    ↓
First press
    ↓
1 press
    ↓
Second press
    ↓
2 presses
    ↓
Double press detected
    ↓
Toggle LED
    ↓
Reset
    ↓
0 presses
```

This allows the process to repeat indefinitely.

---

## 21. LED Operation

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

## 22. Why LED Polarity Is Important

An LED is a diode, meaning it allows conventional current to flow primarily in one direction.

For this circuit:

* The anode (+) faces the Arduino output pin.
* The cathode (-) connects toward the resistor and GND.

If the LED is reversed, it becomes reverse-biased and normally does not illuminate under the Arduino's operating voltage.

---

## 23. Software and Hardware Interaction

This project demonstrates a complete hardware → input → event → timing → logic → output cycle:

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
Count press
     ↓
Measure time between presses
     ↓
Determine whether it is a double press
     ↓
Toggle stored LED state
     ↓
Arduino digital output
     ↓
LED
```

The hardware establishes the electrical state of the button.

The Arduino input pin detects the voltage.

The software interprets the voltage transition as a press event.

The software counts press events and measures the time between them.

The software then determines whether the two events form a double press and changes the stored LED state.

---

## 24. Engineering Observation

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

This project adds:

* Press counting.
* Elapsed-time measurement.
* `millis()`.
* Non-blocking timing.
* Time windows.
* Double-press detection.
* Timeout handling.
* Event grouping.

The important conceptual progression is:

```text
Button state
     ↓
State transition
     ↓
Press event
     ↓
Multiple events
     ↓
Events separated by time
     ↓
Grouped event
     ↓
Double press
```

A double press is therefore not a special physical property of the button.

It is a **software interpretation of two separate press events occurring within a defined time window**.

This demonstrates an important embedded-systems principle:

> **Physical actions become meaningful system events through software interpretation.**

The button produces electrical state changes.

The microcontroller detects those state changes.

The software decides whether individual transitions represent a single press, a double press, or another higher-level event.

---

## 25. Stateful Event Processing

The project now contains several pieces of state:

```cpp
int lastButtonState = HIGH;
bool ledState = false;
unsigned long firstPressTime = 0;
int pressCount = 0;
```

Each variable remembers something about what happened previously.

Conceptually:

```text
lastButtonState
    ↓
What was the button doing?

pressCount
    ↓
How many presses are currently in the sequence?

firstPressTime
    ↓
When did the sequence begin?

ledState
    ↓
What is the current output state?
```

The program therefore does not simply react to the current input.

It combines:

```text
Current input
     +
Previous state
     +
Event count
     +
Elapsed time
     +
Stored output state
     ↓
Current system behavior
```

This is a foundation for more advanced embedded software such as:

* Button debouncing
* Long-press detection
* Triple-click detection
* Menu navigation
* Timers
* State machines
* Event-driven systems
* User-interface input handling
* Non-blocking control systems
