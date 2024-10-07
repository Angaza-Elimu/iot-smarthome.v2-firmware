/*
* RGBLED CONTROL (Header file)-------------------
* Use RGBLED:
*  -> Control remotely
*     - Toggle, Blink and light by specific color from platform set values
* ANGAZA ELIMU - SH.PROJECT V2.0 / 023
* ----------------------------------------
*/

#ifndef RGBLEDCONTROL_H
#define RGBLEDCONTROL_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <WiFiClientSecure.h>

class RGBLEDControl {
    public:
        RGBLEDControl(const char* ssid, const char* password, const char* serverUrl, const char* rootCert, const String& apiKey, int redPin, int greenPin, int bluePin, int onboardLedPin);
        void begin(); // Method to initialize the library and hardware components
        void controlRGBLED(); // Method to control RGB LED based on server data

    private:
        // wifi and server connection control parameters
        const char* _ssid;
        const char* _password;
        const char* _serverUrl;
        const char* _rootCert;
        String _apiKey;

        // component connection pins
        int _redPin;
        int _greenPin;
        int _bluePin;

        // onboard LED pins
        int _onboardLedPin;

        // variables control parameters and functions
        WiFiClientSecure _client;
        HTTPClient _https;
        String httpGETRequest(const char* serverName);
        void RGB_Color(int red, int green, int blue); // Method to set RGB color
        void rgbLedFadeMode(); // controls RGBLED fade mode
        void hueToRGB(uint8_t hue, uint8_t brightness); // controls colors hue fading
};

#endif
