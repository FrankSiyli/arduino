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

unsigned long previousMillis = 0;
const long interval = 2000;

void initializeDHT() {
  Serial.println("Initializing DHT sensor...");
  dht.begin();
  delay(1000);  
  Serial.println("Successfully initialized DHT sensor");
  delay(100);
}

void setup() {
  Serial.begin(9600);
  initializeRTC();
  initializeLCD();
  initializeDHT();
  initializeSD();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    DateTime now = rtc.now();
    int humidity = dht.readHumidity();
    int temperature = dht.readTemperature();

    displayTemperatureAndHumidity(temperature, humidity);

    if (isValidSensorData(temperature, humidity)) {
      logDataToSD(now, temperature, humidity);
      printDataToSerial(now, temperature, humidity);
    }
  }
}

void initializeRTC() {
  Serial.println("Initializing RTC DS1307...");
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Adjust time if needed
  }
  Serial.println("Successfully running RTC DS1307");
  delay(100);
}

void initializeLCD() {
  lcd.begin(16, 2);
}

void initializeSD() {
  Serial.println("Initializing Micro SD Card...");
  delay(100);
  if (!SD.begin(chipSelect)) {
    Serial.println("Initialization failed!");
    while (1);
  }
  Serial.println("Successfully Initializing Micro SD Card");
  Serial.println();
  delay(100);
}

void displayTemperatureAndHumidity(int temperature, int humidity) {
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

bool isValidSensorData(int temperature, int humidity) {
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read Data from DHT sensor!");
    delay(500);
    return false;
  }
  return true;
}

void logDataToSD(DateTime now, int temperature, int humidity) {
  if (now.second() % 5 == 0) {
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
      Serial.println("----");
      Serial.println();
    } else {
      Serial.println("Error opening DHT11Log.txt");
    }
  }
}

void printDataToSerial(DateTime now, int temperature, int humidity) {
  Serial.println("----");
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.print(" | Humidity : ");
  Serial.println(humidity);
  Serial.println();
}
