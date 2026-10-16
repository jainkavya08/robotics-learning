# Lesson 05 — Servo Motors and Ultrasonic Distance Scanning

> # SketchNotes Available At : 
> https://www.tldraw.com/f/mp8TWOuJ5-_LH_xzlSmum?d=v81.4592.2137.1792.cB1jNb205d9Bh55xDD6EQ

## 1. Objective

To understand servo motors, control their position using Arduino, measure distance using an ultrasonic sensor, and combine both components to create a simple obstacle-detection scanner in Tinkercad Circuits.

## 2. Components Used

- Arduino Uno
- Servo motor (such as an SG90)
- HC-SR04 ultrasonic distance sensor
- Potentiometer
- Breadboard and jumper wires
- Tinkercad Circuits for simulation

## 3. What Is a Servo Motor?

A servo motor is an actuator that moves to a commanded position, commonly an angle.

Unlike a continuously rotating DC motor, a standard positional servo is designed to move its output shaft to a requested position within its operating range.

**Applications:**

- Robotic arms and grippers
- Pan-and-tilt camera systems
- Sensor-scanning mechanisms
- Steering mechanisms in small robots

## 4. Servo Motor Wiring

| Servo wire                     | Arduino connection |
| ------------------------------ | ------------------ |
| Signal (usually orange/yellow) | Digital pin 9      |
| Power (usually red)            | 5V                 |
| Ground (usually brown/black)   | GND                |

Wire colors can vary by servo model, so check its documentation.

## 5. Controlling a Servo with Arduino

```
#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);
  myServo.write(90);
}

void loop() {
}
```

### Explanation

- `#include <Servo.h>` includes the Servo library.
- `Servo myServo;` creates a servo control object.
- `myServo.attach(9);` associates the servo signal with pin 9.
- `myServo.write(90);` requests a position of approximately 90 degrees.
- `setup()` runs once when the program starts.
- `loop()` repeats continuously, but it contains no instructions in this example.

### How Servo Control Works

The Arduino sends repeated timed control pulses to the servo. The pulse width represents the requested position. A common control frame is around 20 milliseconds, with pulse widths often near 1–2 milliseconds, although the exact range varies by servo.

The signal wire carries control information; the power wire supplies the energy needed to operate the motor.

## 6. Automatic Servo Sweep

The next experiment moves the servo gradually from one end to the other and back.

```
#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);
}

void loop() {
  for (int angle = 0; angle <= 180; angle += 1) {
    myServo.write(angle);
    delay(15);
  }

  for (int angle = 180; angle >= 0; angle -= 1) {
    myServo.write(angle);
    delay(15);
  }
}
```

### Important concepts

- A `for` loop repeats instructions over a range of values.
- `angle += 1` increases the requested position by one degree per iteration.
- `angle -= 1` decreases it by one degree per iteration.
- `delay(15)` provides time between position commands.

The servo needs time to physically move. Sending a new position command does not mean the shaft instantly reaches that position.

## 7. Potentiometer-Controlled Servo

A potentiometer provides a variable analog voltage that Arduino can read.

### Wiring

| Potentiometer terminal  | Connection |
| ----------------------- | ---------- |
| Outer terminal 1        | 5V         |
| Outer terminal 2        | GND        |
| Middle terminal (wiper) | A0         |

Keep the servo connected to signal pin 9, 5V, and GND.

### Code

```
#include <Servo.h>

Servo myServo;
const int POT_PIN = A0;

void setup() {
  myServo.attach(9);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(POT_PIN);
  int angle = map(potValue, 0, 1023, 0, 180);

  myServo.write(angle);

  Serial.print("Potentiometer: ");
  Serial.print(potValue);
  Serial.print(" | Angle: ");
  Serial.println(angle);

  delay(15);
}
```

### Concepts learned

- `analogRead(A0)` returns a value from 0 to 1023 on the standard Arduino Uno.
- `map()` converts the reading into an angle from 0 to 180.
- The servo position changes as the potentiometer is rotated.
- A reading near 512 maps to approximately 90 degrees.

## 8. Introduction to Ultrasonic Distance Measurement

The HC-SR04 estimates distance by transmitting an ultrasonic sound pulse and measuring the time taken for its echo to return.

### Wiring

