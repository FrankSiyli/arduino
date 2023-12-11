#include <IRremote.h>

int RECV_PIN = 12;

int LED_1 = 6;
int LED_2 = 5;
int LED_3 = 10;
int LED_4 = 9;

int Fadeschritte = 50;
int Helligkeit = 0;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); 
  
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
}

void fadeLEDs() {
  analogWrite(LED_1, Helligkeit);
    delay(500);
  analogWrite(LED_2, Helligkeit);
  delay(500);
  analogWrite(LED_3, Helligkeit);
  delay(500);
  analogWrite(LED_4, Helligkeit);
  delay(500);
  Helligkeit = Helligkeit + Fadeschritte;    
  delay(5);
  if (Helligkeit == 0 || Helligkeit == 255) {
    Fadeschritte = -Fadeschritte;  
  }
}

void toggleLEDs() {
  if (digitalRead(LED_1) == HIGH) {
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
  } else {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
  }
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    if (results.value == 0xFFFFFFFF) {
      toggleLEDs();
    }

    irrecv.resume(); 
  }

  if (digitalRead(LED_1) == HIGH) {
    fadeLEDs();
  }
}
