# Angaza Elimu Smarthome - SmartWindowControl Library

## Description

The **SmartWindowControl** library provides functionality for automating smart window systems based on environmental sensor data (rain and water level) and user-defined timers. It allows for the control of window position (open or closed) by interacting with a rain sensor and sending data to a server for cloud-based monitoring and control.

This library is designed to work with ESP32 devices, leveraging its WiFi capabilities to connect to your IoT platform and control RGB LEDs based on server data.

## Key Features

  1. **WiFi & Secure Communication:**
    - The library supports secure communication using HTTPS and connects to a remote server using WiFi.
  It uses a root certificate to establish a secure connection for sending sensor data and receiving control signals.
  2. **Rain & Water Level Monitoring:**
    - It reads values from a rain sensor and a water level sensor, and based on the received values and thresholds, decides whether to open or close the window.
  3. **Window Control with Servo:**
    - The library uses a servo motor to physically control the window’s position. The motor opens or closes the window incrementally, ensuring smooth movement.
  4. **Server-based Control:**
    - Sensor values are sent to a server, and the window control logic is partly driven by server-side parameters like rain threshold and window state.
  5. **LED Feedback:**
    - The onboard LED provides feedback to indicate the connection status and system activity (e.g., blinking during WiFi connection).
  6. **Timer and Delays:**
    - The control system includes timed delays to ensure stable operations and smooth transitions between window positions.

## Installation

  Follow these steps to install the **SmartWindowControl** library in your Arduino IDE:

  ### Step 1: Clone the Repository
      Clone the `iot-smarthome.v2-firmware` repository from GitHub:
      
      ```bash
      git clone https://github.com/Angaza-Elimu/iot-smarthome.v2-firmware.git
      ```
      
      - With this approach, the whole repository files will be available on your local machine.

  ### Step 2: Download the Library

   - Download the zipped file of the **SmartWindowControl** library from the repository.

  ### Step 3: Install the Library in Arduino IDE

   1. Open Arduino IDE.
   2. Navigate to `Sketch` -> `Include Library` -> `Add .ZIP Library...`
   3. Select the downloaded `SmartWindowControl.zip` file.
   4. The library will now be available in your Arduino IDE.

   - Alternatively, you can manually copy the unzipped folder into the `libraries` directory in your Arduino IDE installation.


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


## Library Class: SmartWindowControl
This class is designed to encapsulate all the logic needed for smarthome window controls and communication with a remote server.

**Constructor:**

  ```cpp
  SmartWindowControl(const char* ssid, const char* password, const char* server_url, const char* root_cacert, const char* api_key, int servoPin, int waterLevelPin, int onboardLedPin);
  ```
  
  - Initializes the SmartWindowControl object with WiFi credentials, server details, and pin assignments.
  - Takes input for the server's URL, root certificate, and API key for secure communication, along with pin assignments for the servo, water sensor, and onboard LED.

  **Parameters:**
    - **server_url:** The URL to which smoke data is posted.
    - **root_cacert:** The root certificate for secure communication (HTTPS).
    - **api_key:** The API key for authenticating with the server.
    - **onboardLedPin:** Pin connected to the onboard LED for status indication.
    - **waterLevelPin:** Pin connected to the rain sensor for reading moisture levels.

    **Methods:**
      1. **begin()**
      
              ```cpp
                void SmartWindowControl::begin();
              ```
              
              - Initializes the servo motor for controlling the window, sets up the rain and water sensors, and connects the system to the specified WiFi network.
              - It also sets up secure communication with the server using the root certificate for HTTPS.

        2. **controlWindow()**
        
                ```cpp
                void SmartWindowControl::controlWindow();
                ```
                
                - Reads the water level sensor and requests rain sensor data from the server. Based on the sensor readings and thresholds, this method controls whether the window should open or close.
                - It moves the servo to adjust the window's position, using a smooth movement by incrementally rotating the servo from 0° to 180° (or vice versa).

        3. **httpGETRequest(const char serverName)**
        
                ```cpp
                String SmartWindowControl::httpGETRequest(const char* serverName);
                ```
                
                - This method sends a POST request to the server with sensor data (water level and rain sensor state) and receives the server’s response containing window control parameters (rain threshold and window state).
                - The server response is then parsed and used in the controlWindow() method to determine the window's action.

          - This library provides a robust, secure, and flexible solution for controlling windows in smart homes, responding to environmental conditions, and allowing for server-side integration and control.

  ---

  Feel free to open an issue or submit a pull request to enhance or report problems with the **SmartWindowControl** library.

  Happy Coding! 😊
