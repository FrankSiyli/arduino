# arduino
## Datalogger // Temperature and humidity to Lcd and Sd card 
Arduino Uno || Nano, 16x2Lcd, Ds1307Rtc, Dht11, MicroSdCardAdapter

### Lcd
Lcd VSS -> Arduino GND
<br/>
Lcd VDD -> Arduino 5V
<br/>
Lcd V0 -> Arduino Potentiometer for Lcd contrast 
<br/>
Lcd RS -> Arduino D10
<br/>
Lcd RW -> Arduino GND
<br/>
Lcd E -> Arduino D9
<br/>
Lcd D4 -> Arduino D8
<br/>
Lcd D5 -> Arduino D7
<br/>
Lcd D6 -> Arduino D6
<br/>
Lcd D7 -> Arduino D5
<br/>
Lcd A -> Arduino 5V
<br/>
Lcd K -> Arduino GND

### 10k Potentiometer
Lcd V0
<br/>
5V
<br/>
GND

### DHT11
VCC -> 5V
<br/>
GND -> GND
<br/>
Pin out -> Aruino D2

### Rtc DS1307
GND -> GND
<br/>
VCC -> 5V
<br/>
SDA -> Arduino A4
<br/>
SCL -> Arduino A5

### SD card adapter
GND -> GND
<br/>
VCC -> 5V
<br/>
MISO -> Arduino D12
<br/>
MOSI -> Arduino D11
<br/>
SCK -> Arduino D13
<br/>
CS -> Arduino D4






