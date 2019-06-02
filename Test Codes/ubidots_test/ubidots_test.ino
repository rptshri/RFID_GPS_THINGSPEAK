#include "UbidotsMicroESP8266.h"

#define TOKEN  "A1E-E9Civ0PCH1OO4TRZEUz99w2qCnWR9c"  // Put here your Ubidots TOKEN
#define WIFISSID "SPAMer" // Put here your Wi-Fi SSID
#define PASSWORD "        " // Put here your Wi-Fi password

Ubidots client(TOKEN);


char str_temp[25];
char str_temp2[25];

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
  dtostrf(latitude, 8, 5, str_temp);
  dtostrf(longitude, 8, 5, str_temp2);


  client.add("str_temp", latitude);
  //  client.add("str_temp2", str_temp2);
  client.sendAll(true);
  delay(100);
}
