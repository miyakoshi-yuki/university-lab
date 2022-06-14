#include "voice_lsi.h"
#include <Arduino.h>
#include <Wire.h>
 
// デバイスアドレス(スレーブ)
uint8_t DEVICE_ADDRESS = 0x2E;
 
// メッセージ配列
String s[] = {
  "teizinanode.kaerimasu.\r",
  "konnitiwa.\r",    // こんにちは。
//  "ohayo-\r",        // おはよー
  "watashihanisokuhoko-robottodesu.\r"}; // お腹すいたー。
 
// メッセージ数
int count = 3;
 
// メッセージのカウンタ用
int index = 0;
 
//void setup() {
//  // マスタとしてI2Cバスに接続する
//  Wire.begin();
//}
 
void talkLsi() {
  // メッセージをデバイスに送信
  Wire.beginTransmission(DEVICE_ADDRESS);
    for (int i = 0; i < s[index].length(); i++) {
      Wire.write(s[index][i]);
    }
  Wire.endTransmission();
 
  // 次のメッセージを発声できるまでループする
  while(true){
    // デバイスへ1byteのレジスタデータを要求する
    Wire.requestFrom(DEVICE_ADDRESS, 1);    
 
    // 「>」(次の発声が準備OK)ならばループを抜ける
    while(Wire.available() == 0) {}
    uint8_t c = Wire.read(); 
    if(c == '>')  break;
//    delay(10);
  }
 
  index++;
  
  if(count <= index){
    index = 0;
  }
}
