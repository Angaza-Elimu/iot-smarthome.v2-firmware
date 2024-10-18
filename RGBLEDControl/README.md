# Angaza Elimu Smarthome - RGBLEDControl Library

## Description

The `RGBLEDControl` library allows you to control RGB LED lights remotely over WiFi. You can toggle, blink, and set colors from a platform, making it an essential component for smart home automation projects.

This library is designed to work with ESP32 devices, leveraging its WiFi capabilities to connect to your IoT platform and control RGB LEDs based on server data.

## Features

- Remotely control RGB LED lights via WiFi.
- Toggle, blink, and set specific colors based on platform inputs.
- Supports fading modes and color transitions.

## Installation

### Install the Library in Arduino IDE

To install the `RGBLEDControl` library, follow these steps:

1. **Download the Library**  
   Clone or download the library from the GitHub repository:

   ```bash
   git clone https://github.com/Angaza-Elimu/iot-smarthome.v2-firmware/RGBLEDControl.git
  ```

  ### Step 2: Install the Library in Arduino IDE

  1. Open Arduino IDE.
  2. Navigate to `Sketch` -> `Include Library` -> `Add .ZIP Library...`
  3. Select the downloaded `RGBLEDControl.zip` file.
  4. The library will now be available in your Arduino IDE.

## Usage
 ### Example Code
Here is a basic example of how to use the RGBLEDControl library in your Arduino sketches.


\`\`\`cpp
#include <RGBLEDControl.h>

// Define your WiFi credentials and server settings
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* serverUrl = "https://your-server.com";
const char* rootCert = "-----BEGIN CERTIFICATE-----\n...your cert...\n-----END CERTIFICATE-----\n"; // Add your root certificate
String apiKey = "your_api_key"; // Get API key from your platform

// Define the pins for RGB LED
#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11
#define ONBOARD_LED_PIN 13

// Create an instance of the RGBLEDControl class
RGBLEDControl rgbLed(ssid, password, serverUrl, rootCert, apiKey, RED_PIN, GREEN_PIN, BLUE_PIN, ONBOARD_LED_PIN);

void setup() {
    rgbLed.begin(); // Initialize the RGB LED
}

void loop() {
    rgbLed.controlRGBLED(); // Control RGB LED based on server data
}

\`\`\`

 ### Pin Connections
Connect the RGB LED to your Arduino as follows:

- Red Pin to Pin 9 (or any PWM-enabled pin)
- Green Pin to Pin 10 (or any PWM-enabled pin)
- Blue Pin to Pin 11 (or any PWM-enabled pin)
- Common Anode/Cathode to 5V or GND as per your LED type
- Onboard LED Pin to Pin 13 (optional)

## Methods
 ### Constructor
\`\`\`cpp
RGBLEDControl(const char* ssid, const char* password, const char* serverUrl, const char* rootCert, const String& apiKey, int redPin, int greenPin, int bluePin, int onboardLedPin);
\`\`\`

 ### Public Methods
- `void begin():` Initializes the library and hardware components.
- `void controlRGBLED():` Controls the RGB LED based on server data.

 ### Private Methods
- `String httpGETRequest(const char* serverName):` Sends a GET request to the server.
- `void RGB_Color(int red, int green, int blue):` Sets the RGB color.
- `void rgbLedFadeMode():` Controls the RGB LED fade mode.
- `void hueToRGB(uint8_t hue, uint8_t brightness):` Controls color hue fading.

 ### Additional Notes
- Ensure that you have configured the correct WiFi credentials, server URL, root certificate, and API key in your sketch for successful operation.
- This library requires an active internet connection to function properly.
