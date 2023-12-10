int LED_1 = 6; 
int LED_2 =  5 ; 
int LED_3 =  3 ; 
int LED_4 =  9; 

int Fadeschritte = 50;  


int Helligkeit = 0;  

void setup()  
{
}
void loop() 
{
  analogWrite(LED_1, Helligkeit);
  delay(100);
  analogWrite(LED_2, Helligkeit);
  delay(100);
  analogWrite(LED_3, Helligkeit);
  delay(100);
  analogWrite(LED_4, Helligkeit);
  delay(100);
  Helligkeit = Helligkeit + Fadeschritte;    
  delay(50); 
  if (Helligkeit == 0 || Helligkeit == 255) 
  {
    Fadeschritte = -Fadeschritte;  
  }

}  