# Lesson 03: Pushbuttons, Digital Inputs & Debouncing

> # SketchNotes Available At : 
> https://www.tldraw.com/f/mp8TWOuJ5-_LH_xzlSmum?d=v0.0.1920.1012.-J7B2vNUF_G3J7OsTaVpC



## Objective

Learn how to read pushbutton inputs using an Arduino Uno, control an LED based on button presses, detect state changes, implement software debouncing, and count button presses using the Serial Monitor.

**Platform:** Tinkercad Circuits
**Board:** Arduino Uno
**Components:** Pushbutton, LED, 220Ω resistor, 10kΩ resistor (for the external pull-down experiment), breadboard, jumper wires.

## 1. Digital Inputs and Pushbuttons

A digital input allows an Arduino to read one of two logical states:

- `HIGH` — logic 1
- `LOW` — logic 0

The `digitalRead()` function reads the current logic state of a digital pin.

```
int buttonState = digitalRead(BUTTON);
```

The returned value can be used to make decisions in the program.

### Button Wiring

An external pull-down circuit uses a 10kΩ resistor to hold the input LOW while the button is released. When pressed, the button connects the input to 5V, making the reading HIGH.

## 2. Understanding `INPUT_PULLUP`

The Arduino Uno has an internal pull-up resistor that can be enabled using:

```
pinMode(BUTTON, INPUT_PULLUP);
```

This avoids the need for an external pull-up resistor.

With this configuration:

| Button condition | Input reading |
| ---------------- | ------------- |
| Released         | `HIGH`        |
| Pressed          | `LOW`         |

When released, the internal pull-up resistor holds the input HIGH. Pressing the button connects the input to GND, causing it to read LOW.

**Important:** `INPUT_PULLUP` reverses the usual button logic. A pressed button reads LOW, not HIGH.

### Example: LED follows the button

```
#define BUTTON 2
#define LED 13

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(BUTTON);

  if (buttonState == LOW) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}
```

In this example, the LED turns ON while the button is pressed and OFF when it is released.

## 3. Toggling an LED

Instead of making the LED follow the button, we can toggle its state.

- First press: LED turns ON.
- Second press: LED turns OFF.
- Third press: LED turns ON again.

### Important variables

```
int ledState = LOW;
int lastButtonState = HIGH;
```

- `ledState` stores the desired LED state.
- `lastButtonState` remembers the previous button reading.

### Toggle operator

```
ledState = !ledState;
```

The `!` operator reverses the logical state:

| Previous state | New state |
| -------------- | --------- |
| `LOW`          | `HIGH`    |
| `HIGH`         | `LOW`     |

### Detecting a new press

```
if (lastButtonState == HIGH && buttonState == LOW) {
  ledState = !ledState;
  digitalWrite(LED, ledState);
  delay(50);
}

lastButtonState = buttonState;
```

The condition detects a transition from HIGH to LOW, called a **falling edge**.

The `&&` operator means both conditions must be true.

The assignment:

```
lastButtonState = buttonState;
```

copies the current reading into the variable that will be used for comparison in the next loop iteration.

Because `loop()` runs continuously, the Arduino can keep checking the button without requiring a new press to start the loop.

## 4. Button Contact Bounce

Mechanical pushbuttons may produce several rapid electrical transitions when pressed or released. This is called **contact bounce**.

One physical press may briefly produce multiple HIGH and LOW readings. If these transitions are interpreted as separate presses, the LED may toggle more than once.

A simple delay can help:

```
delay(50);
```

However, this pauses the program for 50 milliseconds and does not constitute a complete debouncing algorithm.

## 5. Software Debouncing Using `millis()`

A more deliberate approach checks whether a button reading has remained stable for a specified period.

### Complete debounced LED-toggle code

