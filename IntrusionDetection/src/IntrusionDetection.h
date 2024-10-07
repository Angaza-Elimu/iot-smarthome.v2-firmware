/*
* INTRUSION DETECTION CONTROL(Header file)-------------------
* Detect motion using:
*  -> PIR sensor
*  -> Turn ON LED if motion detected
* ANGAZA ELIMU - SH.PROJECT V2.0 / 023
* ----------------------------------------
*/
#ifndef INTRUSION_DETECTION_H
#define INTRUSION_DETECTION_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

class IntrusionDetection {
public:
    // Constructor
    IntrusionDetection(const char* ssid, const char* password, const char* serverUrl, const char* rootCert, const String& apiKey, int pirPin, int onboardLedPin, int redPin, int greenPin, int bluePin);

    // Function to initialize WiFi connection
    void begin();

    // Function to monitor PIR sensor and send status to server
    void monitorPIRSensor();

private:
    // WiFi and Server parameters
    const char* _ssid;
    const char* _password;
    const char* _serverUrl;
    const char* _rootCert;
    String _apiKey;
    WiFiClientSecure _client;
    HTTPClient _https;

    // PIR sensor state variables and pin configuration
    int _pinStateCurrent;
    int _pinStatePrevious;
    int _pirPin;

    // LED connection pins
    int _redPin;
    int _greenPin;
    int _bluePin;

    // onboard LED pin
    int _onboardLedPin;

    // Method to establish secure server connection
    void secureConnection();

    // Method to handle HTTP POST request
    String httpPOSTRequest(const String& data);

    // Method to print WiFi connection status
    void printWiFiStatus();
};

#endif // IntrusionDetection.h
