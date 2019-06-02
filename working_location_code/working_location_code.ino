#include "UbidotsMicroESP8266.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define TOKEN  "A1E-E9Civ0PCH1OO4TRZEUz99w2qCnWR9c"  // Put here your Ubidots TOKEN
#define WIFISSID "SPAMer" // Put here your Wi-Fi SSID
#define PASSWORD "        " // Put here your Wi-Fi password

Ubidots client(TOKEN);

static const int RXPin = 5, TXPin = 4;
static const uint32_t GPSBaud = 9600; // Change according to your device

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

double _lat, _lng;
int dummySensorValue = 22;
char context[25];

unsigned long previousMillis = 0;     // last time data was send
const long interval = 5000;           // data transfer interval

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);

  client.wifiConnection(WIFISSID, PASSWORD);
}

void loop()
{
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        if (gps.location.isValid())
        {
          digitalWrite()
          _lat = gps.location.lat();
          _lng = gps.location.lng();
          sprintf(context, "lat=%.2f$lng=%.2f", _lat, _lng);

          client.add("Dummy Sensor", dummySensorValue, context);
          client.sendAll(true);

          Serial.print(F("Location: "));
          Serial.print(_lat);
          Serial.print(F(","));
          Serial.print(_lng);
        }
        else
        {
          Serial.print(F("INVALID"));
        }

        Serial.println();
      }
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while (true);
  }
}
