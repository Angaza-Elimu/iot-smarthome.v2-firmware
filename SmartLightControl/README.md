# Angaza Elimu Smarthome - SmartLightControl Library

## Description

The **SmartLightControl** library is designed to control an LED light using Wi-Fi, enabling remote control based on platform-set values such as LED state, blink interval, and intensity. The library connects to a server via HTTPS to receive control parameters, which are then used to manipulate the LED's behavior. Below are the key features and class methods of the SmartLightControl library:

## Key Features:
  1. **Wi-Fi Connectivity:** Connects to a Wi-Fi network and a secure server using HTTPS to receive control parameters for the LED.
  2. **Remote Control via Server:** Communicates with a server to fetch control parameters such as LED state (ON/OFF), blink interval, and blink intensity.
  3. **Platform-Specific Controls:** LED behavior (such as blinking or toggling) is controlled through platform-set parameters that are fetched remotely.
  4. **Secure Communication:** Uses a secure Wi-Fi client (WiFiClientSecure) to communicate with the server using a root certificate for HTTPS communication.
  5. **Non-blocking Operations:** Implements a blink interval using the delay method, ensuring non-blocking operation while maintaining the LED's blinking behavior.

## Installation

### Install the Library in Arduino IDE

To install the `SmartLightControl` library, follow these steps:

1. **Download the Library**  
   Clone or download the library from the GitHub repository:

   ```bash
   git clone https://github.com/Angaza-Elimu/iot-smarthome.v2-firmware.git
  ```

  ### Step 2: Install the Library in Arduino IDE

  1. Open Arduino IDE.
  2. Navigate to `Sketch` -> `Include Library` -> `Add .ZIP Library...`
  3. Select the downloaded `SmartLightControl.zip` file.
  4. The library will now be available in your Arduino IDE.

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

   - Configure the sensor and other control modules connection from the `pin_configuration.h` file


## Library Class: SmartLightControl
This class is designed to encapsulate all the logic needed for smarthome smartlights controls and communication with a remote server.

  1. **Constructor:**
    ```cpp
    SmartLightControl(const char* ssid, const char* password, const char* serverUrl, const char* apiKey, const char* rootCaCert, int ledPin, int onboardLedPin);
    ```
    - Initializes Wi-Fi credentials, server details, API key, and pin configurations for both the LED and onboard LED.
    - Takes input for the server's URL, root certificate, and API key for secure communication, along with pin assignments for the LED, and onboard LED.

    **Parameters:**
      - `ssid`: Wi-Fi SSID (network name).
      - `password`: Wi-Fi password.
      - `serverUrl`: URL of the server where control data is fetched from.
      - `apiKey`: API key for the server.
      - `rootCaCert`: Root certificate for HTTPS communication.
      - `ledPin`: Pin number for controlling the external LED.
      - `onboardLedPin`: Pin number for the onboard LED (used for feedback during the connection process).

  2. **Methods:**
      1. **begin()**
          ```cpp
            void SmartLightControl::begin();
          ```
          - Initializes the Wi-Fi connection and sets up secure HTTPS communication with the server.
          - Displays connection status and IP address on the Serial Monitor.
          - Turns the onboard LED on or off depending on connection status.

      2. **update()**
          ```cpp
          void SmartLightControl::update();
          ```
          - Fetches the latest control parameters (LED state, blink interval, and blink intensity) from the server.
          - Controls the LED based on the received parameters:
            - Turns the LED ON or OFF based on the led_control_state fetched from the server.
            - If a blink interval is set, the LED will blink at the specified interval.
          - Logs the LED's status and control parameters to the Serial Monitor.

      3. **httpGETRequest(const char serverName)**
          ```cpp
          String SmartLightControl::httpGETRequest(const char* serverName);
          ```
          - Sends an HTTP POST request to the server with the API key as part of the request data.
          - Returns the server response, which contains the control parameters in JSON format.
          - Logs the HTTP response code and any errors encountered.

## Example Usage:
  The library could be used in an IoT-based home automation system where the LED light is remotely controlled using platform-based settings. The user can turn the LED ON or OFF, adjust its blink interval, and set blink intensity, all from a remote server. This allows for flexible and dynamic control based on environmental factors or user preferences.

## Typical Workflow:
  1. Call the `begin()` method to establish a secure Wi-Fi connection and set up the secure HTTPS client.
  2. Regularly call the `update()` method to check for the latest control parameters from the server and adjust the LED behavior accordingly.
  3. Use `httpGETRequest()` to fetch control parameters from the server in JSON format.

## Potential Use Cases:
   - **Home Automation:** Remotely control LED lights in a smart home environment based on server-set schedules or user input.
   - **Environmental Monitoring Systems:** Automatically adjust LED lighting conditions based on environmental sensor data fetched from a platform.
   - **Remote Management:** Allow administrators or users to remotely toggle or schedule lighting behavior in various systems.

   By integrating this library into an IoT-based project, the LED's behavior can be easily managed and adjusted remotely, providing flexibility and user control.

  ---

  Feel free to open an issue or submit a pull request to enhance or report problems with the **SmartLightControl** library.

  Happy Coding! 😊
