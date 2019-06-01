#include "UbidotsMicroESP8266.h"

#define TOKEN  "A1E-E9Civ0PCH1OO4TRZEUz99w2qCnWR9c"  // Put here your Ubidots TOKEN
#define WIFISSID "Infinity" // Put here your Wi-Fi SSID
#define PASSWORD "        " // Put here your Wi-Fi password

Ubidots client(TOKEN);


void setup() {
  Serial.begin(9600);
  client.wifiConnection(WIFISSID, PASSWORD);
  client.setDebug(true); // Uncomment this line to set DEBUG on
  //  pinMode(pin, INPUT);
}
void loop() {
  char context[25];
  double latitude = 6.031212;
  double longitude = 73.148125;
  sprintf(context, "lat=%.2f$lng=%.2f", latitude, longitude); //Sends latitude and longitude for watching position in a map
  Serial.println(context);
  client.add("gps", context);  // Change for your variable name
  client.sendAll(true);
  delay(100);
}
