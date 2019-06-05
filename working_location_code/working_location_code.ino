#include "UbidotsMicroESP8266.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define TOKEN  "A1E-E9Civ0PCH1OO4TRZEUz99w2qCnWR9c"  // Put here your Ubidots TOKEN
#define WIFISSID "SPAM" // Put here your Wi-Fi SSID
#define PASSWORD "12345678" // Put here your Wi-Fi password

Ubidots client(TOKEN);

static const int RXPin = 0, TXPin = 2;
static const uint32_t GPSBaud = 9600; // Change according to your device

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

double _lat1, _lng1;
double _lat2, _lng2;
int dummy1 = 1;
int dummy2 = 2;
char context[25];

unsigned long previousMillis = 0;     // last time data was send
const long interval = 15000;           // data transfer interval

void calDistance();
int deg2rad();

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
          _lat1 = gps.location.lat();
          _lng1 = gps.location.lng();
          sprintf(context, "lat=%.4f$lng=%.4f", _lat1, _lng1);

          client.add("D1", dummy1, context);
          client.sendAll(true);
          Serial.print(F("Location1: "));
          Serial.print(_lat1);
          Serial.print(F(","));
          Serial.print(_lng1);

          _lat2 = 12.9716;
          _lng2 = 77.5946;
          sprintf(context, "lat=%.4f$lng=%.4f", _lat2, _lng2);

          client.add("D2", dummy2, context);
          client.sendAll(true);

          Serial.print(F("Location2: "));
          Serial.print(_lat2);
          Serial.print(F(","));
          Serial.print(_lng2);
          calDistance();
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

void calDistance()
{
  double dlon, dlat;
  double a, c, d;
  dlon = deg2rad(_lng2 - _lng1);
  Serial.print("dlon:  "); Serial.println(dlon);
  dlat = deg2rad(_lat2 - _lat1);
  Serial.print("dlat:  "); Serial.println(dlat);
  a = sq(sin(dlat / 2)) + cos(deg2rad(_lat1)) * cos(deg2rad(_lat2)) * sq(sin(dlon / 2));
  Serial.print("a:  "); Serial.println(a);
  c = 2 * atan2( sqrt(a), sqrt(1 - a) );
  Serial.print("c:  "); Serial.println(c);
  d = 6378.1 * c    ;                         //(where R is the radius of the Earth);
  Serial.print("d:  "); Serial.println(d);
  client.add("Dist", d);
  client.sendAll(true);
  Serial.print("Dist :: ");
  Serial.println(d);
}

double deg2rad( double degree)
{
  return (degree * (PI / 180));
}
