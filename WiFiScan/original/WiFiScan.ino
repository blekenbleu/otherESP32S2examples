/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include "WiFi.h"
#include "esp32s2LED.h"

//Onboard RGB LED (NeoPixel)
CREATE_ESP32_WS2812_INSTANCE();
int count = 0;

void setup()
{
    Serial.begin(115200);
    ESP32_WS2812_SETUP(0);      // WS2812 all off
    Serial.println("---WiFiScan Start---");
    Serial.println("Chip Model: ");
    Serial.println(ESP.getChipModel());
    Serial.println("\nChip Revision: ");
    Serial.println(ESP.getChipRevision());
    Serial.println();

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");
    ESP32_LED(100,100,100);
}

void loop()
{
    Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }
    Serial.println("");

    // Wait a bit before scanning again
    delay(5000);
    if (0 == count)
      ESP32_LED(100,0,0);
    else if (1 == count)
      ESP32_LED(0,100,0);
    else if (2 == count)
      ESP32_LED(0,0,100);
    else count = -1;
    count++;
}
