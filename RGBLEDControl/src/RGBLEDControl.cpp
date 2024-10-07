/*
* RGBLED CONTROL-------------------
* Use RGBLED:
*  -> Control remotely
*     - Toggle, Blink and light by specific color from platform set values
* ANGAZA ELIMU - SH.PROJECT V2.0 / 023
* ----------------------------------------
*/

#include "RGBLEDControl.h"
#define pwm_Frequency 12000 // PWM frequency
#define pwm_resolution 8    // 8 bit resolution

// RGBLED PWM channels
#define R_channel 0
#define G_channel 1
#define B_channel 2

int timer_count = 0;       // timer counter
uint8_t color = 0;         // a value from 0 to 255 representing the hue
uint32_t R, G, B;          // the Red Green and Blue color components
uint8_t brightness = 255;  // 255 is maximum brightness, but can be changed.  Might need 256 for common anode to fully turn off.
const boolean invert = true;  // set true if common anode, false if common cathode LED

// Constructor with essential parameters
RGBLEDControl::RGBLEDControl(const char* ssid, const char* password, const char* serverUrl, const char* rootCert, const String& apiKey, int redPin, int greenPin, int bluePin, int onboardLedPin)
    : _ssid(ssid), _password(password), _serverUrl(serverUrl), _rootCert(rootCert), _apiKey(apiKey), _redPin(redPin), _greenPin(greenPin), _bluePin(bluePin), _onboardLedPin(onboardLedPin) {}

void RGBLEDControl::begin() {

    // Initialize Serial Monitor
    Serial.begin(115200);

    // RGBLED pins configuration(Attach to PWW channel and setup resolution )
    ledcAttach(_redPin, pwm_Frequency, pwm_resolution);
    ledcAttach(_greenPin, pwm_Frequency, pwm_resolution);
    ledcAttach(_bluePin, pwm_Frequency, pwm_resolution);

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

    _client.setCACert(_rootCert); // set secure client via root cert
}

// Function to initiate RGDLED connection and control
void RGBLEDControl::controlRGBLED() {
    String rgbled_data;
    int blink_interval;
    String rgb_toggle_val;
    int redValue;
    int greenValue;
    int blueValue;

    //Initializing an HTTPS communication using the secure client
    Serial.print("[HTTPS] begin...\n");
    if (_https.begin(_client, _serverUrl)) {
        rgbled_data = httpGETRequest(_serverUrl);
        JSONVar json_rgbled_data = JSON.parse(rgbled_data);

        if (JSON.typeof(json_rgbled_data) == "undefined") {
            Serial.println("Parsing input failed!");
            return;
        }

        // Retrieve data from JSON response
        blink_interval = (const int)(json_rgbled_data["blink_interval"]);
        rgb_toggle_val = (const char*)(json_rgbled_data["toggle_state"]);
        redValue = (const int)(json_rgbled_data["rled_slider_val"]);
        greenValue = (const int)(json_rgbled_data["gled_slider_val"]);
        blueValue = (const int)(json_rgbled_data["bled_slider_val"]);

        Serial.println("Blink interval: " + String(blink_interval));
        Serial.println("RGBLED toggle state: " + rgb_toggle_val);
        Serial.println("\nRed led value: " + String(redValue));
        Serial.println("Green led value: " + String(greenValue));
        Serial.println("Blue led value: " + String(blueValue) + "\n");

        if (rgb_toggle_val == "1") { // Turn ON RGB LED
            RGB_Color(redValue, greenValue, blueValue);

            // invoke color fade mode if no blink interval is set
            if (blink_interval <= 0) {
              rgbLedFadeMode(); // Switch RGB LED to fade mode
            }

            if (blink_interval > 0) { // Blinking based on interval
                RGB_Color(redValue, greenValue, blueValue);
                delay(blink_interval);
                RGB_Color(0, 0, 0);
                delay(blink_interval);
            }
            Serial.println("\nRGB LED status: ON\n");
        } else if (rgb_toggle_val == "0") { // Turn OFF RGB LED
            RGB_Color(0, 0, 0);
            Serial.println("\nRGB LED status: OFF\n");
        }
    } else {
        Serial.printf("[HTTPS] Unable to connect\n");
    }

    // Default delay when no blink interval is set
    if (blink_interval <= 0) {
        delay(3000);
    }
}

