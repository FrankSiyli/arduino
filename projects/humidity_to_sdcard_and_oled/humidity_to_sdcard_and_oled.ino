#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <SD.h>
#include <SPI.h>

RTC_DS1307 rtc;
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define XPOS   0 
#define YPOS   1
#define DELTAY 2

File myFile;
const int chipSelect = 4;
const long displayInterval = 5 * 1000;
const long logInterval = 10 * 60 * 1000;
unsigned long previousDisplayMillis = 0;
unsigned long previousLogMillis = 0;


#define NUMFLAKES     10 
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

void setup() {
  Serial.begin(9600);
if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
  delay(1000);
  testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); 
  initializeRTC();
  initializeDHT();
  waitForSDCard();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousDisplayMillis >= displayInterval) {
    previousDisplayMillis = currentMillis;
    displayTemperatureAndHumidity();
  }

  if (currentMillis - previousLogMillis >= logInterval) {
    DateTime now = rtc.now();
    int humidity = dht.readHumidity();
    int temperature = dht.readTemperature();
    logDataToSD(now, temperature, humidity);
  }
  previousLogMillis = currentMillis;
}



void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMFLAKES][3];

  for(f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
    Serial.print(F("x: "));
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(F(" y: "));
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(F(" dy: "));
    Serial.println(icons[f][DELTAY], DEC);
  }

  for(;;) { 
    display.clearDisplay(); 
    for(f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    }
    display.display(); 
    delay(200);       
    for(f=0; f< NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      if (icons[f][YPOS] >= display.height()) {
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }}
}


void initializeDHT() {
  dht.begin();
  delay(1000);
}

void initializeRTC() {
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }
}

void initializeOLED() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);  // Pause for 2 seconds
  display.clearDisplay();
  display.display();
}

void waitForSDCard() {
  while (!SD.begin(chipSelect)) {
    displayNoCard();
  }
}

void displayTemperatureAndHumidity() {
  DateTime now = rtc.now();
  int humidity = dht.readHumidity();
  int temperature = dht.readTemperature();

  if (SD.begin(chipSelect)) {
    if (isValidSensorData(temperature, humidity)) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.print("Temperatur: ");
      display.print(temperature);
      display.print("C");
      display.setCursor(0, 10);
      display.print("Luftfeuchte: ");
      display.print(humidity);
      display.print("%");
      display.display();
    }
  } else {
    displayNoCard();
  }
}

void displayNoCard() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Keine SD Karte");
  display.setCursor(0, 10);
  display.print("erkannt");
  display.display();
}

bool isValidSensorData(int temperature, int humidity) {
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read Data from DHT sensor!");
    return false;
  }
  return true;
}

void logDataToSD(DateTime now, int temperature, int humidity) {
  myFile = SD.open("DHT11Log.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(now.day());
    myFile.print("-");
    myFile.print(now.month());
    myFile.print("-");
    myFile.print(now.year());
    myFile.print(",");
    myFile.print(now.hour());
    myFile.print(":");
    myFile.print(now.minute());
    myFile.print(":");
    myFile.print(now.second());
    myFile.print(",");
    myFile.print(temperature);
    myFile.print(",");
    myFile.println(humidity);
    myFile.close();
    Serial.println("Successfully writing Data to Micro SD Card");
  } else {
    Serial.println("Error opening DHT11Log.txt");
  }
}
