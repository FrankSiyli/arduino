#include <LiquidCrystal.h>
#include <DHT.h>
int pin = 6;
int  type = DHT11;
DHT dht (pin, type);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void  setup() {
  lcd.begin(16, 2);
   dht.begin();
}

void loop() {
 
 float Temp = dht.readTemperature();
  lcd.setCursor(0,  0);
   lcd.print("Temp:");
    lcd.print(Temp);
     lcd.print("C");
     

  float Humid = dht.readHumidity();
  

  lcd.setCursor(0, 2);
   lcd.print("Humid:");
    lcd.print(Humid);
     lcd.print("%");
               delay(2000);

}
