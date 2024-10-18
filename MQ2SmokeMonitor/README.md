# MQ2SmokeMonitor Library

**MQ2 Smoke Monitor for Arduino**

The `MQ2SmokeMonitor` library is designed to interface with the MQ-2 gas sensor, which can detect various gases including smoke. This library provides functions to read data from the sensor and interpret its readings, allowing for easy integration into Arduino projects for smoke detection.

## Features

- Easy-to-use interface for reading values from the MQ-2 gas sensor.
- Simple calibration procedure to ensure accurate readings.
- Threshold-based alerts for smoke detection.

## Installation

To install the `MQ2SmokeMonitor` library, follow these steps:

1. **Download the Library**  
   Clone or download the library from the GitHub repository:

   ```bash
   git clone https://github.com/your-username/MQ2SmokeMonitor.git


 Follow these steps to install the **MQ2SmokeMonitor** library in your Arduino IDE:

 ### Step 1: Download the Library

 - Download the zipped file of the **MQ2SmokeMonitor** library from the repository.

 ### Step 2: Install the Library in Arduino IDE

 1. Open Arduino IDE.
 2. Navigate to `Sketch` -> `Include Library` -> `Add .ZIP Library...`
 3. Select the downloaded `MQ2SmokeMonitor.zip` file.
 4. The library will now be available in your Arduino IDE.

 Alternatively, you can manually copy the unzipped folder into the `libraries` directory in your Arduino IDE installation.

## Usage

Here is a basic example of how to use the MQ2SmokeMonitor library in your Arduino sketches.

### Basic Example:

\`\`\`cpp
#include <MQ2SmokeMonitor.h>

// Create an instance of the MQ2SmokeMonitor class
MQ2SmokeMonitor mq2Sensor(A0); // Analog pin where the sensor is connected

void setup() { // initialize the serial port and the sensor
    Serial.begin(9600);
    mq2Sensor.begin();
}

void loop() {
    float smokeLevel = mq2Sensor.readSmokeLevel(); // Read smoke level

    Serial.print("Smoke Level: ");
    Serial.println(smokeLevel);

    // Check if smoke level exceeds threshold
    if (smokeLevel > THRESHOLD_VALUE) {
        Serial.println("Warning: Smoke Detected!");
        // Add your alerting mechanism here
    }

    delay(1000); // Wait for a second before the next reading
}

\`\`\`

## Sensor Connection

Connect the MQ-2 sensor to your Arduino as follows:

- **VCC** to 5V
- **GND** to GND
- **A0** to the analog output pin (as specified in the example)

## Calibration
Calibration is essential for accurate readings. Follow these steps:

- **Warm-up:** Allow the sensor to warm up for at least 24 hours before calibration.
- **Read baseline:** Take readings in clean air and note the baseline value.
- **Determine threshold:** Decide on a threshold value that indicates smoke presence based on your application needs.

## Usage and Manipulation
Use `monitorSmoke()` to get the current smoke level reading.
Adjust the threshold based on your calibration for accurate alerts.


---

Feel free to open an issue or submit a pull request to enhance or report problems with the **MQ2SmokeMonitor** library.

Happy Coding! 😊
