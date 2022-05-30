#include "mpu6050.h"
#include "pattern_generator.h"
#include "stepper.h"
#include <Wire.h>

// デバイス初期化時に実行される
void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  delay(1000);
  // mpu6050_Initialize();

}
extern float acc_x,acc_y,acc_z,gyro_x,gyro_y,gyro_z;
extern int motorPIN_output[0]

void loop() {
  // getMpu6050Data();
  // spin();
  turnStepperMotor(1,1,0);
  
  Serial.println(motorPIN_output[0]);

  Serial.println(acc_x);
  Serial.println("A");
}

//   if(acc_x > 0){
//     turnStepperMotor(1,1,0);
//   }else{
//     turnStepperMotor(1,0,0);
//   }

//   if(acc_y > 0){
//     turnStepperMotor(2,1,1);
//   }else{
//     turnStepperMotor(2,0,1);
//   }

//   if(acc_z > 0){
//     turnStepperMotor(3,1,2);
//   }else{
//     turnStepperMotor(3,0,2);
//   }

// digitalWrite(motorPIN_arr[0][0],motorPIN_output[0][0]);
// digitalWrite(motorPIN_arr[0][1],motorPIN_output[0][1]);
// digitalWrite(motorPIN_arr[0][2],motorPIN_output[0][2]);
// digitalWrite(motorPIN_arr[0][3],motorPIN_output[0][3]);

// digitalWrite(motorPIN_arr[1][0],motorPIN_output[1][0]);
// digitalWrite(motorPIN_arr[1][1],motorPIN_output[1][1]);
// digitalWrite(motorPIN_arr[1][2],motorPIN_output[1][2]);
// digitalWrite(motorPIN_arr[1][3],motorPIN_output[1][3]);

// digitalWrite(motorPIN_arr[2][0],motorPIN_output[2][0]);
// digitalWrite(motorPIN_arr[2][1],motorPIN_output[2][1]);
// digitalWrite(motorPIN_arr[2][2],motorPIN_output[2][2]);
// digitalWrite(motorPIN_arr[2][3],motorPIN_output[2][3]);