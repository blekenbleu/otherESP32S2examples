// http://arduino-er.blogspot.com/2021/04/esp32-s2arduino-esp32-s2-saola-1-web.html
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "esp32s2LED.h"

CREATE_ESP32_WS2812_INSTANCE();

AsyncWebServer server(80);

// ssid/password match your WiFi Network
const char* ssid = "Actiontec-8318-2.4G";
const char* password = "e3d9dd3c";

const char* Param_COLOR ="color";
const char* Param_ID = "id";
unsigned int count = 0;
int r = 50, g = 50, b = 50;

// HTML: rename to range.htm to test in browsers
#include "range.h"	// const char index_html[]

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
  Serial.println("--- ESP32_WebRGB_ColorPicker Start---");
  Serial.print("Chip Model: ");
  Serial.println(ESP.getChipModel());
  Serial.print("\nChip Revision: ");
  Serial.println(ESP.getChipRevision());
  Serial.println();
  
  ESP32_WS2812_SETUP(0);      // WS2812 all off

  //Act as STA, connect to WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("Visit IP Address: ");
  Serial.println(WiFi.localIP());

  // Send HTML
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?color=rr -or- gg -or- bb
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String color_value, id_value;

    //check if parameter "color" found
    if (request->hasParam(Param_COLOR)) {
      Serial.print("param_COLOR received:  ");
      color_value = request->getParam(Param_COLOR)->value();
      Serial.println(color_value);
      // color_value.remove(0, 1);  // remove '#' ??
      if (request->hasParam(Param_ID)) {
        Serial.print("param_ID received:  ");
        id_value = request->getParam(Param_ID)->value();
        Serial.print(id_value);
        char c[id_value.length() + 1];
        id_value.toCharArray(c, id_value.length() + 1);
        Serial.write(" = ");
        Serial.println(c);
        //Convert intMessage to int
        int intColor = stol(color_value);
        if ('0' == c[1])
          r = intColor;
        else if ('1' == c[1])
          g = intColor;
        else if ('2' == c[1])
          b = intColor;
        else {
          Serial.write("param_COLOR ignored for Param_ID = ");
          Serial.println(c);
        }
        Serial.write("Setting ESP32_LED(");
        Serial.print(r);
        Serial.write(",");
        Serial.print(g);
        Serial.write(",");
        Serial.print(b);
        Serial.write(")\n");

        //set NeoPixel color
        ESP32_LED(r,g,b);
        // tell loop to cool it for awhile
        count = 0;
      }
      else Serial.println("param_ID NOT received; ignoring param_COLOR");
    }
    else Serial.println("param_COLOR NOT found");
  });        // server.on("/get"...)
  server.onNotFound(notFound);
  server.begin();
}

// intMessage to long
long stol(String recv){
  char c[recv.length() + 1];
  recv.toCharArray(c, recv.length() + 1);
  return strtol(c, NULL, 10); 
}

void loop() {
  if(count > 40)
    count =  11;	// loop colors here
  if (count > 30)
    ESP32_LED(0,0,5);   // blue is dimmer
  else if (count > 20)
    ESP32_LED(0,1,0);    // plenty bright
  else if (count > 10)
    ESP32_LED(1,0, 0);
  else delay(200);	// hold web colors longer
  delay(100);
  count++;
}