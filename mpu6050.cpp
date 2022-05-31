#include "mpu6050.h"
#include <Wire.h>

static int16_t axRaw, ayRaw, azRaw, gxRaw, gyRaw, gzRaw, Temperature;
// static float acc_x,acc_y,acc_z,gyro_x,gyro_y,gyro_z;
static float Data_arr[] = {0,0,0,0,0,0}; //acc_x,acc_y,acc_z,gyro_x,gyro_y,gyro_z;

float getMpu6050Data(char dataName){
  return  Data_arr[dataName];
}

void mpu6050_Initialize(){
// 初回の読み出し
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(MPU6050_PWR_MGMT_1);  //MPU6050_PWR_MGMT_1レジスタの設定
  Wire.write(0x00);
  Wire.endTransmission();
}

void mpu6050_i2c() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 14, true);
  while (Wire.available() < 14);
  
  axRaw = Wire.read() << 8 | Wire.read();
  ayRaw = Wire.read() << 8 | Wire.read();
  azRaw = Wire.read() << 8 | Wire.read();
  Temperature = Wire.read() << 8 | Wire.read();
  gxRaw = Wire.read() << 8 | Wire.read();
  gyRaw = Wire.read() << 8 | Wire.read();
  gzRaw = Wire.read() << 8 | Wire.read();

  // 加速度値を分解能で割って加速度(G)に変換する
  Data_arr[0] = axRaw / 16384.0;  //FS_SEL_0 16,384 LSB / g
  Data_arr[1] = ayRaw / 16384.0;
  Data_arr[2] = azRaw / 16384.0;

  // 角速度値を分解能で割って角速度(degrees per sec)に変換する
  Data_arr[3] = (float)gxRaw / 131;//FS_SEL_0 131 LSB / (°/s)
  Data_arr[4] = (float)gyRaw / 131;
  Data_arr[5] = (float)gzRaw / 131;
}