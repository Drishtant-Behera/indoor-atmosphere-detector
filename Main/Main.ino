// credit to robojax for helping me out with the display for the project.

// all libraries used for project
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// vars for display
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 32
#define LOGO16_GLCD_WIDTH  128 
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

const int sensorPin = A0; 
const int buzzerPin = 9;

void setup() {

  Serial.begin(9600); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();
  delay(2000);
  display.clearDisplay(); 
}

void loop() {

  int sensorValue = analogRead(sensorPin);
  // change the bellow variable to whatever fits your situation
  const float dangerThreshold = 0.2;


  float gas_conc = sensorValue * (5.0 / 1024.0); 

  // if the gas concentration is more or the same as the danger threshold then alert!
  if (gas_conc >= dangerThreshold) {
    Serial.println("Danger!");
    tone(buzzerPin, 440);
    Serial.print("Gas Conc: ");
    Serial.print(gas_conc);
    
  } 
  else {

    Serial.print("Gas Conc: ");
    Serial.println(gas_conc);
    
    noTone(buzzerPin);
  }
  // setting up display
  String vString =  String(gas_conc, 3);
  display.clearDisplay();
  robojaxText("Gas Conc:          ", 4, 3, 0.5, false);
  robojaxText(vString, 72, 3, 1, false);
  display.drawLine(1, 37, 100, 37, WHITE);
  display.drawRect(1, 1, 126,31, WHITE);
  display.display();
  delay(100);

  
}

void robojaxText(String text, int x, int y,int size, boolean d) {

  display.setTextSize(size);
  display.setTextColor(WHITE);
  display.setCursor(x,y);
  display.println(text);
  if(d){
    display.display();
  }

}



