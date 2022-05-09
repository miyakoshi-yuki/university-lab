

// void setup(){
  
  
// // Serial.begin(9600);
// }
// void loop(){


// // Serial.println(count);
// // Serial.print(a);
// // Serial.print(b);
// // Serial.print(c);
// // Serial.println(d);

// }
#include <Wire.h>

// MPU-6050のアドレス、レジスタ設定値
#define MPU6050_WHO_AM_I     0x75  // Read Only
#define MPU6050_PWR_MGMT_1   0x6B  // Read and Write
#define MPU_ADDRESS  0x68
// #define MotorPIN1 2 // 青
// #define MotorPIN2 3 // ピンク
// #define MotorPIN3 4 // 黄
// #define MotorPIN4 5 // オレンジ

char motorPIN_arr[3][4] = {
  {2,3,4,5},
  {6,7,8,9},
  {10,11,12,13}
};

bool motorPIN_output[3][4] = {};

// デバイス初期化時に実行される
void setup() {
  pinMode(motorPIN_arr[0][0], OUTPUT);  // デジタルピンを出力に設定
  pinMode(motorPIN_arr[0][1], OUTPUT);
  pinMode(motorPIN_arr[0][2], OUTPUT);
  pinMode(motorPIN_arr[0][3], OUTPUT);

  pinMode(motorPIN_arr[1][0], OUTPUT);  // デジタルピンを出力に設定
  pinMode(motorPIN_arr[1][1], OUTPUT);
  pinMode(motorPIN_arr[1][2], OUTPUT);
  pinMode(motorPIN_arr[1][3], OUTPUT);

  pinMode(motorPIN_arr[2][0], OUTPUT);  // デジタルピンを出力に設定
  pinMode(motorPIN_arr[2][1], OUTPUT);
  pinMode(motorPIN_arr[2][2], OUTPUT);
  pinMode(motorPIN_arr[2][3], OUTPUT);
  Wire.begin();

  // PCとの通信を開始
  Serial.begin(115200); //115200bps
 
  // 初回の読み出し
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(MPU6050_WHO_AM_I);  //MPU6050_PWR_MGMT_1
  Wire.write(0x00);
  Wire.endTransmission();

  // 動作モードの読み出し
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(MPU6050_PWR_MGMT_1);  //MPU6050_PWR_MGMT_1レジスタの設定
  Wire.write(0x00);
  Wire.endTransmission();
  
}

int16_t axRaw, ayRaw, azRaw, gxRaw, gyRaw, gzRaw, Temperature;
// int16_t maxGx = 0;

void loop() {
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 14, true);
  while (Wire.available() < 14);
//   int16_t axRaw, ayRaw, azRaw, gxRaw, gyRaw, gzRaw, Temperature;

  axRaw = Wire.read() << 8 | Wire.read();
  ayRaw = Wire.read() << 8 | Wire.read();
  azRaw = Wire.read() << 8 | Wire.read();
  Temperature = Wire.read() << 8 | Wire.read();
  gxRaw = Wire.read() << 8 | Wire.read();
  gyRaw = Wire.read() << 8 | Wire.read();
  gzRaw = Wire.read() << 8 | Wire.read();

  // 加速度値を分解能で割って加速度(G)に変換する
  float acc_x = axRaw / 16384.0;  //FS_SEL_0 16,384 LSB / g
  float acc_y = ayRaw / 16384.0;
  float acc_z = azRaw / 16384.0;

  // 角速度値を分解能で割って角速度(degrees per sec)に変換する
//   float gyro_x = gxRaw / 131.0;//FS_SEL_0 131 LSB / (°/s)
//   float gyro_y = gyRaw / 131.0;
//   float gyro_z = gzRaw / 131.0;
//   if(maxGx < gyro_x){
//       maxGx = gyro_x;
//   }
  
  float gyro_x = map(gxRaw / 131.0, 0, 250, 0, 1);//FS_SEL_0 131 LSB / (°/s)
  float gyro_y = map(gyRaw / 131.0, 0, 250, 0, 1);
  float gyro_z = map(gzRaw / 131.0, 0, 250, 0, 1);

  Serial.print(acc_x);  Serial.print(",");
  Serial.print(acc_y);  Serial.print(",");
  Serial.print(acc_z);  Serial.print(",");
 // Serial.print(maxGx); Serial.print(",");
  Serial.print(gyro_x); Serial.print(",");
  Serial.print(gyro_y); Serial.print(",");
  Serial.print(gyro_z); Serial.println("");

  //   for(int i = 0; i<500; i++){
  //   turnStepperMotor(1,0);
  //   delay(20);
  // }
  // for(int i = 0; i<500; i++){
  //   turnStepperMotor(1,1);
  //   delay(20);
  // }

  if(acc_x > 0){
    turnStepperMotor(1,1,0);
  }else{
    turnStepperMotor(1,0,0);
  }

  if(acc_y > 0){
    turnStepperMotor(2,1,1);
  }else{
    turnStepperMotor(2,0,1);
  }

  if(acc_z > 0){
    turnStepperMotor(3,1,2);
  }else{
    turnStepperMotor(3,0,2);
  // delay(800);
  }

digitalWrite(motorPIN_arr[0][0],motorPIN_output[0][0]);
digitalWrite(motorPIN_arr[0][1],motorPIN_output[0][1]);
digitalWrite(motorPIN_arr[0][2],motorPIN_output[0][2]);
digitalWrite(motorPIN_arr[0][3],motorPIN_output[0][3]);

digitalWrite(motorPIN_arr[1][0],motorPIN_output[1][0]);
digitalWrite(motorPIN_arr[1][1],motorPIN_output[1][1]);
digitalWrite(motorPIN_arr[1][2],motorPIN_output[1][2]);
digitalWrite(motorPIN_arr[1][3],motorPIN_output[1][3]);

digitalWrite(motorPIN_arr[2][0],motorPIN_output[2][0]);
digitalWrite(motorPIN_arr[2][1],motorPIN_output[2][1]);
digitalWrite(motorPIN_arr[2][2],motorPIN_output[2][2]);
digitalWrite(motorPIN_arr[2][3],motorPIN_output[2][3]);
}