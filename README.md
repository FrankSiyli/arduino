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
Pin out -> Arduino D2

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
<br/>
<br/>
<br/>



## Temperature and humidity to OLED display
## Temperature and humidity to SDcard
![IMG_4619](https://github.com/FrankSiyli/arduino/assets/123658730/383d85fe-2b2c-4116-9ee3-30bb6d2c8001)
![IMG_4617](https://github.com/FrankSiyli/arduino/assets/123658730/6ab4d51f-6821-4457-a998-731549b969b8)

Due to limited memory on the Arduino I split the code in OLED logic and RTC/SDcard logic for two Arduinos. Both uses the same DHT11 Sensor.
Communication between the two Arduinos is realized via pins D3

2x Arduino Uno || Nano, OLED SSD1306, Ds1307Rtc, Dht11, MicroSdCardAdapter


### DHT11
VCC -> 5V
<br/>
GND -> GND
<br/>
2x Pin out -> Arduino(RTC logic and OLED logic) D2

### Rtc DS1307
GND -> GND
<br/>
VCC -> 5V
<br/>
SDA -> Arduino(RTC logic)  A4
<br/>
SCL -> Arduino(RTC logic) A5

### SD card adapter
GND -> GND
<br/>
VCC -> 5V
<br/>
MISO -> Arduino(RTC logic) D12
<br/>
MOSI -> Arduino(RTC logic) D11
<br/>
SCK -> Arduino(RTC logic) D13
<br/>
CS -> Arduino(RTC logic) D4

### OLED display

GND -> GND
<br/>
VCC -> 5V
<br/>
SDA -> Arduino(OLED logic)  A4
<br/>
SCL -> Arduino(OLED logic) A5
<br/>


### Arduino(OLED logic) D3 -> Arduino(RTC logic) D3
both Arduinos GND -> GND
<br/>
both Arduinos 5V -> 5V






