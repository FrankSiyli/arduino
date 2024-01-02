#include <Wire.h>
#include <RTClib.h>
#include <DHT.h>
#include <SD.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>

RTC_DS1307 rtc;
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define SCREEN_ADDRESS 0x3C
SSD1306AsciiWire display;

const int chipSelect = 4;
const long displayInterval = 5 * 1000;
const long logInterval = 10 * 60 * 1000;
unsigned long previousDisplayMillis = 0;
unsigned long previousLogMillis = 0;

File myFile;

void setup() {
  Serial.begin(9600);

  initializeRTC();
  initializeOLED();
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

void initializeRTC() {
  Wire.begin();
  Wire.beginTransmission(0x68); // Set the I2C address for the RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }
  Wire.endTransmission(); // End the I2C transmission
}

void initializeOLED() {
  Wire.begin();
  display.begin(&Adafruit128x64, SCREEN_ADDRESS);
  display.setFont(Adafruit5x7); // Set font (optional)
  delay(2000);
  display.clear();
display.displayAll();}





void initializeDHT() {
  dht.begin();
  delay(1000);
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

  if (isValidSensorData(temperature, humidity)) {
    display.clear();
    display.setCursor(0, 0);
    display.print("Temperature: ");
    display.print(temperature);
    display.print("C");
    display.setCursor(0, 1);
    display.print("Humidity: ");
    display.print(humidity);
    display.print("%");
display.displayAll();  }
}

void displayNoCard() {
  display.clear();
  display.setCursor(0, 0);
  display.print("No SD Card Detected");
display.displayAll();}


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
