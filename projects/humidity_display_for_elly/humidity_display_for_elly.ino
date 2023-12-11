#include <LiquidCrystal.h>
#include <SimpleDHT.h>

int pinDHT11 = 4;
SimpleDHT11 dht11(pinDHT11);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
byte temperature = 0;
byte humidity = 0;

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
}

void loop() {
  Serial.println("=================================");
  Serial.println("Sample DHT11...");

  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); 
    Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); 
    Serial.println(SimpleDHTErrDuration(err));
    delay(1000);
    return;
  }

  Serial.print("Temperature: "); 
  Serial.print((int)temperature); 
  Serial.print(" *C, Humidity: "); 
  Serial.print((int)humidity); 
  Serial.println(" H");

  delay(1500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print((int)temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print((int)humidity);
  lcd.print(" %");
}
