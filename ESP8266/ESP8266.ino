/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESP8266.h"

/****************************************
 * Define Constants
 ****************************************/
namespace {
  const char * WIFISSID = "VIVOFIBRA-6249"; // Assign your WiFi SSID
  const char * PASSWORD = "8DBD1913B2"; // Assign your WiFi password
  const char * TOKEN = "A1E-2XFeEv14k0TsWFzoQxPJyuY18utbw5"; // Assign your Ubidots TOKEN
}

Ubidots client(TOKEN);

/****************************************
 * Main Functions
 ****************************************/
void setup() {
  Serial.begin(115200);
  client.wifiConnection(WIFISSID, PASSWORD);
}

void loop() {
  client.readData(); // Reads the command from the logger
  delay(1000);
}

