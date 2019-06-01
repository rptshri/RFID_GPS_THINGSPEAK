#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 5, TXPin = 4;        //TX to D1 and RX to D2
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

boolean flag = 0;
//double latitude;
//double latitude;
String latbuf;
String lonbuf;
//float Lat = 0.000000;
//float Long = 0.000000;



void displayInfo()
{ Serial.println("In DisplayInfo.");

  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    double latitude = (gps.location.lat());
    double longitude = (gps.location.lng());

    latbuf += (String(latitude, 6));
    Serial.println(latbuf);

    String lonbuf;
    lonbuf += (String(longitude, 6));
    Serial.println(lonbuf);
    flag = 1;
  }
  else
  {
    Serial.print(F("INVALID"));
    flag = 0;
  }
  //
  //  Serial.print(F("  Date/Time: "));
  //  if (gps.date.isValid())
  //  {
  //    Serial.print(gps.date.month());
  //    Serial.print(F("/"));
  //    Serial.print(gps.date.day());
  //    Serial.print(F("/"));
  //    Serial.print(gps.date.year());
  //  }
  //  else
  //  {
  //    Serial.print(F("INVALID"));
  //  }
  //
  //  Serial.print(F(" "));
  //  if (gps.time.isValid())
  //  {
  //    if (gps.time.hour() < 10) Serial.print(F("0"));
  //    Serial.print(gps.time.hour());
  //    Serial.print(F(":"));
  //    if (gps.time.minute() < 10) Serial.print(F("0"));
  //    Serial.print(gps.time.minute());
  //    Serial.print(F(":"));
  //    if (gps.time.second() < 10) Serial.print(F("0"));
  //    Serial.print(gps.time.second());
  //    Serial.print(F("."));
  //    if (gps.time.centisecond() < 10) Serial.print(F("0"));
  //    Serial.print(gps.time.centisecond());
  //  }
  //  else
  //  {
  //    Serial.print(F("INVALID"));
  //  }

  Serial.println();
}


void getGPSdata()
{ Serial.println("In getGPSdata.");
  Serial.begin(9600);
  ss.begin(GPSBaud);

  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while (true);
  }
}
