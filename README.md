# ESP32 spiffsLoader
Tool ESP32 spiffs loader files html, json, csv, txt

# Required dependencies
https://arduinojson.org/v6/doc/installation/

# Tool spiffsLoader
![image](https://user-images.githubusercontent.com/97078311/148010462-695f1867-81a7-4d56-bb9d-f866aa092614.png)

Tool.zip Load the files to upload (html, json, csv, txt) in the 'data' folder

![image](https://user-images.githubusercontent.com/97078311/148010560-0b610af3-b5d3-4eda-b28b-8d4852888826.png)

# Sketch - WebServer
```C++
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "spiffsLoader.h"

const char* ssid = "********";
const char* password =  "**********";

AsyncWebServer server(80);
SpiffsLoader loader;

void setup() {
  Serial.begin(115200);
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
```
# Index.html 
Copy file to 'data' folder and upload using 'spiffsLoader-win.exe' tool
```HTML
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>SPIFFSLOADER</title>
</head>
<body>
    <h1>Test SPIFFSLOADER</h1>
</body>
</html>
```
![image](https://user-images.githubusercontent.com/97078311/148012261-5e0fee69-65b2-462f-a882-eaa15fea0688.png)

![image](https://user-images.githubusercontent.com/97078311/148012580-235399dc-bd36-4de1-bc11-943794a9246b.png)


