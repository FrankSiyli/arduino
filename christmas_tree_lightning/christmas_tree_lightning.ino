int LED_1 = 6; 
int LED_2 =  5 ; 
int LED_3 =  3 ; 
int LED_4 =  9; 

int Fadeschritte = 5;  


int Helligkeit = 0;  

void setup()  
{
}
void loop() 
{
  analogWrite(LED_1, Helligkeit);
  analogWrite(LED_2, Helligkeit);
  analogWrite(LED_3, Helligkeit);
  analogWrite(LED_4, Helligkeit);
  Helligkeit = Helligkeit + Fadeschritte;    
  delay(50); 
  if (Helligkeit == 0 || Helligkeit == 255) 
  {
    Fadeschritte = -Fadeschritte;  
  }

}  