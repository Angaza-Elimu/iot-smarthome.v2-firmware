// Include the DHTControl library and configuration files
#include <SmartLightControl.h>
#include "secrets.h"
#include "pin_configurations.h"

// Create a SmartLightControl object with required parameters
SmartLightControl smartLight(WIFI_SSID, WIFI_PASSWORD, SERVER_URL, API_KEY, root_cacert, ONBOARD_LED_PIN);

void setup() {
  // Initialize Wi-Fi connection
  smartLight.begin();
}

void loop() {
    smartLight.update();
}
