#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int countdown = 60;
boolean countdownReachedZero = false;

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for (;;);
  }
  display.display();
  delay(1000);
  initializeDHT();
}

void loop() {
  int humidity = dht.readHumidity();
  int temperature = dht.readTemperature();

  display.clearDisplay();
  display.setTextSize(1, 2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Temperatur: ");
  display.print(temperature);
  display.println(" C");
  display.setCursor(0, 25);
  display.print("Luftfeuchte: ");
  display.print(humidity);
  display.println(" %");
  display.setCursor(0, 50);
  display.setTextSize(1);
  display.print("Datalog in: ");
  
  if (countdownReachedZero) {
    display.print("writing");
    countdownReachedZero = false;
    delay(1000);
  } else {
    display.print(countdown);
      display.println(" s");
    countdown--;
    if (countdown < 1) {
      countdown = 60;
      countdownReachedZero = true; 
    }
  }
  
  display.display();
  delay(1000);
}

void initializeDHT() {
  dht.begin();
  delay(1000);
}
