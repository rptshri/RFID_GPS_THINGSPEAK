#include "UbidotsMicroESP8266.h"

#define TOKEN  "A1E-N6Gf7ttRwp6BjyaG2EEQDLtXbTg94V"  // Put here your Ubidots TOKEN
#define WIFISSID "SPAM" // Put here your Wi-Fi SSID
#define PASSWORD "12345678" // Put here your Wi-Fi password

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
  int latitude = 124;
    int lat1= 50;
  


  client.add("str_temp", latitude);
    client.add("str_temp2", lat1);
  client.sendAll(true);
  delay(100);
}
