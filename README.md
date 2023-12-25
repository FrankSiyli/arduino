# arduino
## Datalogger // Temperature and humidity to Lcd and Sd card 
Arduino Uno || Nano
16x2Lcd, Ds1307Rtc, Dht11, MicroSdCardAdapter

#Lcd
Lcd VSS -> Arduino GND
Lcd VDD -> Arduino 5V
Lcd V0 -> Arduino Potentiometer for Lcd contrast 
Lcd RS -> Arduino D10
Lcd RW -> Arduino GND
Lcd E -> Arduino D9
Lcd D4 -> Arduino D8
Lcd D5 -> Arduino D7
Lcd D6 -> Arduino D6
Lcd D7 -> Arduino D5
Lcd A -> Arduino 5V
Lcd K -> Arduino GND

# 10k Potentiometer
Lcd V0
5V
GND

#DHT11
+ -> 5V
- -> GND
out -> Aruino D2

#Rtc DS1307
GND -> GND
VCC -> 5V
SDA -> Arduino A4
SCL -> Arduino A5

#SD card adapter
GND -> GND
VCC -> 5V
MISO -> Arduino D12
MOSI -> Arduino D11
SCK -> Arduino D13
CS -> Arduino D4





