#include <RTClib.h>
#include <DHT.h>
#include <SD.h>
#include <SPI.h>

RTC_DS1307 rtc;
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

File myFile;
const int chipSelect = 4;
const int noCardPin = 3;
const long logInterval = 10 * 60* 1000;
unsigned long previousLogMillis = 0;
unsigned long checkCardMillis = 0;
const long checkCardInterval = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(noCardPin, OUTPUT);
  initializeRTC();
  initializeDHT();
  if (SD.begin(chipSelect)) {
    digitalWrite(noCardPin, LOW);
  } else {
    digitalWrite(noCardPin, HIGH);
    while (1);
  }
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousLogMillis >= logInterval) {
    DateTime now = rtc.now();
    if (SD.begin(chipSelect)) {
      logDataToSD(now, dht.readTemperature(), dht.readHumidity());
    } else {
      digitalWrite(noCardPin, HIGH);
    }
    previousLogMillis = currentMillis;
  }
  if (currentMillis - checkCardMillis >= checkCardInterval) {
    checkCardStatus();
    checkCardMillis = currentMillis;
  }
}

void checkCardStatus() {
  if (SD.begin(chipSelect)) {
    digitalWrite(noCardPin, LOW);
  } else {
    digitalWrite(noCardPin, HIGH);
  }
}

void initializeDHT() {
  dht.begin();
  delay(1000);
}

void initializeRTC() {
  if (!rtc.begin()) {
    while (1);
  }
  if (!rtc.isrunning()) {
  }
}

void logDataToSD(DateTime now, float temperature, float humidity) {
  myFile = SD.open("DHT11Log.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(now.timestamp());
    myFile.print(",");
    myFile.print("");
    myFile.print(" Temp in C: ");
    myFile.print(temperature);
    myFile.print(",");
    myFile.print("");
    myFile.print(" Humi in %: ");
    myFile.println(humidity);
    myFile.close();
    digitalWrite(noCardPin, LOW);
  } else {
    Serial.println("Error opening DHT11Log.txt");
  }
}