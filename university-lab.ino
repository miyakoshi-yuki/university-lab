#include "mpu6050.h"
#include "pattern_generator.h"
#include <Wire.h>
#include "AX12A.h"
#include "U8glib.h"
#include "oled.h"
#include "voice_lsi.h"

#define DirectionPin   (2u)
#define BaudRate      (1000000ul)
#define ID        (3u)


int n = 0;    //カウントする変数nを定義
int Temperature,Voltage,Position; 
int reg = 0;
float b=0;
byte disp_x;
byte disp_y;

void setup() {
  Wire.begin();
  startupScreen();
  mpu6050_Initialize();
  
  ax12a.begin(BaudRate, DirectionPin, &Serial);

}

void loop(){

  reg = ax12a.readRegister(ID, AX_PRESENT_LOAD_L, 2);
  
  mpu6050_i2c();

  b = getMpu6050Data(1);
  
  ax12a.ledStatus(ID, ON);
  delay(1000);
  ax12a.ledStatus(ID, OFF);
  delay(1000);

  ax12a.move(ID,random(200,800));

  talkLsi();

  delay(1500);
  

}
