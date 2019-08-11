#include "UbidotsMicroESP8266.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 0, TXPin = 2;
static const uint32_t GPSBaud = 9600; // Change according to your device
// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 15 //D8
#define RST_PIN 0//D3 (NC)
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;


#define TOKEN  "A1E-E9Civ0PCH1OO4TRZEUz99w2qCnWR9c"  // Put here your Ubidots TOKEN
#define WIFISSID "SPAM" // Put here your Wi-Fi SSID
#define PASSWORD "12345678" // Put here your Wi-Fi password

Ubidots client(TOKEN);

double _lat1, _lng1;
double _lat2, _lng2;
int dummy1 = 1;
int dummy2 = 2;
char context[25];
int flag = 0;
boolean one = false;

unsigned long previousMillis = 0;     // last time data was send
const long interval = 15000;           // data transfer interval

void calDistance();
int deg2rad();
void lcdprint();
void RFIDcheck();

void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
  client.wifiConnection(WIFISSID, PASSWORD);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  lcd.begin();
  lcd.backlight();
  lcd.print("Hello!!!");
  //  lcdprint();
}

void loop()
{
  flag = flag % 2;
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      unsigned long currentMillis = millis();

      RFIDcheck();

      if (flag == 1 && one == true)
      {
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
          Serial.println();
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("lat1=");
          lcd.print(_lat1);
          lcd.setCursor(0, 1);
          lcd.print("lng1=");
          lcd.print(_lng1);
          delay(1000);
        }
        else
        {
          Serial.print(F("INVALID"));
        }
        one = false;
      }

      if (flag == 0 && one == true)
      {
        _lat2 = 12.9716;
        _lng2 = 77.5946;
        sprintf(context, "lat=%.4f$lng=%.4f", _lat2, _lng2);

        client.add("D2", dummy2, context);
        client.sendAll(true);

        Serial.print(F("Location2: "));
        Serial.print(_lat2);
        Serial.print(F(","));
        Serial.print(_lng2);
        one = false;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("lat2=");
        lcd.print(_lat2);
        lcd.setCursor(0, 1);
        lcd.print("lng2=");
        lcd.print(_lng2);
        Serial.println();
        delay(1000);
        calDistance();
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
  dlat = deg2rad(_lat2 - _lat1);
  a = sq(sin(dlat / 2)) + cos(deg2rad(_lat1)) * cos(deg2rad(_lat2)) * sq(sin(dlon / 2));
  c = 2 * atan2( sqrt(a), sqrt(1 - a) );
  d = 6378.1 * c    ;                         //(where R is the radius of the Earth);
  client.add("Dist", d);
  client.sendAll(true);
  Serial.print("Dist :: ");
  Serial.println(d);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:  ");
  lcd.setCursor(0, 1);
  lcd.print(d);
  delay(1000);
}

double deg2rad( double degree)
{
  return (degree * (PI / 180));
}

void lcdprint()
{
  lcd.begin();
  lcd.backlight();
  lcd.print("Hello, world!");
}

void RFIDcheck()
{
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  lcd.setCursor(0, 0);
  lcd.print(content.substring(1));
  Serial.println();
  delay(500);

  if (content.substring(1) == "36 55 C5 F7") //change UID of the card that you want to give access
  {
    flag++;
    one = true;
    Serial.println(" Access Granted ");
    Serial.println(" Welcome Prasad! ");
    lcd.setCursor(0, 1);
    lcd.print(" Access Granted! ");
    delay(1000);
    Serial.println();
    statuss = 1;
  }
  else
  {
    Serial.println(" Access Denied ");
    lcd.setCursor(0, 1);
    lcd.print(" Access Denied!!! ");
    delay(1000);
  }
}
