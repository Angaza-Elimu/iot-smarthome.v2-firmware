
# IntrusionDetection Library

The **IntrusionDetection** library is designed to help detect unauthorized movement or intrusion using a motion sensor like the PIR (Passive Infrared) sensor. It's a simple and efficient solution for creating motion detection systems in your Arduino projects.

## Installation

To install the **IntrusionDetection** library in your Arduino IDE, follow these steps:

1. **Download the Library**  
   Download the **IntrusionDetection** library as a ZIP file from the repository.

2. **Add the Library to Arduino IDE**  
   - Open Arduino IDE.
   - Go to `Sketch` -> `Include Library` -> `Add .ZIP Library...`.
   - Navigate to the downloaded ZIP file and select it.

Once added, the library will be available in your Arduino IDE for use.

## Usage

The **IntrusionDetection** library provides a simple API for detecting movement using a PIR sensor.

### Example Code

After installing the library, you can find a basic example in the Arduino IDE:

1. Go to `File` -> `Examples` -> `IntrusionDetection` -> `IntrusionDetectionExample`.
2. Open the example sketch to get started.

Below is an example of how to use the **IntrusionDetection** library:

```cpp
#include <IntrusionDetection.h>

// Define the PIR sensor pin
#define PIR_SENSOR_PIN 2

// Create an IntrusionDetection object
IntrusionDetection intrusion(PIR_SENSOR_PIN);

void setup() {
  Serial.begin(9600);
  intrusion.begin();  // Initialize the sensor
}

void loop() {
  if (intrusion.detectMovement()) {
    Serial.println("Intrusion detected!");
    // Add additional logic for alerting or reacting to the intrusion
  } else {
    Serial.println("No movement detected.");
  }
  delay(1000);  // Wait for 1 second before checking again
}
```

### Library Functions

- **`IntrusionDetection(int sensorPin)`**: Constructor to initialize the library with the given sensor pin.
- **`void begin()`**: Initializes the PIR sensor.
- **`bool detectMovement()`**: Checks for motion detection. Returns `true` if motion is detected, `false` otherwise.

## Manipulating the Library

You can customize how the **IntrusionDetection** library behaves by adjusting these elements:

1. **PIR Sensor Pin**: Modify the pin number in the constructor to match the digital pin connected to the PIR sensor.
2. **Adding Alerts**: You can easily add an alert mechanism such as a buzzer or LED by checking the motion detection and performing an action when motion is detected.

Example of adding a buzzer alert:

```cpp
#define BUZZER_PIN 5

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);  // Set the buzzer pin as output
  intrusion.begin();            // Initialize the PIR sensor
}

void loop() {
  if (intrusion.detectMovement()) {
    digitalWrite(BUZZER_PIN, HIGH);  // Turn on the buzzer
  } else {
    digitalWrite(BUZZER_PIN, LOW);   // Turn off the buzzer
  }
}
```

### Hardware Setup

- **PIR Sensor**:  
  - Connect the VCC and GND pins of the PIR sensor to the 5V and GND of your Arduino.
  - Connect the signal pin of the PIR sensor to the designated digital pin (e.g., pin 2).

- **Buzzer (optional)**:  
  - Connect one terminal of the buzzer to a digital pin (e.g., pin 5), and the other terminal to GND.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

---

With this library, you can easily integrate motion detection capabilities into your Arduino projects for security or automation purposes.