| HC-SR04 pin | Arduino Uno |
| ----------- | ----------- |
| VCC         | 5V          |
| GND         | GND         |
| TRIG        | D7          |
| ECHO        | D6          |

### Measurement sequence

1. Set TRIG LOW briefly.
2. Set TRIG HIGH for approximately 10 microseconds.
3. Set TRIG LOW again.
4. Measure the duration of the ECHO signal.
5. Calculate distance from the measured time.

```
const int TRIG_PIN = 7;
const int ECHO_PIN = 6;

float measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration =
      pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return -1;
  }

  return duration * 0.0343 / 2.0;
}
```

### Distance formula

Distance is calculated by:

**Distance = (Time × Speed of Sound) / 2**

The division by two is necessary because sound travels to the object and then returns to the sensor.

- `duration` is the measured echo pulse duration in microseconds.
- `30000` is the timeout in microseconds, equivalent to 30 milliseconds.
- If `pulseIn()` does not detect a suitable pulse before the timeout, it returns zero.
- Returning `-1` marks an unsuccessful measurement rather than a valid distance.

## 9. Combining the Servo and Ultrasonic Sensor

The servo rotates the ultrasonic sensor through different angles. At each angle, Arduino requests a distance measurement.

### Scanner logic

1. Command the servo to an angle.
2. Allow the servo time to move.
3. Trigger the ultrasonic sensor.
4. Calculate the distance.
5. Check whether an obstacle is within the threshold.
6. Stop the scan if the obstacle is detected.
7. Otherwise, continue scanning.

Example threshold condition:

```
if (distance > 0 && distance < 20) {
  // Obstacle detected within 20 cm
}
```

The condition `distance > 0` excludes failed measurements represented by `-1`.

### Understanding the scanning loop

```
for (int angle = 0; angle <= 180; angle += 30) {
  myServo.write(angle);
  delay(300);

  float distance = measureDistance();
}
```

This visits the angles 0°, 30°, 60°, 90°, 120°, 150°, and 180°. The delay gives the servo time to move before the measurement.

A complete back-and-forth scanner needs a second loop that decreases the angle.

**Important:** If the program enters `while (true)` after detecting an obstacle, it stays there indefinitely unless the code provides an exit condition. To resume scanning automatically, the program must keep checking the distance and leave the stopped state when the obstacle moves away.

## 10. Robotics System Architecture

A simple robotic sensing system contains three important roles:

- **Sensor:** Measures the environment. Here, the HC-SR04 measures distance.
- **Controller:** Processes measurements and makes decisions. Here, the Arduino Uno executes the program.
- **Actuator:** Produces movement. Here, the servo changes the sensor's direction.

The system follows this cycle:

**Sense → Process → Decide → Act → Repeat**

In a mobile robot, a motor driver may also be needed to control wheel motors. The current scanner only controls a servo; it does not drive a robot car.

## 11. Challenges and Troubleshooting

| Problem                                       | Possible explanation                                         |
| --------------------------------------------- | ------------------------------------------------------------ |
| Servo does not move                           | Check signal pin, power, ground, and `attach()` pin          |
| Servo moves but sensor readings are wrong     | Check TRIG/ECHO wiring and the measurement code              |
| Distance shows an invalid result              | The echo may have timed out or the object may not be detected |
| Scanner moves too quickly                     | Increase the settling delay                                  |
| Scanner stops permanently                     | Check for an infinite loop without an exit condition         |
| Servo does not cover the full requested range | Physical servo limits may differ from the commanded 0–180° range |

In physical hardware, check the servo's current requirements and use an appropriate power supply if needed. Arduino, servo, and sensor grounds must share a common reference.

## 12. Key Learnings

By completing Lesson 05, I learned how to:

- Control servo position using the Arduino Servo library.
- Generate a gradual servo sweep.
- Map potentiometer readings to servo angles.
- Measure distance using an ultrasonic sensor.
- Use measured distance in conditional logic.
- Combine a sensor, controller, and actuator into a scanning system.
- Recognize the difference between commanding movement and allowing time for the hardware to respond.

## 13. Next Steps

- Improve the scanner so it resumes after an obstacle moves away.
- Display angle and distance readings clearly in the Serial Monitor.
- Explore how scanning data could guide a robot's movement.
- Later, integrate additional sensors and motor control into a more complete robotics project.