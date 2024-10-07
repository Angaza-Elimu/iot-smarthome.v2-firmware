#ifndef SECRETS_H
#define SECRETS_H

#include "cert.h"  // Include the certificate file

// WiFi credentials
#define WIFI_SSID "wifi_name_here"
#define WIFI_PASSWORD "wifi_password_here"

// API key for the server
#define API_KEY "project_API_key_here"

// URL to the server API endpoint
const char* serverURL = "https://smart-home-iot.angazaelimu.com/api/rainsensor_state_update";

#endif // SECRETS_H
