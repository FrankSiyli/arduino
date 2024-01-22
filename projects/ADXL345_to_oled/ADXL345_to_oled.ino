#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1 
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define HISTORY_SIZE 80 // Number of historical data points to display

float history[HISTORY_SIZE]; // Array to store historical data
int historyIndex = 0; // Index to keep track of the current position in the history array

int ADXL345 = 0x53;

float X_out;  // X-axis output

void setup() {
  Serial.begin(9600); 
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(1000); 

  display.display();  
  display.clearDisplay();
  
  Wire.beginTransmission(ADXL345); 
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable 
  Wire.endTransmission();
  delay(10);
}

void loop() {
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); 
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 2, true); 
  X_out = (Wire.read() | Wire.read() << 8) / 256.0; 

  for (int i = HISTORY_SIZE - 1; i > 0; i--) {
    history[i] = history[i - 1];
  }

  history[0] = X_out;

  display.clearDisplay();
  drawGraph();
  display.display();

 

  delay(10); 
}

void drawGraph() {
  int graphWidth = SCREEN_WIDTH - 10;
  int graphHeight = SCREEN_HEIGHT - 10;
  int middleY = graphHeight / 2;

  for (int i = 0; i < HISTORY_SIZE - 1; i++) {
    int xPos1 = map(i, 0, HISTORY_SIZE, 0, graphWidth);
   // int yPos1 = map(history[i] * 100, -100, 100, middleY, -middleY);  Full sensor range
        int yPos1 = map(history[i] * 100, -1, 1, middleY, -middleY);  // Sensor range -0.10 - 0.10


    int xPos2 = map(i + 1, 0, HISTORY_SIZE, 0, graphWidth);
    // int yPos2 = map(history[i + 1] * 100, -100, 100, middleY, -middleY);  Full sensor range
        int yPos2 = map(history[i + 1] * 100, -1, 1, middleY, -middleY);  // Sensor range -0.10 - 0.10


    display.drawLine(xPos1 + 5, middleY + yPos1 + 5, xPos2 + 5, middleY + yPos2 + 5, SSD1306_WHITE);
  }
}



