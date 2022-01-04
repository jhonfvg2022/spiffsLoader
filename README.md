# ESP32 spiffsLoader
Tool ESP32 spiffs loader files html, json, csv, txt

# Required dependencies
https://arduinojson.org/v6/doc/installation/

![image](https://user-images.githubusercontent.com/97078311/148014232-79a137b2-2a88-4929-a966-471490214e5d.png)

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
Example https://www.w3schools.com/w3css/tryit.asp?filename=tryw3css_input_contact
```HTML
<!DOCTYPE html>
<html>
<title>W3.CSS</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
<body>

<form action="/action_page.php" class="w3-container w3-card-4 w3-light-grey w3-text-blue w3-margin">
<h2 class="w3-center">Contact Us</h2>
 
<div class="w3-row w3-section">
  <div class="w3-col" style="width:50px"><i class="w3-xxlarge fa fa-user"></i></div>
    <div class="w3-rest">
      <input class="w3-input w3-border" name="first" type="text" placeholder="First Name">
    </div>
</div>

<div class="w3-row w3-section">
  <div class="w3-col" style="width:50px"><i class="w3-xxlarge fa fa-user"></i></div>
    <div class="w3-rest">
      <input class="w3-input w3-border" name="last" type="text" placeholder="Last Name">
    </div>
</div>

<div class="w3-row w3-section">
  <div class="w3-col" style="width:50px"><i class="w3-xxlarge fa fa-envelope-o"></i></div>
    <div class="w3-rest">
      <input class="w3-input w3-border" name="email" type="text" placeholder="Email">
    </div>
</div>

<div class="w3-row w3-section">
  <div class="w3-col" style="width:50px"><i class="w3-xxlarge fa fa-phone"></i></div>
    <div class="w3-rest">
      <input class="w3-input w3-border" name="phone" type="text" placeholder="Phone">
    </div>
</div>

<div class="w3-row w3-section">
  <div class="w3-col" style="width:50px"><i class="w3-xxlarge fa fa-pencil"></i></div>
    <div class="w3-rest">
      <input class="w3-input w3-border" name="message" type="text" placeholder="Message">
    </div>
</div>

<button class="w3-button w3-block w3-section w3-blue w3-ripple w3-padding">Send</button>

</form>

</body>
</html> 
```
![image](https://user-images.githubusercontent.com/97078311/148012261-5e0fee69-65b2-462f-a882-eaa15fea0688.png)

![image](https://user-images.githubusercontent.com/97078311/148013677-461f2967-07f6-4ac8-a477-faa70a1dfb67.png)


