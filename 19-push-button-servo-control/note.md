# Push Button Servo Control — Engineering Notes

## 1. Overview

This project uses a push button to control the position of a servo motor.

Each button press switches the servo's target angle between 0° and 90°.

The project combines digital input, button state detection, program state, and servo position control.

## 2. Components

- Arduino Uno
- Positional servo motor (SG90)
- Push button
- Breadboard
- Jumper wires

## 3. Circuit Connections

### Push Button

- One side → Arduino pin 12
- Opposite side → Arduino GND
- Configured using `INPUT_PULLUP`

### Servo Motor

- Signal wire → Arduino pin 9
- Power wire → 5 V supply
- Ground wire → GND

The servo and Arduino must share a common ground. In Tinkercad, the servo can be powered from the Arduino's 5 V connection for this basic simulation.

## 4. How a Servo Motor Works

A servo motor is an electromechanical device designed to move its output shaft toward a commanded position.

A typical hobby servo contains:

- **DC motor:** converts electrical energy into rotational movement.
- **Gearbox:** reduces rotational speed and increases available torque.
- **Position sensor:** measures the output shaft's position.
- **Control circuit:** compares the requested position with the measured position and controls the motor.

The position sensor provides feedback, allowing the servo to correct its movement rather than simply running the motor for a fixed amount of time.

## 5. Servo Position Control

The Arduino uses the Servo library to command the servo's target angle.

```cpp
#include <Servo.h>

Servo servo;
```

`Servo servo;` creates a Servo object.

```cpp
servo.attach(servoPin);
```

`attach()` associates the servo object with the Arduino pin used for its control signal.

```cpp
servo.write(angle);
```

`write()` commands the servo to move toward the specified angle.

In this project, the target positions are 0° and 90°.

**Important:** `servo.write(angle)` sends a position command. The angle variable represents the requested position, not a measured reading from the servo.

## 6. Push Button and INPUT_PULLUP

The button connects Arduino pin 12 to GND.

With `INPUT_PULLUP`, the Arduino enables an internal pull-up resistor.

| Button condition | Digital reading |
|---|---|
| Released | `HIGH` |
| Pressed | `LOW` |

The internal pull-up resistor keeps the input HIGH when the button is released. Pressing the button connects the input to GND, making it LOW.

## 7. Detecting a Single Press

The program compares the current button state with the previous state.

```cpp
if (lastButtonState == HIGH && currentButtonState == LOW)
```

This detects the transition from HIGH to LOW.

The transition indicates that a new press has occurred. The condition prevents the program from switching the servo position repeatedly while the button remains held down.

At the end of each loop:

```cpp
lastButtonState = currentButtonState;
```

The current reading becomes the previous reading for the next iteration.

## 8. Program State and Angle Switching

The variable:

```cpp
int angle = 0;
```

stores the servo's target position.

When the button is pressed:

- If `angle` is 0, the program changes it to 90.
- Otherwise, the program changes it back to 0.

The sequence is:

`0° → 90° → 0° → 90° → 0°`

This is an example of **state-based control**. The program remembers its current state and uses it to determine the next state.

## 9. Control Workflow

1. The Arduino reads the button.
2. The program checks for a HIGH-to-LOW transition.
3. The target angle changes between 0° and 90°.
4. `servo.write(angle)` sends the new position command.
5. The Serial Monitor displays the target angle.
6. The current button state is saved for the next loop.

The overall relationship is:

**Physical input → state detection → decision → position command → physical movement**

## 10. Key Concepts Learned

- Servo motor
- DC motor
- Gearbox
- Position feedback
- Servo library
- `Servo` object
- `attach()`
- `write()`
- `INPUT_PULLUP`
- `digitalRead()`
- Button state transitions
- `HIGH → LOW` edge detection
- Program state
- Conditional logic
- Positional control
- Serial Monitor

## 11. Key Takeaway

A push button does not directly move the servo. The Arduino detects the button press, changes the target angle, and sends a position command to the servo.

This project demonstrates how a digital input can control a physical actuator through program logic.

The central engineering pattern is:

**Input → decision → output.**
