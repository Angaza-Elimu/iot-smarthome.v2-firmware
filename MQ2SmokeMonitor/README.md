# Angaza Elimu Smarthome - MQ2SmokeMonitor Library

The **MQ2SmokeMonitor** library provides functionality for monitoring smoke levels using the MQ2 gas sensor and sounding an alarm when smoke surpasses a defined threshold. It also supports secure communication with a server, allowing real-time data transmission and threshold updates.

## Key Features

  - **WiFi Connectivity:** Automatically connects to a specified WiFi network.
  - **Secure Communication:** Communicates with a server using HTTPS for secure data transmission.
  - **Alarm System:** A buzzer sounds when the detected smoke levels exceed the threshold.
  - **Server Integration:** Retrieves the smoke threshold from the server and sends smoke values.
  - **Flexible Pin Configurations:** Supports custom pin configurations for gas sensor, LED, and buzzer.


## Installation

 Follow these steps to install the **MQ2SmokeMonitor** library in your Arduino IDE:

### Step 1: Clone the Repository
    Clone the `iot-smarthome.v2-firmware` repository from GitHub:
    ```bash
    git clone https://github.com/Angaza-Elimu/iot-smarthome.v2-firmware.git
    ```
    - With this approach, the whole repository files will be available on your local machine.

### Step 2: Download the Library

 - Download the zipped file of the **MQ2SmokeMonitor** library from the repository.

### Step 3: Install the Library in Arduino IDE

 1. Open Arduino IDE.
 2. Navigate to `Sketch` -> `Include Library` -> `Add .ZIP Library...`
 3. Select the downloaded `MQ2SmokeMonitor.zip` file.
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

   ---

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


## Library Class: MQ2SmokeMonitor
This class is designed to encapsulate all the logic needed for smoke detection, alarm triggering, and communication with a remote server.

**Constructor:**
  ```cpp
  MQ2SmokeMonitor(const char* server_url, const char* root_cacert, const char* api_key, int onboardLedPin, int buzzerPin, int gasSensorPin);
  ```
  **Parameters:**
    - **server_url:** The URL to which smoke data is posted.
    - **root_cacert:** The root certificate for secure communication (HTTPS).
    - **api_key:** The API key for authenticating with the server.
    - **onboardLedPin:** Pin connected to the onboard LED for status indication.
    - **buzzerPin:** Pin connected to the buzzer for sounding the alarm.
    - **gasSensorPin:** Pin connected to the MQ2 sensor for reading smoke levels.

    **Methods:**
      1. **begin(const char ssid, const char password)**
          - This method initializes the hardware components and connects the device to the WiFi network.
            - It sets up the onboard LED and connects the buzzer to the PWM channel for tone control.
            - It also establishes a secure HTTPS connection using the provided root certificate.

              ```cpp
                void MQ2SmokeMonitor::begin(const char* ssid, const char* password);
              ```
        2. **monitorSmoke()**
           - This function continuously reads smoke values from the MQ2 sensor and compares them with the threshold received from the server.
              - If the smoke level exceeds the threshold, the buzzer will sound an alarm.
              - A secure HTTPS request is sent to retrieve the current smoke threshold from the server.
                ```cpp
                void MQ2SmokeMonitor::monitorSmoke();
                ```

        3. **handleSmokeDetection()**
           - This method compares the current smoke sensor value with the predefined threshold and  triggers the buzzer alarm if the threshold is surpassed.
              - The buzzer alternates between two different frequencies (800 Hz and 1000 Hz) as an alert.
                ```cpp
                void MQ2SmokeMonitor::handleSmokeDetection();
                ```

        4. **httpGETRequest(const char serverName)**
            - This function sends a POST request to the server, including the smoke sensor's API key and the current smoke level. It retrieves the server response containing the smoke threshold in JSON format.
              - If the POST request is successful (HTTP 200 response), it returns the server's response as a string.
                ```cpp
                String MQ2SmokeMonitor::httpGETRequest(const char* serverName);
                ```

  The **MQ2SmokeMonitor** library offers a complete and flexible smoke detection solution with secure server communication and real-time alarm triggering.

  ---

  Feel free to open an issue or submit a pull request to enhance or report problems with the **MQ2SmokeMonitor** library.

  Happy Coding! 😊
