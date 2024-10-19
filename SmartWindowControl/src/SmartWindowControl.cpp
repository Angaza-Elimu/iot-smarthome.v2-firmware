 /*
  * SMART WINDOW CONTROL(Source file)-------------------
  * SmartWindowControl.cpp - Implementation of SmartWindowControl library
  * Version 2.0.0
  *
  * This file contains the implementation of the methods used to control a window
  * based on rain sensor data and timer values.
  * Windows are closed if rain is detected or window close timer control has elapsed
  * Windows are opened if no rain is detected or window open timer control has elapsed 
  *
  * Control window based on:
  *    -> Set timer(Opening/Closing time)
  *    -> Rain state
  * AMGAZA ELIMU - SH. V2.0/023
  * ----------------------------------------
  */

#include "SmartWindowControl.h"
#define TIMER_INTERRUPT_DEBUG 0
#define ISR_SERVO_DEBUG 1
// For ESP32 and ESP32_S2, select ESP32 timer number (0-3)
#define USE_ESP32_TIMER_NO 3
// Published values for SG90 servos; adjust if needed
#define MIN_MICROS 544
#define MAX_MICROS 2450

// Constructor: Initializes WiFi, server details, and pin configurations
SmartWindowControl::SmartWindowControl(const char* ssid, const char* password, const char* server_url, const char* root_cacert, const char* api_key, int servoPin, int waterLevelPin, int onboardLedPin) {
  _ssid = ssid;
  _password = password;
  _serverUrl = server_url;
  _rootCert = root_cacert;
  _apiKey = api_key;
  _servoPin = servoPin;
  _waterLevelPin = waterLevelPin;
  _onboardLedPin = onboardLedPin;
  _client = new WiFiClientSecure;
  _windowStateCurrent = LOW;  // Window is initially open
}

// begin() - Initializes the WiFi connection and sets up the servo
void SmartWindowControl::begin() {
  Serial.begin(115200);
  delay(500);

  // Configure the servo
  windowServo.attach(_servoPin);    // Attach the servo to the specified pin

  pinMode(_waterLevelPin, INPUT); // set water level sensor pin mode to input

  // Connect to WiFi network
  WiFi.begin(_ssid, _password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);                       // Wait for WiFi connection
    Serial.print(".");
    digitalWrite(_onboardLedPin, LOW); // Blink LED while connecting
    delay(250);
    digitalWrite(_onboardLedPin, HIGH);
    delay(250);
  }

  //----------------------------------------
  digitalWrite(_onboardLedPin, LOW);  // Turn off the LED once connected
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(_ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------

  // server initialization
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
  Serial.print("\nConnecting...");
  delay(2000);
  Serial.println("\nServer connected!\n");
  delay(1000);

  _client->setCACert(_rootCert); // set secure client via root cert
}

// controlWindow() - Controls the window based on sensor data and timer
void SmartWindowControl::controlWindow() {
  // Read water level sensor value
  _waterLevel = analogRead(_waterLevelPin);
  Serial.println("Current water level: " + String(_waterLevel));

  //Initializing an HTTPS communication using the secure client
  Serial.println("[HTTPS] begin...\n");
  if (_https.begin(*_client, _serverUrl)) {
    _rainsensorData = httpGETRequest(_serverUrl); // read server data

    JSONVar json_data = JSON.parse(_rainsensorData);// decode received server data
    if (JSON.typeof(json_data) == "undefined") {
      Serial.println("JSON Parsing failed!");
      return;
    }

    // Get set parameters from the platform
    _rainThreshold = (int)(json_data["rain_threshold"]);
    _rainSensorState = (const char*)(json_data["rain_sensor_state"]);
    _windowState = (const char*)(json_data["window_state"]);

    Serial.println("Rain threshold: " + String(_rainThreshold));
    Serial.println("Rain sensor state: " + String(_rainSensorState));
    Serial.println("Window state: " + String(_windowState));

    // Control window based on sensor data
    if (_windowState == "1" || _rainSensorState == "1") {
      if (_windowStateCurrent == LOW) {  // Close window if open
        for (_position = 0; _position <= 180; _position += 10) { // turn servo motor from position 0 to 180deg in steps of 10deg
          windowServo.write(_position);   // Move the servo to the specified position
          delay(30); // delay between steps(30ms)
        }
        _windowStateCurrent = HIGH; // change window state to CLOSED
      }
    } else {
      if (_windowStateCurrent == HIGH) {  // Open window if closed
        for (_position = 180; _position >= 0; _position -= 10) { // turn servo motor from position 180 to 0deg in steps of 10deg
          windowServo.write(_position);   // Move the servo to the specified position
          delay(30); // delay between steps(30ms)
        }
        _windowStateCurrent = LOW; // change window state to OPEN
      }
    }
  }
  delay(3000);
}

// httpGETRequest() - Sends a POST request with sensor data
String SmartWindowControl::httpGETRequest(const char* serverName) {
  _https.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String requestData = "rain_sensor_API_KEY=" + String(_apiKey) + "&water_level=" + String(_waterLevel);
  _httpResponseCode = _https.POST(requestData); // post data

  // return server response if connection success
  if (_httpResponseCode == 200) {
    return _https.getString();
  } else {
    Serial.println("Error code: " + String(_httpResponseCode));
    return "";
  }

  _https.end(); // close server connection and release memory resources
}


Create a SmartWindowControl monitor library using this source code. Describe key features and  library class methods in manipulating the library
