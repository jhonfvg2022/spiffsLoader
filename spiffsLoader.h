/*
    spiffsLoader.h
    Created on: Jan 3, 2022
    Author: Jhon Valencia
    jhonfvg78@gmail.com
*/

#ifndef SPIFFSLOADER_H
#define SPIFFSLOADER_H

#include "Arduino.h"
#include "SPIFFS.h"
#include <ArduinoJson.h>

class SpiffsLoader
{
public:
  SpiffsLoader();
  void initSpiffsLoader();
  void loop();

private:
  void createFile(String filename);
  void appendFile(String line);
  void getFiles();
  void deleteFile(String filename);
  void deletesAll();
  void getError();  
  void receiveSerial();
  void completeSerial();
  String _filename;
  int error;
  String inputString = "";
  bool stringComplete = false;
};

#endif
