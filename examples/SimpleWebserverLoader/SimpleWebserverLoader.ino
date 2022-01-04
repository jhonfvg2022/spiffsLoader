#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "spiffsLoader.h"

const char* ssid = "********";
const char* password =  "**********";

AsyncWebServer server(80);
SpiffsLoader loader;

void setup() {
  //Serial.begin(115200);
  loader.initSpiffsLoader();    
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }  
  Serial.println(WiFi.localIP());
  server.on("/index", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", "text/html");
  }); 
  server.begin();
}

void loop() {
  loader.loop();
}
