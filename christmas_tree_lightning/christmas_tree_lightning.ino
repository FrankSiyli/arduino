int LED = 6; 

int Fadeschritte = 1;  


int Helligkeit = 0;  

void setup()  
{
}
void loop() 
{
  
  analogWrite(LED, Helligkeit);
 
  Helligkeit = Helligkeit + Fadeschritte;    
  delay(50);
  
  if (Helligkeit == 0 || Helligkeit == 255) 
  {
    Fadeschritte = -Fadeschritte;  
  }

}  