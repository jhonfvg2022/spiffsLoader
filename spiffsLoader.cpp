/*
    spiffsLoader.h
    Created on: Jan 3, 2022
    Author: Jhon Valencia
    jhonfvg78@gmail.com
*/

#include "Arduino.h"
#include "spiffsLoader.h"

SpiffsLoader::SpiffsLoader()
{
  error = 0;
  inputString = "";
  stringComplete = false;
}

void SpiffsLoader::initSpiffsLoader()
{
  initSerial();
  if (!SPIFFS.begin(true))
  {
    return;
  }
}

void SpiffsLoader::loop()
{
  receiveSerial();
}

//----------------------------------------------------
//private function SPIFFS
//----------------------------------------------------
void SpiffsLoader::createFile(String filename)
{
  error = 0;
  _filename = filename;
  SPIFFS.remove("/" + _filename);
  File fileToAppend = SPIFFS.open("/" + _filename, FILE_APPEND);
  if (!fileToAppend)
  {
    error++;
    return;
  }
  fileToAppend.close();
  String jsonString;
  DynamicJsonDocument doc(512);
  doc["cmd"] = "start";
  serializeJson(doc, jsonString);
  Serial.println(jsonString);
}

void SpiffsLoader::appendFile(String line)
{
  File fileToAppend = SPIFFS.open("/" + _filename, FILE_APPEND);
  if (!fileToAppend)
  {
    error++;
    return;
  }
  if (!fileToAppend.println(line))
    error++;
  fileToAppend.close();
}

void SpiffsLoader::getFiles()
{
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  DynamicJsonDocument doc(512);
  doc["cmd"] = "files";
  JsonArray data = doc.createNestedArray("files");
  while (file)
  {
    data.add(((String)file.name()).substring(1));
    file = root.openNextFile();
  }
  root.close();
  file.close();
  String jsonString;
  serializeJson(doc, jsonString);
  Serial.println(jsonString);
}

void SpiffsLoader::deleteFile(String filename)
{
  if (SPIFFS.remove("/" + filename))
  {
    String jsonString;
    DynamicJsonDocument doc(512);
    doc["cmd"] = "delete";
    serializeJson(doc, jsonString);
    Serial.println(jsonString);
  }
}

void SpiffsLoader::deletesAll()
{
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while (file)
  {
    SPIFFS.remove((String)file.name());
    file = root.openNextFile();
  }
  root.close();
  file.close();
  String jsonString;
  DynamicJsonDocument doc(512);
  doc["cmd"] = "deleteall";
  serializeJson(doc, jsonString);
  Serial.println(jsonString);
}

void SpiffsLoader::getError()
{
  String jsonString;
  DynamicJsonDocument doc(512);
  doc["cmd"] = "error";
  doc["error"] = (String)error;
  serializeJson(doc, jsonString);
  Serial.println(jsonString);
}

//----------------------------------------------------
//private function Serial
//----------------------------------------------------

void SpiffsLoader::initSerial()
{
  Serial.begin(115200);
  delay(100);
  Serial.println("serial ok");
}

void SpiffsLoader::receiveSerial()
{
  while (Serial.available())
  {
    char inChar = (char)Serial.read();
    if (inChar == '\n')
      stringComplete = true;
    else
    {
      if (inChar != '\r')
        inputString += inChar;
    }
  }
  completeSerial();
}

void SpiffsLoader::completeSerial()
{
  if (stringComplete)
  {
    DynamicJsonDocument docIn(1024);
    DeserializationError error = deserializeJson(docIn, inputString);
    if (error)
    {
      inputString = "";
      stringComplete = false;
      return;
    }
    if (docIn.containsKey("cmd"))
    {
      if (String((const char *)docIn["cmd"]) == "upload")
      {
        if (docIn.containsKey("fileName"))
          createFile(String((const char *)docIn["fileName"]));
      }
      if (String((const char *)docIn["cmd"]) == "line")
      {
        if (docIn.containsKey("line"))
          appendFile(String((const char *)docIn["line"]));
      }
      if (String((const char *)docIn["cmd"]) == "error")
      {
        getError();
      }
      if (String((const char *)docIn["cmd"]) == "files")
      {
        getFiles();
      }
      if (String((const char *)docIn["cmd"]) == "delete")
      {
        if (docIn.containsKey("fileName"))
          deleteFile(String((const char *)docIn["fileName"]));
      }
      if (String((const char *)docIn["cmd"]) == "deleteall")
      {
        deletesAll();
      }
    }
    inputString = "";
    stringComplete = false;
  }
}
