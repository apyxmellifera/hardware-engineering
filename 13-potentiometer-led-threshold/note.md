# Potentiometer — Analog Input and Threshold Control

## 1. Project Overview

This project introduces **analog input** using a potentiometer.

Previous projects mainly dealt with digital signals:

```text
HIGH ──── 5V
LOW  ──── 0V
```

A potentiometer introduces something different: a voltage that can vary continuously between approximately 0 V and 5 V.

The Arduino reads this changing voltage through an analog input and converts it into a numerical value that software can work with.

The project then uses that value to make a decision:

```text
Potentiometer
      ↓
Variable voltage
      ↓
Analog input A0
      ↓
ADC
      ↓
0–1023
      ↓
Voltage calculation
      ↓
Threshold decision
      ↓
LED ON / OFF
```

---

# 2. What Is a Potentiometer?

A potentiometer is a **variable resistor with three terminals**.

Internally, it contains a resistive track and a movable contact called the **wiper**.

```text
5V ───────[ Resistive Track ]────── GND
                       ↑
                     Wiper
                       │
                       ↓
                      A0
```

The two outer pins connect to the ends of the resistive track.

The middle pin connects to the wiper.

When the knob is turned, the wiper moves along the resistive track.

This changes the voltage appearing at the middle pin.

Therefore, the potentiometer acts as a **variable voltage source for the analog input**.

---

# 3. Potentiometer Connections

The potentiometer was connected as:

```text
Potentiometer

Pin 1 ───────── 5V
Pin 2 ───────── A0
Pin 3 ───────── GND
```

The middle pin is the important one for the Arduino because it is connected to the wiper.

The two outer pins determine the direction of the voltage change.

If the outer connections are reversed:

```text
GND ───────── Pin 1
A0  ───────── Pin 2
5V  ───────── Pin 3
```

the potentiometer still works, but the direction of increasing/decreasing values is reversed.

For example, clockwise might increase the ADC value in one wiring arrangement and decrease it in the other.

---

# 4. The Potentiometer as a Voltage Divider

The potentiometer can be understood as two variable resistances:

```text
             5V
              │
              R₁
              │
              ├────── A0
              │
              R₂
              │
             GND
```

As the wiper moves:

* `R₁` changes
* `R₂` changes
* the voltage at the wiper changes

The total resistance of the potentiometer can remain approximately constant while the ratio between the two sections changes.

This is why the potentiometer can produce a variable voltage.

---

# 5. Analog vs Digital Input

A digital input generally answers:

```text
Is the voltage HIGH or LOW?
```

An analog input gives us information about **where the voltage lies within a range**.

For this project:

```text
0V ─────────────────────────────── 5V
 │                                  │
 │                                  │
0                                  1023
```

Instead of simply knowing:

```text
LOW
HIGH
```

we can obtain values such as:

```text
0
247
491
768
1023
```

This gives the program much more information about the physical input.

---

# 6. The Arduino ADC

The Arduino Uno uses a **10-bit Analog-to-Digital Converter (ADC)** for its analog inputs.

"10-bit" means:

```text
2¹⁰ = 1024
```

possible values.

Because the values start at zero, the range is:

```text
0 → 1023
```

Therefore:

```text
0 V       → approximately 0
5 V       → approximately 1023
```

Intermediate voltages produce intermediate ADC readings.

For example:

```text
0 V       → 0
1.25 V    → ~256
2.5 V     → ~512
3.75 V    → ~768
5 V       → 1023
```

These are approximate values.

---

# 7. `analogRead()`

The Arduino function used to read the potentiometer is:

```cpp
analogRead(pot);
```

For example:

```cpp
int potValue = analogRead(pot);
```

If:

```cpp
int pot = A0;
```

then:

```cpp
analogRead(pot);
```

reads the voltage present on A0.

The result is a number between:

```text
0 and 1023
```

---

# 8. ADC Value vs Voltage

The ADC value is not itself a voltage.

It is a numerical representation of the voltage.

The relationship can be written as:

```text
ADC reading
─────────── × reference voltage
maximum ADC value
```

For the Arduino Uno experiment:

```text
voltage = (potValue × 5.0) / 1023.0
```

For example, if:

```text
potValue = 491
```

then:

```text
voltage = (491 × 5) / 1023
        ≈ 2.40 V
```

So an ADC reading of approximately 491 represents roughly 2.4 V under the assumed 5 V reference.

---

# 9. Why `float` Is Used

The ADC reading is stored as an integer:

```cpp
int potValue = analogRead(pot);
```

because the ADC produces a whole-number reading.

The voltage calculation can produce a fractional value:

```text
2.40
3.75
1.21
```

Therefore we use:

```cpp
float voltage;
```

A `float` can represent decimal values.

---

# 10. The First Potentiometer Program

The first experiment simply displayed the ADC value:

```cpp
int pot = A0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int potValue = analogRead(pot);

  Serial.println(potValue);
}
```

The experiment showed:

```text
Minimum → 0
Middle  → approximately 491
Maximum → 1023
```

The middle value did not need to be exactly 512 because the physical knob position does not necessarily correspond to the exact electrical midpoint.

---

# 11. Reading the Voltage

The next version converted the ADC reading into an approximate voltage:

```cpp
int potValue = analogRead(pot);

float voltage = (potValue * 5.0) / 1023.0;

Serial.println(voltage);
```

This allowed the physical position of the knob to be observed as both:

```text
ADC value
```

and:

