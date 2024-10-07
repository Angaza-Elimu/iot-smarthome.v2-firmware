 /*
  * SMART WINDOW CONTROL(Header file)-------------------
  * SmartWindowControl.h - Smart window controller library
  * Version 2.0.0
  *
  * This library controls a window based on rain sensor data and a timer.
  *
  * Control window based on:
  *    -> Set timer(Opening/Closing time)
  *    -> Rain state
  * AMGAZA ELIMU - SH. V2.0/023
  * ----------------------------------------
  */

#ifndef SmartWindowControl_h
#define SmartWindowControl_h

#include <WiFi.h>
#include <Arduino.h>
#include <ESP32Servo.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <WiFiClientSecure.h>

// Library for controlling a smart window based on rain and timer states
class SmartWindowControl {
  public:
    // Constructor to initialize window control parameters
    SmartWindowControl(const char* ssid, const char* password, const char* server_url, const char* root_cacert, const char* api_key, int servoPin, int waterLevelPin, int onboardLedPin);

    // Initializes WiFi connection and servo motor
    void begin();

    // Controls the smart window state (open/close) based on rain and timer
    void controlWindow();

  private:
    // Helper function to handle the GET request for rain sensor data
    String httpGETRequest(const char* serverName);

    // WiFi credentials and server details
    const char* _ssid;
    const char* _password;
    const char* _serverUrl;
    const char* _rootCert;
    const char* _apiKey;

    Servo windowServo; // Use Servo object from ESP32Servo.h

    // Pin assignments and control variables
    int _servoPin;
    int _waterLevelPin;
    int _onboardLedPin;
    int _servoIndex;
    int _waterLevel;
    int _windowStateCurrent;

    WiFiClientSecure* _client;
    HTTPClient _https;
    String _rainsensorData;
    String _windowState;
    String _rainSensorState;
    int _rainThreshold;
    int _position;
    int _httpResponseCode;
};

#endif