// Method to handle HTTP POST request
String RGBLEDControl::httpGETRequest(const char* serverName) {
    String httpRequestData = "rgbled_toggle_API_KEY=" + String(_apiKey);
    _https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpResponseCode = _https.POST(httpRequestData);

    String payload;

    if (httpResponseCode > 0) {
        payload = _https.getString();
    }

    _https.end(); // end the connection and free the resources
    return payload; // returns server response
}

void RGBLEDControl::RGB_Color(int red, int green, int blue) {
    ledcWrite(_redPin, red);
    ledcWrite(_greenPin, green);
    ledcWrite(_bluePin, blue);
}

//RGB LED Fade mode Loop Handler
void RGBLEDControl::rgbLedFadeMode(){
    Serial.println("LED TEST\n-------------------");
    Serial.println("1. Send all LEDs a 255 and wait 2 seconds.");
    Serial.println("\nNOTE:--------------------");
    Serial.println("-> If your RGB LED turns OFF instead of ON here you should check if the LED\n   is common anode or cathode.");
    Serial.println("-> If it doesn't fully turn off and is common anode try using 256(as max brightness).\n");
    ledcWrite(_redPin, 255);
    ledcWrite(_greenPin, 255);
    ledcWrite(_bluePin, 255);
    delay(2000);
    Serial.println("2. Send all LEDs a 0 and wait 2 seconds.\n");
    ledcWrite(_redPin, 0);
    ledcWrite(_greenPin, 0);
    ledcWrite(_bluePin, 0);
    delay(2000);

    Serial.print("Switching to fade color mode");
    delay(500);
    while(timer_count < 3){
      delay(500);
      Serial.print(".");

      timer_count++; // increment time counter by 1
    }

    timer_count = 0; // resets time counter
    Serial.println("");
    for (color = 0; color < 255; color++) {  // Slew through the color spectrum

      hueToRGB(color, brightness);  // call function to convert hue to RGB

      // write the RGB values to the pins
      ledcWrite(_redPin, R);  // write red component to channel 1, etc.
      ledcWrite(_greenPin, G);
      ledcWrite(_bluePin, B);

      delay(100);  // full cycle of rgb over 256 colors takes 26 seconds
    }
}

void RGBLEDControl::hueToRGB(uint8_t hue, uint8_t brightness) {
  uint16_t scaledHue = (hue * 6);
  uint8_t segment = scaledHue / 256;                     // segment 0 to 5 around the
                                                         // color wheel
  uint16_t segmentOffset = scaledHue - (segment * 256);  // position within the segment

  uint8_t complement = 0;
  uint16_t prev = (brightness * (255 - segmentOffset)) / 256;
  uint16_t next = (brightness * segmentOffset) / 256;

  if (invert) {
    brightness = 255 - brightness;
    complement = 255;
    prev = 255 - prev;
    next = 255 - next;
  }

  switch (segment) {
    case 0:  // red
      R = brightness;
      G = next;
      B = complement;
      break;
    case 1:  // yellow
      R = prev;
      G = brightness;
      B = complement;
      break;
    case 2:  // green
      R = complement;
      G = brightness;
      B = next;
      break;
    case 3:  // cyan
      R = complement;
      G = prev;
      B = brightness;
      break;
    case 4:  // blue
      R = next;
      G = complement;
      B = brightness;
      break;
    case 5:  // magenta
    default:
      R = brightness;
      G = complement;
      B = prev;
      break;
  }
}
