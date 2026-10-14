# Lesson 04: PWM and Analog Input

> # SketchNotes Available At : 
> https://www.tldraw.com/f/mp8TWOuJ5-_LH_xzlSmum?d=v371.4270.2302.1213.FbROZjU9OnQ1xxyko3B4C

## Objective

Learn how to control LED brightness using PWM, read analog inputs from a potentiometer, convert input ranges, and make decisions using conditional statements.

## Hardware and Simulation

- Arduino Uno
- Potentiometer
- LED
- 220 Ω resistor
- Breadboard and jumper wires
- Tinkercad Circuits

## Circuit Connections

### LED

- LED anode (long leg) → Arduino pin 9
- LED cathode (short leg) → 220 Ω resistor
- Other end of resistor → GND

### Potentiometer

- One outer terminal → 5V
- Other outer terminal → GND
- Middle terminal (wiper) → A0

**Note:** Pin 9 supports PWM on the Arduino Uno.

## Part 1: Controlling LED Brightness with PWM

PWM stands for Pulse Width Modulation. It rapidly switches a digital output between HIGH and LOW to control the effective power delivered to a load.

```
#define LED 9

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  analogWrite(LED, 128);
}
```

### Observations

Tested PWM values of 0, 64, 128, 192, and 255.

| PWM value | Approximate duty cycle | Observation        |
| --------- | ---------------------- | ------------------ |
| 0         | 0%                     | LED off            |
| 64        | 25%                    | Low brightness     |
| 128       | 50%                    | Medium brightness  |
| 192       | 75%                    | Higher brightness  |
| 255       | 100%                   | Maximum brightness |

The perceived brightness may not increase linearly with the PWM value.

## Part 2: Understanding Analog Input

The Arduino Uno's `analogRead()` function reads an analog voltage and returns an integer from 0 to 1023.

```
int potValue = analogRead(A0);
```

- Reading near 0: voltage near 0V.
- Reading near 512: voltage approximately halfway between 0V and 5V.
- Reading near 1023: voltage near 5V.

These voltage relationships assume the default 5V analog reference.

## Part 3: Potentiometer-Controlled Brightness

```
#define LED 9
#define POT A0

int potValue = 0;
int brightness = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  potValue = analogRead(POT);
  brightness = map(potValue, 0, 1023, 0, 255);

  analogWrite(LED, brightness);

  Serial.print("Potentiometer: ");
  Serial.print(potValue);
  Serial.print(" | Brightness: ");
  Serial.println(brightness);

  delay(100);
}
```

### How it works

1. `analogRead(A0)` reads the potentiometer.
2. `map()` converts the reading from the range 0–1023 to 0–255.
3. `analogWrite()` uses the converted value to control LED brightness.
4. The Serial Monitor displays the input and output values.

## Part 4: Mapping and Range Conversion

The `map()` function converts a number from one range to another.

```
brightness = map(potValue, 0, 1023, 50, 200);
```

This maps the potentiometer reading to an output range of 50–200.

| Potentiometer reading | Approximate mapped value |
| --------------------- | ------------------------ |
| 0                     | 50                       |
| 256                   | 87                       |
| 512                   | 125                      |
| 768                   | 162                      |
| 1023                  | 200                      |

Arduino's `map()` uses integer arithmetic and truncates fractional results.

### Alternative: Division

```
brightness = potValue / 4;
```

This is a simple approximation for converting an Arduino Uno analog reading to a PWM value. It works for this conversion because the input range is approximately four times the output range.

## Part 5: Conditional Logic and Thresholds

A sensor threshold allows the Arduino to make a decision based on an input reading.

```
if (potValue >= 512) {
  digitalWrite(LED, HIGH);
} else {
  digitalWrite(LED, LOW);
}
```

- If the reading is 512 or greater, the LED turns ON.
- If the reading is below 512, the LED turns OFF.

This demonstrates how sensor readings can trigger actions.

## Part 6: Three-Level Brightness Controller

```
if (potValue < 300) {
  brightness = 0;
} else if (potValue < 700) {
  brightness = 128;
} else {
  brightness = 255;
}
```

The LED switches between OFF, medium brightness, and maximum brightness according to the potentiometer reading.

## Part 7: Final Challenge — Smart Sensor Indicator

### Requirements

| Input range | PWM value | LED behavior       |
| ----------- | --------- | ------------------ |
| 0–249       | 0         | OFF                |
| 250–499     | 64        | Low brightness     |
| 500–749     | 160       | Higher brightness  |
| 750–1023    | 255       | Maximum brightness |

### Final working code

```
#define LED 9
#define POT A0

int potValue = 0;
int brightness = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  potValue = analogRead(POT);

  if (potValue < 250) {
    brightness = 0;
  } else if (potValue < 500) {
    brightness = 64;
  } else if (potValue < 750) {
    brightness = 160;
  } else {
    brightness = 255;
  }

  analogWrite(LED, brightness);

  Serial.print("Sensor: ");
  Serial.print(potValue);
  Serial.print(" | Brightness: ");
  Serial.println(brightness);

  delay(100);
}
```

### Observations

- The potentiometer reading changes as the knob rotates.
- The LED responds to the four input ranges.
- The Serial Monitor displays both the sensor reading and PWM command.
- The brightness changes in steps rather than gradually.

## Key Concepts Learned

| Concept         | Purpose                                                    |
| --------------- | ---------------------------------------------------------- |
| `analogRead()`  | Reads analog input, 0–1023 on the Uno                      |
| `analogWrite()` | Controls PWM output, 0–255 on PWM-capable pins             |
| PWM             | Controls effective output power using duty cycle           |
| `map()`         | Converts values between numerical ranges                   |
| `if`            | Executes code when a condition is true                     |
| `else if`       | Checks another condition when earlier conditions are false |
| `else`          | Handles the remaining cases                                |
| Serial Monitor  | Displays readings and debugging information                |

## Robotics Applications

These concepts form the foundation for:

- Light-sensitive systems
- Motor speed control
- Sensor-based indicators
- Obstacle detection logic
- Threshold-based automation

In a real robot, a potentiometer can be replaced by a suitable sensor, such as a light sensor or distance sensor. The controller can then use its readings to decide what action to take.

## Lesson 04 Summary

I learned to control LED brightness using PWM, read analog inputs through a potentiometer, convert input ranges using `map()`, and implement threshold-based decisions using conditional logic. I also built a four-level LED indicator and observed its behavior in Tinkercad.

**Status:** Lesson 04 practical challenge completed.