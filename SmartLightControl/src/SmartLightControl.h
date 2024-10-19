/*
* SMARTLIGHTS CONTROL-------------------
* Use LED:
*  -> Control remotely
*     - Toggle ON/OFF
*     - Blink using platform set interval
*     - Schedule ON/OFF from platform using timer
* AMGAZA ELIMU - SH.PROJECT V2.0 / 023
* ----------------------------------------
*/
#ifndef SmartLightControl_h
#define SmartLightControl_h

#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>

class SmartLightControl {
public:
    SmartLightControl(const char* ssid, const char* password, const char* serverUrl, const char* apiKey, const char* rootCaCert, int ledPin, int onboardLedPin);
    void begin();
    void update();

private:
    // server and wifi connection parameters
    const char* _ssid;
    const char* _password;
    const char* _serverUrl;
    const char* _apiKey;
    const char* _rootCaCert;

    // compoent pin
    int _ledPin;

    // onboard LED
    int _onboardLedPin;

    // control variable parameters
    WiFiClientSecure* _client;
    HTTPClient _https;
    unsigned long _lastTime;
    unsigned long _timerDelay;
    int _httpResponseCode;
    String _ledState;
    int _ledBlinkInterval;
    int _ledBlinkIntensity;

    String httpGETRequest(const char* serverName);
};

#endif


cREATE a README.md file for SmartLightControl library
