/*
 * This sketch demonstrates multiple I2C Slaves with ESP32
 * Here, the slaves are OLED Screen and MPU6050
 * The ESP will fetch data from MPU6050 and write to OLED Screen in one loop
 * Both have different I2C Addresses
 * 
 * Library for OLED Display Interface can be found here: https://github.com/ThingPulse/esp8266-oled-ssd1306
 * 
 * Author: Yash Sanghvi
 */

#include "SSD1306.h"
#include<Wire.h>
#include "esp_system.h"


//OLED related variables
#define OLED_ADDR   0x3c
#define OLED_SDA    21//4     //21 is for the TTGO board with SD Card, 4 for the board without it
#define OLED_SCL    22//15    //22 is for the TTGO board with SD Card, 15 for the board without it
#define OLED_RST    16

//MPU6050 related variables
const int MPU=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ, AcX_H, AcX_L, AcX_2;

SSD1306  display(OLED_ADDR, OLED_SDA, OLED_SCL); 

void showOLEDMessage(String line1, String line2, String line3)
{
  display.init();                                                        // clears screen
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, line1);                                          // adds to buffer
  display.drawString(0, 20, line2);
  display.drawString(0, 40, line3);
  display.display();                                                     // displays content in buffer
}

void initOLED()
{
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);
}


void setup() {
  // put your setup code here, to run once:
  Wire.setClock(100000);
  Wire.begin(21, 22, 100000); // sda, scl, freq
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(115200);
  Serial.println("Setup complete...");
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU);
  Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  GyY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
 
       
    //Serial.print("AcX = "); 
   Serial.print(AcX);Serial.print(" , ");
    //Serial.print(" | AcY = "); 
   Serial.print(AcY);Serial.print(" , ");
   // Serial.print(" | AcZ = "); 
   Serial.print(AcZ);
   Serial.print(" , ");
  
  
     Serial.print(GyX);Serial.print(" , ");
    //Serial.print(" | AcY = "); 
    Serial.print(GyY);Serial.print(" , ");
   // Serial.print(" | AcZ = "); 
    Serial.print(GyZ);Serial.println(" , ");

    String Accln = String(AcX) + "," + String(AcY) + "," + String(AcZ);
    showOLEDMessage("X, Y, Z Accln",Accln,"");
    delay(100);

}
