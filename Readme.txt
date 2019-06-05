hi there!

UID (blue tag):     36 55 C5 F7
UID (White tag):    30 B0 C7 3A 
UID (White tag):    91 9F E5 2F
















References:

RC522:      https://www.instructables.com/id/MFRC522-RFID-Reader-Interfaced-With-NodeMCU/

RC522               NodeMCU
SS(1)               D8(gpio15)             1,2,5,6,7
SCK(2)              D5(gpio14)
MOSI(3)             D7(gpio13)
MISO(4)             D6(gpio12)
IRQ(5)              ~
GND(6)              GND
RST(7)              D1(gpio5)----(NC)
3.3v(8)             +3.3V

I2C LCD:   https://www.instructables.com/id/I2C-LCD-on-NodeMCU-V2-With-Arduino-IDE/
library link:   https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
LCD                 NodeMCU
VCC                 +3.3v
GND                 GND         
SDA                 D2
SCL                 D1

GPS:    https://circuitdigest.com/microcontroller-projects/interfacing-gps-with-nodemcu-esp12

GPS Pins            NodeMCU
VCC                 +3.3V
RX                  D4
TX                  D3
GND                 GND

for finding distance between two lat and long
https://andrew.hedges.name/experiments/haversine/
dlon = lon2 - lon1 
dlat = lat2 - lat1 
a = (sin(dlat/2))^2 + cos(lat1) * cos(lat2) * (sin(dlon/2))^2 
c = 2 * atan2( sqrt(a), sqrt(1-a) ) 
d = R * c (where R is the radius of the Earth)