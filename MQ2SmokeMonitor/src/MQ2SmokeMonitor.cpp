/*
* SMOKE DETECTION HANDLER(source file)------------------
* USE MQ2 - SMOKE SENSOR:
*    -> Measure smoke value and compare against the set threshold
*    -> Sound buzzer alarm if smoke value surpasses set threshold
* AMGAZA ELIMU - SH. PROJECT V2.0 / 023
* ----------------------------------------
*/
#include "MQ2SmokeMonitor.h"

#define TONE_PWM_CHANNEL 0
#define pwm_resolution 8    // 8 bit resolution

// Constructor: Initializes the class with server details, API key, and pin configurations
MQ2SmokeMonitor::MQ2SmokeMonitor(const char* server_url, const char* root_cacert, const char* api_key, int onboardLedPin, int buzzerPin, int gasSensorPin)
{
  _serverUrl = server_url;            // URL to send smoke sensor data
  _rootCert = root_cacert;            // Root certificate for secure communication
  _apiKey = api_key;                  // API key for authentication
  _onboardLedPin = onboardLedPin;     // LED pin for status indication
  _buzzerPin = buzzerPin;             // Buzzer pin for sounding alarm
  _gasSensorPin = gasSensorPin;       // MQ2 gas sensor pin to read smoke levels
}

// Begin function: Connects to WiFi and initializes hardware components
void MQ2SmokeMonitor::begin(const char* ssid, const char* password)
{
  Serial.begin(115200); // Initialize serial

  pinMode(_gasSensorPin, INPUT); // Set MQ2 sensor pin as input

  pinMode(_onboardLedPin, OUTPUT);    // Set onboard LED pin as output
  digitalWrite(_onboardLedPin, HIGH); // Initially turn off the onboard LED

  // Connect to WiFi network
  WiFi.begin(ssid, password);
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
  Serial.println(ssid);
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

  // Attach the buzzer to the PWM channel for tone control
  ledcAttach(_buzzerPin, TONE_PWM_CHANNEL, pwm_resolution);
  ledcWriteTone(TONE_PWM_CHANNEL, 0); // Ensure no tone is playing initially

  _client.setCACert(_rootCert);         // Set secure connection with the root certificate
}

// monitorSmoke function: Reads the smoke sensor value and handles alarms if necessary
void MQ2SmokeMonitor::monitorSmoke()
{
  _gasValue = analogRead(_gasSensorPin);  // Read smoke sensor value from MQ2 pin

  // Check if the WiFiClientSecure instance is connected
  if (_client.connected()) {

    // Begin HTTPS communication with the server
    if (_https.begin(_client, _serverUrl)) {
      String data = httpGETRequest(_serverUrl);  // Get the current smoke threshold from the server

      // Parse the received JSON data
      JSONVar json_threshold = JSON.parse(data);
      if (JSON.typeof(json_threshold) != "undefined") {
          // Extract smoke threshold value from server response
        _smokeThreshold = (const int)(json_threshold["smoke_threshold"]);

        handleSmokeDetection();  // Check smoke levels and trigger the alarm if necessary
      }
    }
  }
  delay(3000);  // Add a delay for regular monitoring intervals
}

// handleSmokeDetection function: Compares the sensor value with the threshold and triggers an alarm if exceeded
void MQ2SmokeMonitor::handleSmokeDetection()
{
  // If smoke level exceeds the set threshold, sound the alarm using the buzzer
  if (_gasValue > _smokeThreshold) {
    ledcWriteTone(TONE_PWM_CHANNEL, 800);  // Play a tone at 800 Hz
    delay(500);                            // Wait for 500ms
    ledcWriteTone(TONE_PWM_CHANNEL, 1000); // Change tone to 1000 Hz
    delay(500);                            // Wait for 500ms
  }
}

// httpGETRequest function: Sends a POST request with smoke sensor data and returns the server's response
String MQ2SmokeMonitor::httpGETRequest(const char* serverName)
{
  // Add the appropriate content type for the POST request
  _https.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Prepare the POST request data with the API key and smoke sensor value
  String payload = "smoke_sensor_API_KEY=" + String(_apiKey) + "&smoke_sensor_val=" + String(_gasValue);

  // Send the POST request and capture the HTTP response code
  _httpResponseCode = _https.POST(payload);

  // If the request was successful (HTTP 200), return the server response
  if (_httpResponseCode == 200) {
    return _https.getString();  // Return the response payload as a string
  }

  // End the HTTPS session and return an empty string if the request fails
  _https.end();
  return "";
}
