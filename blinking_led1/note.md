a. Ground is the node connected to the negative terminal of the power supply.
b. The power supply as a whole creates the voltage difference that moves charge.
c. Electrons move from the negative side toward the positive side, but only when there is a complete loop. 
d. In an Arduino circuit where the LED is connected from the pin to ground:
    • Conventional current flows from the Arduino pin → LED → resistor → ground. 
    • Electrons actually flow in the opposite direction: from ground → resistor → LED → Arduino pin.
e. A typical LED contains a semiconductor PN junction.

The longer lead is the anode (+) and the shorter lead is the cathode (-).

When the LED is forward biased, electrons from the N-type region and holes from the P-type region move toward the PN junction.

When an electron recombines with a hole, it transitions to a lower energy state.

The energy difference is released as a photon (light).

The wavelength and color of the emitted light depend on the semiconductor material and the energy gap:

- Blue light: shorter wavelength, higher energy
- Green light: medium wavelength
- Red light: longer wavelength, lower energy

f. Why Polarity Is Important

An LED (Light Emitting Diode) is a diode, meaning it allows current to flow primarily in one direction.

* The anode (+) should be connected toward the positive side of the circuit (the Arduino output pin when it is HIGH).
* The cathode (-) should be connected toward ground through the current-limiting resistor.

If the LED is connected in reverse (anode to ground and cathode to the Arduino pin), it is reverse-biased. Under normal Arduino voltages (5V), almost no current flows through the LED, so it does not emit light.

This is because a diode's internal semiconductor junction permits current in the forward direction but blocks it in the reverse direction under normal operating conditions.
