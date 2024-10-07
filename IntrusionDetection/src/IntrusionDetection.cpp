/*
* INTRUSION DETECTION CONTROL(source code file)-------------------
* Detect motion using:
*  -> PIR sensor
*  -> Turn ON LED if motion detected
* ANGAZA ELIMU - SH.PROJECT V2.0 / 023
* ----------------------------------------
*/
#include "IntrusionDetection.h"
#define pwm_Frequency 12000 // PWM frequency
#define pwm_resolution 8    // 8 bit resolution

// RGBLED PWM channels
#define R_channel 0
#define G_channel 1
#define B_channel 2

// Constructor with essential parameters
IntrusionDetection::IntrusionDetection(const char* ssid, const char* password, const char* serverUrl, const char* rootCert, const String& apiKey, int pirPin, int onboardLedPin, int redPin, int greenPin, int bluePin)
    : _ssid(ssid), _password(password), _serverUrl(serverUrl), _rootCert(rootCert), _apiKey(apiKey), _pirPin(pirPin), _onboardLedPin(onboardLedPin), _pinStateCurrent(LOW), _pinStatePrevious(LOW), _redPin(redPin), _greenPin(greenPin), _bluePin(bluePin) {}

// Function to initialize WiFi connection and set up the PIR pin
void IntrusionDetection::begin() {
    Serial.begin(115200);

    pinMode(_pirPin, INPUT); // Set PIR pin as input
    pinMode(_onboardLedPin, OUTPUT); // Set onboard LED pin as output
    digitalWrite(_onboardLedPin, HIGH); // Turn off onboard LED

    // RGBLED pins configuration(Attach to PWW channel and setup resolution )
    ledcAttach(_redPin, pwm_Frequency, pwm_resolution);
    ledcAttach(_greenPin, pwm_Frequency, pwm_resolution);
    ledcAttach(_bluePin, pwm_Frequency, pwm_resolution);

    WiFi.begin(_ssid, _password); // Start WiFi connection
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        // Flash the onboard LED while connecting
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

    // Set root certificate for secure connection
    _client.setCACert(_rootCert);
}

// Function to monitor PIR sensor and send status to server
void IntrusionDetection::monitorPIRSensor() {
    _pinStatePrevious = _pinStateCurrent;
    _pinStateCurrent = digitalRead(_pirPin);

    if (_https.begin(_client, _serverUrl)) {

      if (_pinStatePrevious == LOW && _pinStateCurrent == HIGH) { // send to server PIR 1 if motion detected
          Serial.println("Motion detected!\n - Turning ON lights...");

          // Turn ON RGB LED
          Serial.println("\nNOTE:--------------------");
          Serial.println("-> If your RGB LED turns OFF instead of ON here you should check if the LED\n   is common anode or cathode.");
          Serial.println("-> If it doesn't fully turn off and is common anode try using 256(as max brightness).\n");
          ledcWrite(_redPin, 255);
          ledcWrite(_greenPin, 255);
          ledcWrite(_bluePin, 255);

          // post PIR status request
          httpPOSTRequest("pir_sensor_API_KEY=" + _apiKey + "&pir_status=1");
      } else if (_pinStatePrevious == HIGH && _pinStateCurrent == LOW) { // send to server PIR 0 if NO motion detected
          Serial.println("No motion detected!");

          // Turn OFF RGB LED
          ledcWrite(_redPin, 0);
          ledcWrite(_greenPin, 0);
          ledcWrite(_bluePin, 0);

          // post PIR status request
          httpPOSTRequest("pir_sensor_API_KEY=" + _apiKey + "&pir_status=0");
      }
    } else {
        Serial.printf("[HTTPS] Unable to connect\n");
    }
    delay(3000);
}

// Method to handle HTTP POST request
String IntrusionDetection::httpPOSTRequest(const String& data) {
    String payload;
    if (_https.begin(_client, _serverUrl)) { // initialize server HTTPS connection
        _https.addHeader("Content-Type", "application/x-www-form-urlencoded");
        int httpResponseCode = _https.POST(data);
        if (httpResponseCode == 200) {
            Serial.println("Data sent successfully.");
            payload = _https.getString();
        } else {
            Serial.printf("Error: HTTP Response code %d\n", httpResponseCode);
        }
        _https.end(); // end connection and free resources
    } else {
        Serial.println("Error connecting to server.");
    }
    return payload; // returns server response
}

// Method to print WiFi connection status
void IntrusionDetection::printWiFiStatus() {
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}
