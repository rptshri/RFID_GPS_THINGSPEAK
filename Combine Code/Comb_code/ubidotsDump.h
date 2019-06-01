#include "UbidotsMicroESP8266.h"

#define TOKEN  "A1E-E9Civ0PCH1OO4TRZEUz99w2qCnWR9c"  // Put here your Ubidots TOKEN
#define WIFISSID "Infinity" // Put here your Wi-Fi SSID
#define PASSWORD "        " // Put here your Wi-Fi password

Ubidots client(TOKEN);

void uploadData()
{ Serial.println("In uploadData.");
  
  client.wifiConnection(WIFISSID, PASSWORD);
  delay(100);
  client.setDebug(true);
  client.add("lat", latitude);
  client.add("long", longitude);
  client.sendAll(true);
  delay(100);
}
