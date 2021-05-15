/*
   This sketch demonstrates multiple I2C Slaves with ESP32
   Here, the slaves are OLED Screen and MPU6050
   The ESP will fetch data from MPU6050 and write to OLED Screen in one loop
   Both have different I2C Addresses

   Library for OLED Display Interface can be found here: https://github.com/ThingPulse/esp8266-oled-ssd1306

   Author: Yash Sanghvi
*/

#include "SSD1306.h"
#include<Wire.h>


//OLED related variables
#define OLED_ADDR   0x3c
#define OLED_SDA    21
#define OLED_SCL    22

//MPU6050 related variables
#define MPU_ADDR 0x68  // I2C address of the MPU-6050
#define MPU_SDA 21
#define MPU_SCL 22
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ, AcX_H, AcX_L, AcX_2;

SSD1306  display(OLED_ADDR, OLED_SDA, OLED_SCL);

void showOLEDMessage(String line1, String line2, String line3)
{
  display.init();                                                           // clears screen
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, line1);                                          // adds to buffer
  display.drawString(0, 20, line2);
  display.drawString(0, 40, line3);
  display.display();                                                        // displays content in buffer
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin(MPU_SDA, MPU_SCL, 100000); // sda, scl, freq
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  Serial.begin(115200);
  Serial.println("Setup complete...");
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU_ADDR);
  Wire.requestFrom(MPU_ADDR, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)


  //Serial.print("AcX = ");
  Serial.print(AcX); Serial.print(" , ");
  //Serial.print(" | AcY = ");
  Serial.print(AcY); Serial.print(" , ");
  // Serial.print(" | AcZ = ");
  Serial.print(AcZ);
  Serial.print(" , ");


  Serial.print(GyX); Serial.print(" , ");
  //Serial.print(" | AcY = ");
  Serial.print(GyY); Serial.print(" , ");
  // Serial.print(" | AcZ = ");
  Serial.print(GyZ); Serial.println(" , ");

  String AcclnX = "X: " + String(AcX) + ",";
  String AcclnY = "Y: " + String(AcY) + ",";
  String AcclnZ = "Z: " + String(AcZ);
  showOLEDMessage(AcclnX,AcclnY,AcclnZ);
  delay(100);

}