```
#define BUTTON 2
#define LED 13

int ledState = LOW;

int lastButtonState = HIGH;
int currentButtonState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  digitalWrite(LED, ledState);
}

void loop() {
  int reading = digitalRead(BUTTON);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
    lastButtonState = reading;
  }

  if (millis() - lastDebounceTime >= debounceDelay) {
    if (reading != currentButtonState) {
      currentButtonState = reading;

      if (currentButtonState == LOW) {
        ledState = !ledState;
        digitalWrite(LED, ledState);
      }
    }
  }
}
```

### Understanding the variables

| Variable             | Purpose                                           |
| -------------------- | ------------------------------------------------- |
| `reading`            | Current raw button reading                        |
| `lastButtonState`    | Previous raw button reading                       |
| `currentButtonState` | Last accepted stable state                        |
| `lastDebounceTime`   | Time of the most recent raw reading change        |
| `debounceDelay`      | Required stability period, set to 50 milliseconds |
| `ledState`           | Current LED state                                 |

### How it works

1. Read the button's current state.
2. If the raw reading changes, record the current time.
3. Check whether at least 50 milliseconds have elapsed since the last change.
4. If the reading is stable and differs from the last accepted state, update that state.
5. If the accepted state is LOW, toggle the LED.
6. Repeat the loop.

### Why use `millis()` instead of `delay()`?

`millis()` allows the program to check elapsed time without deliberately blocking execution for the entire debounce period.

**Note:** This is a simple software debouncing method. More complex applications may require additional handling, but this is a useful starting point.

## 6. Smart Button Counter

The final practical challenge extends the debounced LED-toggle circuit by counting valid button presses.

### Additional code

Declare the counter:

```
int pressCount = 0;
```

Initialize serial communication inside `setup()`:

```
Serial.begin(9600);
```

Inside the accepted-press condition, add:

```
pressCount++;

Serial.print("Button presses: ");
Serial.println(pressCount);
```

### Complete Smart Button Counter code

```
#define BUTTON 2
#define LED 13

int ledState = LOW;
int pressCount = 0;

int lastButtonState = HIGH;
int currentButtonState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  digitalWrite(LED, ledState);

  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(BUTTON);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
    lastButtonState = reading;
  }

  if (millis() - lastDebounceTime >= debounceDelay) {
    if (reading != currentButtonState) {
      currentButtonState = reading;

      if (currentButtonState == LOW) {
        ledState = !ledState;
        digitalWrite(LED, ledState);

        pressCount++;

        Serial.print("Button presses: ");
        Serial.println(pressCount);
      }
    }
  }
}
```

### Expected behaviour

| Event              | LED  | Counter |
| ------------------ | ---- | ------- |
| Arduino starts     | OFF  | 0       |
| First valid press  | ON   | 1       |
| Second valid press | OFF  | 2       |
| Third valid press  | ON   | 3       |

The Serial Monitor must be configured to **9600 baud** to match `Serial.begin(9600)`.

The counter is stored in RAM, so it resets when the Arduino restarts.

## 7. Key Concepts Learned

- Digital inputs and outputs
- `digitalRead()` and `digitalWrite()`
- `INPUT_PULLUP` and inverted button logic
- Pull-up and pull-down resistors
- Boolean state variables
- The logical NOT (`!`) and AND (`&&`) operators
- Edge detection and previous-state tracking
- Continuous execution of `loop()`
- Mechanical contact bounce
- Software debouncing with `millis()`
- Serial communication and output
- Variables and incrementing counters

## 8. Practical Checkpoint

- Read a pushbutton using Arduino digital input.
- Control an LED using button state.
- Use `INPUT_PULLUP` and understand reversed logic.
- Toggle an LED with successive button presses.
- Understand edge detection and state tracking.
- Implement software debouncing.
- Count button presses using the Serial Monitor.

## Conclusion

In this lesson, I built a button-controlled LED circuit in Tinkercad, implemented LED toggling with edge detection, improved reliability through software debouncing, and extended the project into a Smart Button Counter.

This lesson introduced the transition from simple digital input/output operations to stateful embedded programming.