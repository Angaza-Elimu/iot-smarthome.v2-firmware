/*
* TEMPERATURE&HUMIDITY MONITORING(Source file)------------------
* USE DHT SENSOR:
*    -> Measure room temperature and humidity values
*    -> Send the recorded data to the platform
*    -> Set temperature threshold from the platform
*    -> Use set threshod and recorded data to control fan
* ANGAZA ELIMU - SH. PROJECT V2.0 / 023
* ----------------------------------------
*/

#include "DHTControl.h"

// Constructor with essential parameters
DHTControl::DHTControl(const char* ssid, const char* password, const char* serverUrl, const char* rootCert, const String& apiKey, int dhtPin, uint8_t dhtSensorType, uint8_t dispScreenW, uint8_t dispScreenH, int inaPin, int inbPin, int oledSda, int oledScl, int onboardLedPin)
    : _ssid(ssid), _password(password), _serverUrl(serverUrl), _rootCert(rootCert), _apiKey(apiKey), _dhtPin(dhtPin), _dhtSensorType(dhtSensorType), _dispScreenW(dispScreenW), _dispScreenH(dispScreenH), _inaPin(inaPin), _inbPin(inbPin), _oledSda(oledSda), _oledScl(oledScl), _onboardLedPin(_onboardLedPin),
      _dhtSensor(dhtPin, _dhtSensorType), _display(dispScreenW, dispScreenH, &Wire, -1), _client(), _humi(0), _tempC(0), _tempThreshold(0), _humidThreshold(0) {}

    // Function to initialize WiFi connection and set up the pins
void DHTControl::begin() {
    Serial.begin(115200);

    // Setting up custom I2C pins
    Wire.begin(_oledSda, _oledScl);

    // Initialize display
    if(!_display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }

    delay(2000);
    _display.clearDisplay();
    _display.setTextColor(WHITE);

    // Pins functionality definition
    pinMode(_inaPin, OUTPUT);
    pinMode(_inbPin, OUTPUT);

    // WiFi network initialization
    WiFi.begin(_ssid, _password);
    pinMode(_onboardLedPin, OUTPUT);
    digitalWrite(_onboardLedPin, HIGH); // Turn off onboard LED

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
    Serial.print("\nConnecting...");
    delay(2000);
    Serial.println("\nServer connected!\n");
    delay(1000);

    _dhtSensor.begin(); // Initialize the DHT sensor

    _client.setCACert(_rootCert); // Set root certificate
}

// Function to monitor DHT sensor and send data to server
void DHTControl::monitorDHTSensor() {
    _humi = _dhtSensor.readHumidity(); // Read humidity
    _tempC = _dhtSensor.readTemperature(); // Read temperature in Celsius

    if (isnan(_tempC) || isnan(_humi)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    
    // HTTPS initialization
    if (_https.begin(_client, _serverUrl)) {
        // Get the DHT threshold data values from the server
        String dhtData = httpGETRequest(_serverUrl);

        JSONVar jsonThreshold = JSON.parse(dhtData);

        if (JSON.typeof(jsonThreshold) == "undefined") {
            Serial.println("Parsing input failed!");
            return;
        }

        // Extract server set threshold data
        _tempThreshold = (const int)(jsonThreshold["temp_threshold"]);
        _humidThreshold = (const int)(jsonThreshold["humid_threshold"]);

        Serial.println("Set temperature threshold: " + String(_tempThreshold));

        // Control fan based on temperature
        if (_tempC > _tempThreshold) { // start fan
            digitalWrite(_inaPin, LOW);
            Serial.println("Fan spinning");
            digitalWrite(_inbPin, HIGH);
            delay(5000);
        } else { // stop fan
            digitalWrite(_inaPin, LOW);
            Serial.println("Fan stopped");
            digitalWrite(_inbPin, LOW);
        }

        // Display data on OLED screen
        _display.clearDisplay();
        _display.setTextSize(1);
        _display.setCursor(0, 0);
        _display.print("Temperature: ");
        _display.setTextSize(2);
        _display.setCursor(0, 16);
        _display.print(_tempC);
        _display.print(" ");
        _display.setTextSize(1);
        _display.cp437(true);
        _display.write(167);
        _display.setTextSize(2);
        _display.print("C");

        _display.setTextSize(1);
        _display.setCursor(0, 35);
        _display.print("Humidity: ");
        _display.setTextSize(2);
        _display.setCursor(0, 45);
        _display.print(_humi);
        _display.print(" %");

        _display.display();
    } else {
        Serial.println("[HTTPS] Unable to connect");
    }

    // Wait for 2 seconds before next reading
    delay(2000);
}

// Method to handle HTTP POST request
String DHTControl::httpGETRequest(const char* serverName) {
    _https.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String httpRequestData = "dht_sensor_API_KEY=" + _apiKey + "&temperature=" + String(_tempC) + "&humidity=" + String(_humi);
    int httpResponseCode = _https.POST(httpRequestData);

    String payload;

    if (httpResponseCode == 200) {
        Serial.println("Data sent successfully.");
        payload = _https.getString();
    } else {
        Serial.printf("Error: HTTP Response code %d\n", httpResponseCode);
    }
    _https.end(); // End connection and free resources
    return payload; // returns the received server response
}
