/*
 * SMART LIGHT CONTROL(Source file)-------------------
 * SmartLightControl.cpp - Implementation of SmartLightControl library
 * Version 2.0.0
 *
 * This file contains the implementation of the methods used to control an LED
 * based on platform set controls:
 *     - Toggle ON/OFF
 *     - Blink using platform set interval
 *     - Schedule ON/OFF from platform using timer
 *
 * AMGAZA ELIMU - SH.PROJECT V2.0 / 023
 * ----------------------------------------
 */
#include "SmartLightControl.h"

SmartLightControl::SmartLightControl(const char* ssid, const char* password, const char* serverUrl, const char* apiKey, const char* rootCaCert, int ledPin, int onboardLedPin)
  : _ssid(ssid), _password(password), _serverUrl(serverUrl), _apiKey(apiKey), _rootCaCert(rootCaCert), _ledPin(ledPin), _onboardLedPin(onboardLedPin) {
    _client = new WiFiClientSecure;
    _timerDelay = 5000;
}

void SmartLightControl::begin() {
    Serial.begin(115200);
    delay(10);
    WiFi.begin(_ssid, _password);

    pinMode(_onboardLedPin, OUTPUT);
    digitalWrite(_onboardLedPin, HIGH); // Turn off onboard LED initially

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        digitalWrite(_onboardLedPin, LOW);
        delay(250);
        digitalWrite(_onboardLedPin, HIGH);
        delay(250);
    }

    //----------------------------------------
    digitalWrite(_onboardLedPin, LOW); //--> Turn off the On Board LED when it is connected to the wifi router.
    //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
    Serial.println("");
    Serial.print("Successfully connected to : ");
    Serial.println(_ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println();
    delay(1000);

    // server initialization
    Serial.println("Server started");
    Serial.println(WiFi.localIP());
    Serial.print("\nconnecting...");
    delay(2000);
    Serial.println("\nServer connected!\n");
    delay(1000);

    _client->setCACert(_rootCaCert);
}

void SmartLightControl::update() {
    if (_client) {
        Serial.print("[HTTPS] begin...\n");
        if (_https.begin(*_client, _serverUrl)) {
            String ledData = httpGETRequest(_serverUrl);
            JSONVar jsonResData = JSON.parse(ledData);

            if (JSON.typeof(jsonResData) == "undefined") {
                Serial.println("Parsing input failed!");
                return;
            }

            _ledState = (const char*)(jsonResData["led_control_state"]);
            _ledBlinkInterval = (const int)(jsonResData["led_blink_interval"]);
            _ledBlinkIntensity = (const int)(jsonResData["led_blink_intensity"]);

            Serial.println("LED blink interval: " + String(_ledBlinkInterval));
            Serial.println("LED blink intensity: " + String(_ledBlinkIntensity));

            if (_ledState == "1") { //turn ON signal LED
                digitalWrite(_ledPin, HIGH);
                Serial.println("LED status: ON");

                if (_ledBlinkInterval > 0) { //blinks LED based on platform set time interval
                    digitalWrite(_ledPin, HIGH);
                    delay(_ledBlinkInterval);
                    digitalWrite(_ledPin, LOW);
                    delay(_ledBlinkInterval);
                }
            } else if (_ledState == "0") { //turn OFF signal LED
                digitalWrite(_ledPin, LOW);
                Serial.println("LED status: OFF");
            }
        } else {
            Serial.printf("[HTTPS] Unable to connect\n");
        }
    } else {
        Serial.printf("[HTTPS] Unable to connect\n");
    }

    if (_ledBlinkInterval <= 0) {
        delay(3000);
    }
}

String SmartLightControl::httpGETRequest(const char* serverName) {
    _https.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String httpRequestData = "ledctrl_API_KEY=" + String(_apiKey);
    _httpResponseCode = _https.POST(httpRequestData);
    Serial.print("Data request: ");
    Serial.print(httpRequestData);
    Serial.println("");

    String payload;

    if (_httpResponseCode == 200) {
        Serial.print("HTTP Response code: ");
        Serial.println(_httpResponseCode);
        payload = _https.getString();
    } else {
        Serial.print("Error code: ");
        Serial.println(_httpResponseCode);
    }
    _https.end();

    return payload;
}
