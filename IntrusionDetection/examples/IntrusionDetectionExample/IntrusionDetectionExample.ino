/*
* INTRUSION DETECTION CONTROL(arduino source code)-------------------
* Detect motion using:
*  -> PIR sensor
*  -> Turn ON LED if motion detected
* ANGAZA ELIMU - SH.PROJECT V2.0 / 023
* ----------------------------------------
*/
#include "IntrusionDetection.h"
#include "secrets.h"  // Include the secrets file for credentials and API key
#include "pin_configurations.h" // Includes board pins configuration

// Create an instance of the IntrusionDetection class using secrets
IntrusionDetection intrusionDetector(WIFI_SSID, WIFI_PASSWORD, SERVER_URL, root_cacert, API_KEY, PIR_PIN, ONBOARD_LED_PIN, RED_PIN, GREEN_PIN, BLUE_PIN);

void setup() {
    // Initialize the library
    intrusionDetector.begin();
}

void loop() {
    // Monitor the PIR sensor
    intrusionDetector.monitorPIRSensor();

    // Delay to avoid rapid consecutive requests
    delay(3000);
}
