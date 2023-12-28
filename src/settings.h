#ifndef SETTINGS_H
#define SETTINGS_H

#include <ArduinoJson.h>

// Define the maximum number of stations
#define MAX_STATIONS 20

struct Station {
  const char* name;
  const char* url;
  const char* image;
};

struct Config {
  const char* wifiSSID;
  const char* wifiPassword;
  Station stations[MAX_STATIONS];
  int numberOfStations;  // New variable
};

extern Config configuration;

bool loadConfigFromSDCard();
const char* getStationName(int index);
const char* getStationURL(int index);
const char* getStationImage(int index);

#endif
