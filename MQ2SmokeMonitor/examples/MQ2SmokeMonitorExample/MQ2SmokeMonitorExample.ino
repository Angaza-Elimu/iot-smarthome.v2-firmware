/*
* SMOKE DETECTION HANDLER(Arduino source file)------------------
* USE MQ2 - SMOKE SENSOR:
*    -> Measure smoke value and compare against the set threshold
*    -> Sound buzzer alarm if smoke value surpasses set threshold
* AMGAZA ELIMU - SH. PROJECT V2.0 / 023
* ----------------------------------------
*/

// Include the DHTControl library and configuration files
#include <MQ2SmokeMonitor.h>
#include "secrets.h"
#include "pin_configurations.h"

// Create a DHTControl object with required parameters for the DHT sensor, Wi-Fi, and display
MQ2SmokeMonitor smokeMonitor(serverURL, root_cacert, API_KEY, ONBOARD_LED_PIN, BUZZER_PIN, MQ2_PIN);

// Initialize Wi-Fi connection, smoke sensor, and buzzer
void setup() {
  smokeMonitor.begin(WIFI_SSID, WIFI_PASSWORD);
}

// Handles logiv control
void loop() {
  smokeMonitor.monitorSmoke();
}
