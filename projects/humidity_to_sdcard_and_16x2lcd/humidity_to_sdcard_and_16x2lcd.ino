#include <RTClib.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <SD.h>
#include <SPI.h>

RTC_DS1307 rtc;
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(10, 9, 8, 7, 6, 5);

File myFile;
const int chipSelect = 4;
const long displayInterval = 5 * 1000;  
const long logInterval = 10 * 60 * 1000;      
unsigned long previousDisplayMillis = 0;
unsigned long previousLogMillis = 0;

void setup() {
  Serial.begin(9600);
  initializeRTC();
  initializeLCD();
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

void initializeLCD() {
  lcd.begin(16, 2);
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
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temperatur:");
      lcd.setCursor(13, 0);
      lcd.print(temperature);
      lcd.print("C");
      lcd.setCursor(0, 1);
      lcd.print("Luftfeuchte:");
      lcd.setCursor(13, 1);
      lcd.print(humidity);
      lcd.print("%");
    }
  } else {
    displayNoCard();
  }
}

void displayNoCard() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Keine SD Karte");
  lcd.setCursor(0, 1);
  lcd.print("erkannt");
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