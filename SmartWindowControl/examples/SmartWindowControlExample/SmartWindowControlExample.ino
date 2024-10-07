/*
* SMART WINDOW CONTROL(Arduino source file)-------------------
* Control window based on:
*    -> Set timer(Opening/Closing time)
*    -> Rain state
* AMGAZA ELIMU - SH. V2.0/023
* ----------------------------------------
*/

// Include the SmartWindowControl library and configuration files
#include <SmartWindowControl.h>
#include "secrets.h"
#include "pin_configurations.h"

SmartWindowControl windowControl(WIFI_SSID, WIFI_PASSWORD, serverURL, root_cacert, API_KEY, SERVO_PIN, WATER_LEVEL_PIN, ONBOARD_LED_PIN);

void setup() {
  windowControl.begin();  // Initialize WiFi and servo control
}

void loop() {
  windowControl.controlWindow();  // Continuously monitor and control the window
}
