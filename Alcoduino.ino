#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4

int timeToWarm = 5;
/* For actual use, set wait time to 500 */
unsigned long time;

const int analogPin = 0;
int val = 0;
int buttonState = 0;  

Adafruit_SSD1306 display(OLED_RESET);

void setup()  {              
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 display.clearDisplay();
}


void loop() {  
  delay(100);
  
  val = readAlcohol();
  printTitle();
  printWarming();
  
  time = millis() / 1000;
  
  if (time <= timeToWarm) {
    time = map(time, 0, timeToWarm, 0, 100);
    display.drawRoundRect(0, 10, 128, 7, 4, WHITE); //Empty Bar
    display.fillRoundRect(0, 10, (time * 1.2), 7, 4, WHITE);
  }
  else {
     printNewTitle();
     printAlcohol(val);
     printAlcoholMeter(val);  
  }
  
  display.display();
}

void printNewTitle() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5,0);
  display.println("READY");
}

void printTitle() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5,0);
  display.println("Breathalyser");
}

void printWarming() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5,20);
  display.println("Warming up...");
}

void printAlcohol(int value) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5,20);
  display.println(val);
}

void printAlcoholMeter(int value) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.setCursor(85,0);
  display.println("H");
  display.drawFastVLine(87, 9, 13, WHITE);
  display.setCursor(85,24);
  display.println("L");
  
  display.drawRect(100, 0, 25, 8, WHITE);
  display.drawRect(100, 8, 25, 8, WHITE);
  display.drawRect(100, 16, 25, 8, WHITE);
  display.drawRect(100, 24, 25, 8, WHITE);
  
  if(value>= 95 && value<100) {
    display.fillRect(100, 24, 25, 8, WHITE); /* New */
  }
  
  if (value>=100 && value<110) {
    display.fillRect(100, 16, 25, 16, WHITE); /* New */
  }
  
  if (value>=770 && value<800) {
    display.fillRect(100, 8, 25, 24, WHITE); /* New */
  }

  if(value >= 800) {
    display.fillRect(100, 0, 25, 32, WHITE); /* New */
  }
}
 
int readAlcohol(){
  int val = 0;
  int val1;
  int val2;
  int val3; 


  display.clearDisplay();
  val1 = analogRead(analogPin); 
  delay(10);
  val2 = analogRead(analogPin); 
  delay(10);
  val3 = analogRead(analogPin);
  
  val = (val1 + val2 + val3) / 3;
  return val;
}
