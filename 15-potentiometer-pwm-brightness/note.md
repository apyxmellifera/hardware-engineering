# Potentiometer PWM Brightness

## Objective

Learn how to use a potentiometer to control LED brightness by converting an analog input value into a PWM output value.

```text
Potentiometer
      ↓
analogRead()
      ↓
ADC (0–1023)
      ↓
map()
      ↓
PWM (0–255)
      ↓
LED Brightness
```

## ADC Input

The Arduino Uno uses a **10-bit ADC**:

$$
2^{10} = 1024
$$

Therefore, the ADC range is:

```text
0–1023
```

Approximately:

```text
0 V → 0
5 V → 1023
```

At approximately 2.5 V:

$$
\frac{2.5}{5} \times 1023 \approx 512
$$

So:

```text
2.5 V → ADC ≈ 512
```

## `map()`

`map()` converts a value from one range into another:

```text
map(value, fromLow, fromHigh, toLow, toHigh)
```

In this project:

```text
0–1023 → 0–255
```

The general calculation is:

$$
\text{Output} =
\frac{\text{Input} - \text{Input Min}}
{\text{Input Max} - \text{Input Min}}
\times
(\text{Output Max} - \text{Output Min})
+
\text{Output Min}
$$

For this project:

$$
\text{PWM} =
\frac{\text{ADC}}{1023} \times 255
$$

### Examples

**ADC = 256**

$$
\frac{256}{1023} \times 255 \approx 63
$$

```text
256 → 63
```

**ADC = 512**

$$
\frac{512}{1023} \times 255 \approx 127
$$

```text
512 → 127
```

**ADC = 768**

$$
\frac{768}{1023} \times 255 \approx 191
$$

```text
768 → 191
```

## PWM and Duty Cycle

The PWM value determines the duty cycle:

$$
\text{Duty Cycle} =
\frac{\text{PWM Value}}{255} \times 100
$$

Examples:

| PWM | Duty Cycle |
| --: | ---------: |
|   0 |         0% |
|  63 |      24.7% |
| 127 |      49.8% |
| 191 |      74.9% |
| 255 |       100% |

## Serial Monitor

The Serial Monitor lets us observe the conversion:

```text
ADC: 512 | PWM: 127
```

This makes the relationship visible:

```text
ADC value
    ↓
  map()
    ↓
PWM value
```

## Key Takeaway

Project 15 combines the main concepts from Projects 13 and 14:

```text
Analog Input
     ↓
ADC 0–1023
     ↓
Range Mapping
     ↓
PWM 0–255
     ↓
LED Brightness
```

The main new concept is **mapping one numerical range to another while preserving the relative position of the value**.
