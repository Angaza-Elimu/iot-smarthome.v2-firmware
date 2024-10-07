/*
* RGBLED CONTROL-------------------
* Use RGBLED:
*  -> Control remotely
*     - Toggle, Blink and light by specific color from platform set values
* AMGAZA ELIMU - SH.PROJECT V2.0 / 023
* ----------------------------------------
*/

#include <RGBLEDControl.h>
#include "secrets.h"
#include "pin_configurations.h"

// Define your RGBLEDControl object
RGBLEDControl rgbLedControl(WIFI_SSID, WIFI_PASSWORD, SERVER_URL, root_cacert, API_KEY, RED_PIN, GREEN_PIN, BLUE_PIN, ONBOARD_LED_PIN);

void setup() {
    Serial.begin(115200);
    rgbLedControl.begin();
}

void loop() {
    rgbLedControl.controlRGBLED();
    delay(1000); // Check RGB LED control every second
}
