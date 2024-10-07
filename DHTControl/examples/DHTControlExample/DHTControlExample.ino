/*
* TEMPERATURE&HUMIDITY MONITORING(Arduino Source file)------------------
* USE DHT SENSOR:
*    -> Measure room temperature and humidity values
*    -> Send the recorded data to the platform
*    -> Set temperature threshold from the platform
*    -> Use set threshod and recorded data to control fan
* ANGAZA ELIMU - SH. PROJECT V2.0 / 023
* ----------------------------------------
*/

// Include the DHTControl library and configuration files
#include "DHTControl.h"
#include "secrets.h"
#include "pin_configurations.h"

// Create a DHTControl object with required parameters for the DHT sensor, Wi-Fi, and display
DHTControl dhtController(WIFI_SSID, WIFI_PASSWORD, SERVER_URL, root_cacert, API_KEY, DHT_PIN, DHT_SENSOR_TYPE, SCREEN_WIDTH, SCREEN_HEIGHT, INA_PIN, INB_PIN, I2C_SDA, I2C_SCL, ONBOARD_LED_PIN);

void setup() {
  Serial.begin(115200);

  // Initialize Wi-Fi connection, DHT sensor, and OLED display
  dhtController.begin();
}

void loop() {
  // Monitor DHT sensor readings, send data to the server, and control the fan
  dhtController.monitorDHTSensor();

  // Wait before next cycle
  delay(2000);
}
