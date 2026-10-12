# Lesson 02: Electricity, Resistance & GPIO

## Objective

Understand voltage, current, resistance, Ohm's law, and how a resistor controls LED current.

## 1. Core Concepts

- **Voltage (V):** Electrical potential difference that drives current.
- **Current (A):** Flow of electric charge through a circuit.
- **Resistance (Ω):** Opposition to current flow.
- **GPIO:** General-Purpose Input/Output pins used by a microcontroller to interact with external components.

## 2. Ohm's Law

[
I = \frac{V}{R}
]

Where:

- I = current in amperes (A)
- V = voltage across the resistor in volts (V)
- R = resistance in ohms (Ω)

For a constant voltage, increasing resistance decreases current.

## 3. Practical Experiment

**Platform:** Tinkercad Circuits
**Components:** Arduino Uno, red LED, resistor, multimeter

Circuit:
Arduino D13 → LED → Resistor → GND

Arduino code:

```
#define LED 13

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
}

void loop() {
}
```

## 4. Observations

| Resistance | Measured current | LED brightness |
| ---------- | ---------------- | -------------- |
| 220 Ω      | 9.60 mA          | Bright         |
| 1 kΩ       | 2.58 mA          | Dim            |
| 10 kΩ      | 328 µA           | Appeared off   |

Measured voltage:

- LED at 220 Ω: 2.41 V
- Resistor at 220 Ω: 2.11 V
- Resistor at 1 kΩ: 2.58 V
- Resistor at 10 kΩ: 2.83 V

Note: At 10 kΩ, the measured values do not match the simple Ohm's law calculation exactly. Record both observations and investigate the discrepancy later.

## 5. Multimeter Rules

- **Voltage:** Connect probes in parallel across the component.
- **Current:** Connect the meter in series with the circuit.
- Stop the simulation before changing connections or meter settings.

## 6. Key Learnings

1. Higher resistance generally means lower current at a constant voltage.
2. LED brightness generally decreases as current decreases.
3. A series resistor helps protect an LED from excessive current.
4. Voltage and current are different quantities.
5. Ohm's law relates the voltage across a resistor, its resistance, and the current through it.

## Completion Status

- Built an Arduino LED circuit
- Compared 220 Ω, 1 kΩ, and 10 kΩ
- Measured LED voltage
- Measured current
- Measured resistor voltage
- Passed the Lesson 02 checkpoint

**Status: Completed — practical and theory checkpoint passed.**