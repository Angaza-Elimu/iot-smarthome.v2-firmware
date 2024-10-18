
# DHTControl Library

The **DHTControl** library provides an easy interface for managing DHT sensors (DHT11, DHT22) in your projects. This library simplifies sensor setup, data reading, and control, making it easier to gather temperature and humidity data for your applications.

## Installation

Follow these steps to install the **DHTControl** library in your Arduino IDE:

### Step 1: Download the Library

- Download the zipped file of the **DHTControl** library from the repository.

### Step 2: Install the Library in Arduino IDE

1. Open Arduino IDE.
2. Navigate to `Sketch` -> `Include Library` -> `Add .ZIP Library...`
3. Select the downloaded `DHTControl.zip` file.
4. The library will now be available in your Arduino IDE.

Alternatively, you can manually copy the unzipped folder into the `libraries` directory in your Arduino IDE installation.

## Usage

### Basic Example

Here’s a simple example that demonstrates how to use the **DHTControl** library to read temperature and humidity data from a DHT11 or DHT22 sensor.

\`\`\`cpp
#include <DHTControl.h>

#define DHT_PIN 7          // Pin where the DHT sensor is connected
#define DHT_TYPE DHT22     // DHT11 or DHT22

DHTControl dhtSensor(DHT_PIN, DHT_TYPE);  // Initialize DHT sensor

void setup() {
  Serial.begin(9600);
  dhtSensor.begin();  // Start the sensor
}

void loop() {
  float temperature = dhtSensor.readTemperature();  // Read temperature
  float humidity = dhtSensor.readHumidity();        // Read humidity

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C  Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  delay(2000);  // Wait 2 seconds before the next reading
}
\`\`\`

### DHTControl Library API

Here are some common functions provided by the **DHTControl** library:

- **`DHTControl(int pin, int type)`**  
  Constructor to initialize the sensor with the specified pin and type (DHT11 or DHT22).

- **`void begin()`**  
  Initializes the DHT sensor. This function must be called in the `setup()`.

- **`float readTemperature()`**  
  Reads and returns the current temperature in Celsius. Returns `NAN` if reading fails.

- **`float readHumidity()`**  
  Reads and returns the current humidity in percentage. Returns `NAN` if reading fails.

- **`float computeHeatIndex(float temperature, float humidity)`**  
  Calculates the heat index (apparent temperature) based on the measured temperature and humidity.

### Example Sketch

After installing the library, you can access the example directly from the Arduino IDE:

- Go to `File` -> `Examples` -> `DHTControl` -> `DHTControlExample`

This will open an example sketch for using the **DHTControl** library.

## Manipulation

The **DHTControl** library supports both DHT11 and DHT22 sensors. You can easily switch between these two sensor types by changing the `DHT_TYPE` in your code to either `DHT11` or `DHT22` depending on your sensor.

Example:

\`\`\`cpp
#define DHT_TYPE DHT11  // Change to DHT22 for DHT22 sensors
\`\`\`

### Customize Read Interval

You can adjust the sensor reading interval by modifying the delay in the `loop()` function. The default example uses a 2-second interval:

\`\`\`cpp
delay(2000);  // Delay for 2 seconds between readings
\`\`\`

You can change this value based on your requirements, but it is recommended to allow a minimum of 2 seconds between readings for DHT11 sensors and 1 second for DHT22 sensors to ensure accurate data.

---

Feel free to open an issue or submit a pull request to enhance or report problems with the **DHTControl** library.

Happy Coding! 😊
