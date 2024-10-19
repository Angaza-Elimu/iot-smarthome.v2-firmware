
# Angaza Elimu Smarthome - DHTControl Library

The **DHTControl** library provides functionality for monitoring temperature and humidity using a DHT sensor. It supports sending recorded data to a remote platform and controlling a fan based on temperature thresholds set remotely. Additionally, it displays the current readings on an OLED screen for real-time monitoring.

## Features:

- Reads temperature and humidity values from a DHT sensor.
- Displays data on an OLED screen.
- Sends sensor data to a remote platform via HTTPS.
- Controls a fan based on temperature thresholds set remotely.
- Supports both ESP32-based microcontroller architectures.

## Installation

Follow these steps to install the **DHTControl** library in your Arduino IDE:


### Step 1: Clone the Repository

   Clone the `iot-smarthome.v2-firmware` repository from GitHub:
   
   ```bash
   git clone https://github.com/Angaza-Elimu/iot-smarthome.v2-firmware.git
   ```
   - With this approach, the whole repository files will be available on your local machine.

### Step 2: Download the Library

- Download the zipped file of the **DHTControl** library from the repository.

### Step 3: Install the Library in Arduino IDE

1. Open Arduino IDE.
2. Navigate to `Sketch` -> `Include Library` -> `Add .ZIP Library...`
3. Select the downloaded `DHTControl.zip` file.
4. The library will now be available in your Arduino IDE.

Alternatively, you can manually copy the unzipped folder into the `libraries` directory in your Arduino IDE installation.

## Usage

Access Example Files
   - After the sensor library is installed, a basic `.ino` example file will be available for testing and getting started.
   - To access the example file:
     - Go to `File` -> `Examples` -> `Installed_Library_Name`
     - Open the example `.ino` file.
   - Load the example sketch, modify the necessary parameters:
      - Sensor `pins` under `pin_configuration.h` file,
      - `WiFi credentials` and `API Key` under `secrets.h` file, and upload it to your ESP32 board.

   - Alternatively, you can navigate directly to the `examples` folder in each sensor library directory within the GitHub repository.

### NOTE
  - Every `.ino` file has a `cert.h` file attached.
    - This holds server certificate for secure connection - `DO NOT` edit it

### Additional Notes

  - **WiFi Configuration**: Ensure that you have configured the correct `ssid` and `password` values in your firmware for WiFi connectivity.
  - **Secure Communication**: This firmware supports secure HTTP communication. Make sure NOT to tamper with the provided root certificate for secure connections when required.
  - **Platform connection**: For successful platform connection, ensure to provide a valid project `API Key`(generated after new project creation).

## Sensor Connection

   - Configure the sensor and other control modules connection from the `pin_configuration.h` file

  ---

## Key Class Methods

  1. **Constructor:** `DHTControl()`

    ```cpp
    DHTControl(const char* ssid, const char* password, const char* serverUrl, const char* rootCert, const String& apiKey, int dhtPin, uint8_t dhtSensorType, uint8_t dispScreenW, uint8_t dispScreenH, int inaPin, int inbPin, int oledSda, int oledScl, int onboardLedPin);
    ```
    - **Purpose:** Initializes the DHTControl object with all the necessary parameters like WiFi credentials, server URL, SSL certificate, API key, and hardware pin configurations.
    - **Parameters:**
      - `ssid, password:` WiFi network credentials.
      - `serverUrl:` The URL of the remote platform for sending data and fetching threshold values.
      - `rootCert:` SSL certificate for secure HTTPS communication.
      - `apiKey:` API key for server authentication.
      - `dhtPin:` The pin connected to the DHT sensor.
      - `dhtSensorType:` The type of DHT sensor used (e.g., DHT22).
      - `dispScreenW, dispScreenH:` OLED screen width and height.
      - `inaPin, inbPin:` Pins for controlling the fan.
      - `oledSda, oledScl:` I2C pins for the OLED display.
      - `onboardLedPin:` Pin for controlling an onboard LED.
    - `Usage:` Creates an instance of the library with all the required settings to start data monitoring and fan control.

  3. `begin()`
      ```cpp
        void begin();
      ```
      - **Purpose:** Initializes WiFi connectivity, configures the OLED display, and sets up pin modes for the fan control and the onboard LED.
      - **Behavior:**
        - Starts a serial connection to print debug information.
        - Initializes the OLED display with custom I2C pins.
        - Connects the device to a specified WiFi network and prints the IP address.
        - Sets the SSL certificate for secure HTTPS communication.
      - **Usage:** This method must be called in the setup() function of the Arduino sketch to ensure the system initializes correctly before any sensor monitoring occurs.

  4. `monitorDHTSensor()`
      ```cpp
        void monitorDHTSensor();
      ```
      - **Purpose:** Monitors the DHT sensor, reads temperature and humidity values, and sends the data to a remote platform. It also retrieves temperature thresholds from the server and controls the fan based on the sensor data.
      - **Behavior:**
        - Reads the temperature and humidity values from the DHT sensor.
        - Sends the sensor data to the server via a POST request.
        - Retrieves the temperature and humidity thresholds set remotely via a GET request.
        - Compares the current temperature to the threshold and starts/stops the fan accordingly.
        - Updates the OLED display with the latest temperature and humidity readings.
      - **Usage:** This method is typically called in the loop() function, continuously monitoring the sensor data and adjusting the fan and display as needed.

  5. `monitorDHTSensor()`
      ```cpp
        string httpGETRequest(const char* serverName);
      ```
        - **Purpose:** Sends an HTTP POST request to the remote server with the sensor data (temperature and humidity) and receives the server response, which contains the temperature and humidity thresholds.
        - **Parameters:**
        serverName: The URL of the server that receives the POST request.
        - **Behavior:**
          - Posts sensor data to the server and retrieves the JSON response that contains threshold values.
          - Checks the HTTP response code to ensure data was sent successfully.
          - Returns the server's response (usually a JSON string) that can be parsed for threshold values.
        - **Usage:** This method is called internally within monitorDHTSensor() to handle data exchange with the remote platform.


### Method Flow and Manipulation
  - **Initialization (begin()):** Ensures WiFi connection and hardware setup, preparing the system for operation.
  - **Sensor Monitoring (monitorDHTSensor()):** Continuously monitors the sensor data, updates the display, and interacts with the server to control the fan.
  - **Data Exchange (httpGETRequest()):** Manages the data transmission between the device and the server, ensuring thresholds are dynamically updated.

  ---

  Feel free to open an issue or submit a pull request to enhance or report problems with the **DHTControl** library.

  Happy Coding! 😊
