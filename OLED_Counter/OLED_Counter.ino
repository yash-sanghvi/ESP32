
#include "SSD1306Wire.h"

//OLED related variables
#define OLED_ADDR   0x3c
#define OLED_SDA    21//4     //TTGO board without SD Card has OLED SDA connected to pin 4 of ESP32
#define OLED_SCL    22//15    //TTGO board without SD Card has OLED SCL connected to pin 15 of ESP32
#define OLED_RST    16        //Optional, TTGO board contains OLED_RST connected to pin 16 of ESP32


SSD1306Wire  display(OLED_ADDR, OLED_SDA, OLED_SCL); 
int counter = 0;

void initOLED()
{
  pinMode(OLED_RST, OUTPUT);

  //Give a low to high pulse to the OLED display to reset it
  //This is optional and not required for OLED modules not containing a reset pin
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);
}


void showOLEDMessage(String line1, String line2, String line3)
{
  display.init();                                                        // clears screen
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, line1);                                          // adds to buffer
  display.drawString(0, 20, line2);
  display.drawString(0, 40, line3);
  display.display();                                                     // displays content in buffer
}

void setup() {
  // put your setup code here, to run once:
  initOLED();
}

void loop() {
  // put your main code here, to run repeatedly
  showOLEDMessage("Number of seconds is: ", String(counter), "");
  delay(1000);
  counter = counter+1;

}