```text
Voltage
```

---

# 12. Threshold Logic

The project then introduced a decision based on the voltage.

The chosen threshold was:

```text
2.6 V
```

The logic was:

```text
              Voltage
                 │
                 ↓
          Is voltage ≥ 2.6 V?
             /          \
           YES           NO
            ↓             ↓
          HIGH           LOW
```

In C++:

```cpp
if (voltage >= 2.6)
{
  Serial.println("High");
}
else
{
  Serial.println("Low");
}
```

The important concept here is that the program is no longer simply measuring the physical world.

It is **making a decision based on the measurement**.

---

# 13. Controlling the LED

The threshold was then connected to the LED.

```cpp
if (voltage >= 2.6)
{
  digitalWrite(led, HIGH);
  Serial.println("Led ON");
  Serial.println(voltage);
}
else
{
  digitalWrite(led, LOW);
  Serial.println("Led OFF");
  Serial.println(voltage);
}
```

The behavior becomes:

```text
Voltage ≥ 2.6 V
       ↓
     LED ON


Voltage < 2.6 V
       ↓
     LED OFF
```

---

# 14. Why the `else` Was Important

An earlier version had:

```cpp
if (voltage >= 2.6)
{
  digitalWrite(led, HIGH);
}

digitalWrite(led, LOW);
```

The problem was that the `LOW` command was **outside the `if` block**.

Therefore it executed every loop iteration.

The sequence became:

```text
Condition is TRUE
      ↓
LED HIGH
      ↓
LED LOW
```

The LED was therefore immediately turned off again.

Putting the `LOW` command inside `else` makes the two possible paths mutually exclusive:

```text
             Condition
                 │
        ┌────────┴────────┐
        ↓                 ↓
      TRUE              FALSE
        ↓                 ↓
      HIGH              LOW
```

This reinforced the importance of understanding **program flow and block scope**.

---

# 15. Complete Project Code

```cpp
// 13-potentiometer-led-threshold

int led = 12;
int pot = A0;

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int potValue = analogRead(pot);
  float voltage = (potValue * 5.0) / 1023.0;

  if (voltage >= 2.6)
  {
    digitalWrite(led, HIGH);
    Serial.println("Led ON");
    Serial.println(voltage);
  }
  else
  {
    digitalWrite(led, LOW);
    Serial.println("Led OFF");
    Serial.println(voltage);
  }
}
```

---

# 16. Engineering Flow

The complete system can be viewed as:

```text
                PHYSICAL WORLD
                     │
                     ↓
             Turn potentiometer
                     │
                     ↓
             Wiper position
                     │
                     ↓
             Variable voltage
                     │
                     ↓
              ┌────────────┐
              │     A0     │
              └────────────┘
                     │
                     ↓
                    ADC
                     │
                     ↓
                 0–1023
                     │
                     ↓
             Voltage calculation
                     │
                     ↓
              Threshold check
                     │
              ┌──────┴──────┐
              ↓             ↓
           ≥ 2.6 V       < 2.6 V
              ↓             ↓
          LED HIGH       LED LOW
              │             │
              └──────┬──────┘
                     ↓
                  LED
```

---

# 17. What Changed From Previous Projects?

The earlier button projects followed a pattern like:

```text
Physical button
      ↓
Digital input
      ↓
HIGH / LOW
      ↓
Program decision
      ↓
Output
```

This project introduced:

```text
Physical potentiometer
      ↓
Variable voltage
      ↓
Analog input
      ↓
ADC conversion
      ↓
Numerical value
      ↓
Mathematical processing
      ↓
Program decision
      ↓
Digital output
```

This is a significant step because the program is now working with **measured numerical values**, not just two digital states.

---

# 18. Important Concepts Learned

### Potentiometer

A three-terminal variable resistor whose wiper can provide a variable voltage.

### Wiper

The movable contact inside the potentiometer.

### Analog input

An input that allows the Arduino to measure a range of voltages rather than simply HIGH or LOW.

### ADC

Analog-to-Digital Converter.

It converts the physical voltage into a numerical representation that software can process.

### 10-bit resolution

The Arduino Uno's ADC provides:

```text
2¹⁰ = 1024 levels
```

represented by:

```text
0–1023
```

### Threshold

A chosen value used to divide measurements into different behaviors.

This project uses:

```text
2.6 V
```

### Analog input → digital decision

Although the input is analog, the program can still use it to make a digital decision:

```text
Analog measurement
       ↓
    threshold
       ↓
Digital decision
```

---

# 19. Important Distinction

This project is called:

```text
13-potentiometer-led-threshold
```

because the potentiometer is **not controlling LED brightness yet**.

The LED currently has only two states:

```text
ON
OFF
```

The potentiometer determines **when the state changes**.

Actual brightness control will require a different technique:

```text
Potentiometer
      ↓
Analog reading
      ↓
Map reading to output range
      ↓
PWM
      ↓
Variable LED brightness
```

That will be introduced separately rather than being mixed into this project.

---

# 20. Key Takeaway

The most important idea from this project is:

```text
INPUT → PROCESS → DECISION → OUTPUT
```

Specifically:

```text
Potentiometer
     ↓
analogRead()
     ↓
ADC value
     ↓
Voltage calculation
     ↓
Threshold comparison
     ↓
digitalWrite()
     ↓
LED
```

This pattern is fundamental to embedded programming.

A physical signal enters the system, software processes the measurement, a decision is made, and the program produces a physical response.
