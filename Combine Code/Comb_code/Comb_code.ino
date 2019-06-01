#include "GPSdata.h"
#include "ubidotsDump.h"

void setup()
{
  Serial.begin(9600);

}

void loop()
{

  getGPSdata();
  delay(100);
  if (flag == 1)
  {
    uploadData();
  }
  //  delay(1000);
}
