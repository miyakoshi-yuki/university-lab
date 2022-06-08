#include "mpu6050.h"
#include "pattern_generator.h"
#include <Wire.h>
#include "AX12A.h"
#include <Adafruit_GFX.h>     //ダウンロードしたライブラリをインクルード
#include <Adafruit_SSD1306.h>

#define DirectionPin   (2u)
#define BaudRate      (1000000ul)
#define ID        (6u)

int n = 0;    //カウントする変数nを定義
int Temperature,Voltage,Position; 
int reg = 0;

Adafruit_SSD1306 display(-1);

// デバイス初期化時に実行される
void setup() {
  Wire.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  delay(1000);
  mpu6050_Initialize();
  
  ax12a.begin(BaudRate, DirectionPin, &Serial);

}

void loop(){

  reg = ax12a.readRegister(ID, AX_PRESENT_LOAD_L, 2);
  
//  spin();
  mpu6050_i2c();

  float b = getMpu6050Data(1);
  
  ax12a.ledStatus(ID, ON);
  delay(1000);
  ax12a.ledStatus(ID, OFF);
  delay(1000);

  ax12a.move(ID,random(200,800));

  display.clearDisplay();    //ディスプレイをクリア
  display.setTextSize(1);    //文字サイズを設定
  display.setTextColor(WHITE);    //文字色を設定
  display.setCursor(0, 0);    //文字の開始位置を設定
  display.print(reg);    //変数nをディスプレイ出力するよう設定
  display.display();    //上記条件でディスプレイ表示
  delay(2000);    //１秒間待つ
  n++;    //nに１を足す
}
