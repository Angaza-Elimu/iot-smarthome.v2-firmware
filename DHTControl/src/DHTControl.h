/*
* TEMPERATURE&HUMIDITY MONITORING(Header file)------------------
* USE DHT SENSOR:
*    -> Measure room temperature and humidity values
*    -> Send the recorded data to the platform
*    -> Set temperature threshold from the platform
*    -> Use set threshod and recorded data to control fan
* ANGAZA ELIMU - SH. PROJECT V2.0 / 023
* ----------------------------------------
*/

#ifndef DHTCONTROL_H
#define DHTCONTROL_H

#include <Arduino.h>
#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFiClientSecure.h>

class DHTControl {
public:
    DHTControl(const char* ssid, const char* password, const char* serverUrl, const char* rootCert, const String& apiKey, int dhtPin, uint8_t dhtSensorType, uint8_t dispScreenW, uint8_t dispScreenH, int inaPin, int inbPin, int oledSda, int oledScl, int onboardLedPin);
    void begin(); // Method to initialize the library and hardware components
    void monitorDHTSensor(); // Method to monitor DHT sensor and control fan
    String httpGETRequest(const char* serverName); // Method for HTTP GET request

private:
    // server and wifi connection parameters
    const char* _ssid;
    const char* _password;
    const char* _serverUrl;
    const char* _rootCert;
    String _apiKey;

    // components pin
    int _dhtPin;
    int _inaPin;
    int _inbPin;
    int _oledSda;
    int _oledScl;

    // component objects
    DHT _dhtSensor;
    Adafruit_SSD1306 _display;
    WiFiClientSecure _client;
    uint8_t _dhtSensorType;
    uint8_t _dispScreenW;
    uint8_t _dispScreenH;

    // control parameter variables
    HTTPClient _https;
    float _humi;
    float _tempC;
    int _tempThreshold;
    int _humidThreshold;
    String _payload;

    // onboard LED pin
    int _onboardLedPin;
};

#endif
