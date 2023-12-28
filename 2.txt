#include "settings.h"
#include <SD.h>  // Use SD.h for external SD card

Config configuration;

bool loadConfigFromSDCard() {
  if (SD.begin()) {  // Initialize SD card
    File configFile = SD.open("/settings.json");
    if (!configFile) {
      Serial.println("Failed to open config file");
      return false;
    }

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);

    StaticJsonDocument<4096> doc;
    DeserializationError error = deserializeJson(doc, buf.get());

    if (error) {
      Serial.println("Failed to parse JSON");
      return false;
    }

    configuration.wifiSSID = doc["wifiSSID"];
    configuration.wifiPassword = doc["wifiPassword"];

    JsonArray stationArray = doc["station"].as<JsonArray>();
    int i = 0;
    for (JsonObject station : stationArray) {
      if (i >= MAX_STATIONS) {
        // Stop processing when the maximum number of stations is reached
        break;
      }

      configuration.stations[i].name = station["name"];
      configuration.stations[i].url = station["url"];
      configuration.stations[i].image = station["image"];
      i++;
    }

    // Set the numberOfStations variable
    configuration.numberOfStations = i;

    configFile.close();
    return true;
  } else {
    Serial.println("Failed to mount SD card");
    return false;
  }
}

const char* getStationName(int index) {
  if (index >= 0 && index < configuration.numberOfStations) {
    return configuration.stations[index].name;
  } else {
    return nullptr;
  }
}

const char* getStationURL(int index) {
  if (index >= 0 && index < configuration.numberOfStations) {
    return configuration.stations[index].url;
  } else {
    return nullptr;
  }
}

const char* getStationImage(int index) {
  if (index >= 0 && index < configuration.numberOfStations) {
    return configuration.stations[index].image;
  } else {
    return nullptr;
  }
}
