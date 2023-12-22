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
 
 int Temp = dht.readTemperature();
 
  lcd.setCursor(0,  0);
   lcd.print("Temperatur:");
  lcd.setCursor(13, 0);
    lcd.print(Temp);
     lcd.print("C");
     

  int Humid = dht.readHumidity();
  
  lcd.setCursor(0, 1);
   lcd.print("Luftfeuchte:");
     lcd.setCursor(13, 1);
    lcd.print(Humid);
     lcd.print("%");
               delay(2000);

}
