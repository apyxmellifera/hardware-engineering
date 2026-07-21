# Blinking LED

## Demo Video

https://youtu.be/eezdAk9oCLw

## Objective

1. Learn how to control a digital output pin using Arduino.
2. Understand how software instructions produce a physical electrical effect in a circuit.

---

## Components

- Arduino Uno
- LED
- 220Ω resistor
- Breadboard
- Jumper wires

---

## Engineering Procedure

### Circuit Connections

1. Connect the cathode (-) of the LED to one end of a 220Ω resistor.
2. Connect the other end of the resistor to the Arduino GND pin.
3. Connect the anode (+) of the LED to Arduino digital pin 5.

---

## Physics

### Power Source

The Arduino receives power from the USB connection.

When digital pin 5 is configured as an output and set HIGH, it provides approximately 5V.

### Voltage Difference

Ground is maintained at approximately 0V.

The voltage difference between pin 5 and ground creates an electric field that causes charge to move through the circuit.

### Current Flow

Conventional current flows:

Pin 5 → LED → Resistor → GND

As current passes through the LED, the semiconductor junction emits photons, producing visible light.

When pin 5 is set LOW, both sides of the circuit are approximately 0V, so current stops flowing and the LED turns off.

### Current Calculation

Assuming:

- Supply Voltage = 5V
- LED Forward Voltage ≈ 2V
- Resistor = 220Ω

Using Ohm's Law:

I = (5V - 2V) / 220Ω

I = 0.0136A

I ≈ 13.6mA

---

## Software Engineering Insight

The Arduino pin behaves like a Boolean output:

```text
HIGH -> LED ON
LOW  -> LED OFF
```

The `loop()` function executes continuously.

Each iteration changes the state of the digital output, causing the LED to switch between ON and OFF states.

This project demonstrates how software instructions can directly influence physical hardware behavior.

---

## Files

- `code.ino` - Arduino source code
- `blinking_led.png` - Circuit screenshot from Tinkercad
- `blinking_led_schema.png` - Schematic view from Tinkercad
- `note.md` - Deeper engineering and physics note
- `README.md` - Project summary