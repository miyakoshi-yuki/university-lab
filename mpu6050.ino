#include "mpu6050.h"
#include <Wire.h>

void mpu6050_Initialize(){
// 初回の読み出し
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(MPU6050_PWR_MGMT_1);  //MPU6050_PWR_MGMT_1レジスタの設定
  Wire.write(0x00);
  Wire.endTransmission();
}

int16_t axRaw, ayRaw, azRaw, gxRaw, gyRaw, gzRaw, Temperature;
float acc_x,acc_y,acc_z,gyro_x,gyro_y,gyro_z;

void getMpu6050Data() {
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
  acc_x = axRaw / 16384.0;  //FS_SEL_0 16,384 LSB / g
  acc_y = ayRaw / 16384.0;
  acc_z = azRaw / 16384.0;

  // 角速度値を分解能で割って角速度(degrees per sec)に変換する
  gyro_x = (float)gxRaw / 131;//FS_SEL_0 131 LSB / (°/s)
  gyro_y = (float)gyRaw / 131;
  gyro_z = (float)gzRaw / 131;
}