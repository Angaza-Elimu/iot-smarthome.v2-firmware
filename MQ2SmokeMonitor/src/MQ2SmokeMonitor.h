/*
* SMOKE DETECTION HANDLER(header file)------------------
* USE MQ2 - SMOKE SENSOR:
*    -> Measure smoke value and compare against the set threshold
*    -> Sound buzzer alarm if smoke value surpasses set threshold
* AMGAZA ELIMU - SH. PROJECT V2.0 / 023
* ----------------------------------------
*/
#ifndef MQ2SmokeMonitor_h
#define MQ2SmokeMonitor_h

#include <WiFi.h>
#include "Arduino.h"
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

class MQ2SmokeMonitor
{
  public:
    MQ2SmokeMonitor(const char* server_url, const char* root_cacert, const char* api_key, int onboardLedPin, int buzzerPin, int gasSensorPin);
    void begin(const char* ssid, const char* password); //initialize the library, wifi connection and hardware components
    void monitorSmoke(); // Method to monitor smoke sensor and control buzzer

  private:
    // variables control parameters and functions
    int _onboardLedPin, _buzzerPin, _gasSensorPin, _smokeThreshold, _gasValue, _httpResponseCode;
    const char* _serverUrl;
    const char* _rootCert;
    const char* _apiKey;
    WiFiClientSecure _client;
    HTTPClient _https;
    String httpGETRequest(const char* serverName);
    void handleSmokeDetection();
};

#endif
