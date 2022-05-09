/*
 * File:   steppermotor.ino
 * Author: Yuki Miyakoshi
 */
 
/*
 * ステッピングモーターを回転させる関数
 * turnStepperMotor(char excitation, bool isForward, char motorPinNumber)
 * 引数:excitation 励磁方式 
 *  0, 無回転
 *  1, 1-1相励磁
 *  2, 2-2相励磁
 *  3, 1-2相励磁
 * 
 * 引数:isForward 正転か逆転かどうか 
 *  true, 正転
 *  false, 逆転 
 * 
 * 引数:motorPinNumber ステッピングモータのPIN番号;
 * 
 * 返り値:
 * なし
 * 
 * motorPIN_output[][] 返り値はありませんが、この配列にbool値が代入されます。
 */

// char motorPIN_arr[3][4] = {
//   {0,2,3,4},
//   {5,6,7,8},
//   {10,11,12,13}
// };

// bool motorPIN_output[3][4] = {};

// void setup(){
  
//   // pinMode(motorPIN_arr[0][0], OUTPUT);  // デジタルピンを出力に設定
//   // pinMode(motorPIN_arr[0][1], OUTPUT);
//   // pinMode(motorPIN_arr[0][2], OUTPUT);
//   // pinMode(motorPIN_arr[0][3], OUTPUT);

//   // pinMode(motorPIN_arr[1][0], OUTPUT);  // デジタルピンを出力に設定
//   // pinMode(motorPIN_arr[1][1], OUTPUT);
//   // pinMode(motorPIN_arr[1][2], OUTPUT);
//   // pinMode(motorPIN_arr[1][3], OUTPUT);

//   // pinMode(motorPIN_arr[2][0], OUTPUT);  // デジタルピンを出力に設定
//   // pinMode(motorPIN_arr[2][1], OUTPUT);
//   // pinMode(motorPIN_arr[2][2], OUTPUT);
//   // pinMode(motorPIN_arr[2][3], OUTPUT);
// // Serial.begin(9600);
// }
// void loop(){

// turnStepperMotor(1,0,0);
// turnStepperMotor(2,1,1);
// turnStepperMotor(3,1,2);

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

// delay(8);
// // Serial.println(count);
// // Serial.print(a);
// // Serial.print(b);
// // Serial.print(c);
// // Serial.println(d);

// }

static char count[3] = {0,0,0};
static bool isHalf[3] = {true,true,true};

static void onePhaseOn(bool isForward, char motorPinNumber);
static void twoPhaseOn(bool isForward, char motorPinNumber);

void turnStepperMotor(char excitation, bool isForward, char motorPinNumber){
	switch (excitation){
  case 0:
    break;
    
	case 1:
		{
			onePhaseOn(isForward, motorPinNumber);
		}
		break;

	case 2:
		{
			twoPhaseOn(isForward, motorPinNumber);
		}
		break;

	case 3:
		{
      if (isHalf[motorPinNumber]){
        onePhaseOn(isForward, motorPinNumber);
        if(isForward){
          count[motorPinNumber] = (count[motorPinNumber] != 0) ? count[motorPinNumber] - 1 : 3 ;
        }      
      }else{
        twoPhaseOn(isForward, motorPinNumber);
        if(!isForward){
          count[motorPinNumber] = (count[motorPinNumber] != 3) ? count[motorPinNumber] + 1 : 0 ;
        }
      }
      isHalf[motorPinNumber] = !isHalf[motorPinNumber] ;
      
		}
		break;
	}

}

static unsigned char output[3];
static void countUp(bool isForward, char motorPinNumber);
static void setMotorPinOutput(char motorPinNumber);

static void onePhaseOn(bool isForward, char motorPinNumber){
	output[motorPinNumber] = 0x01 << count[motorPinNumber] ;
  setMotorPinOutput(motorPinNumber);

  countUp(isForward, motorPinNumber);

}

static void twoPhaseOn(bool isForward, char motorPinNumber){
  
  output[motorPinNumber] = (count[motorPinNumber] != 3) ? 0x03 << count[motorPinNumber] : 0x09 ;
  setMotorPinOutput(motorPinNumber);

  countUp(isForward, motorPinNumber);

}

static void setMotorPinOutput(char motorPinNumber){
  motorPIN_output[motorPinNumber][0] = ( output[motorPinNumber] & 0x01 );
	motorPIN_output[motorPinNumber][1] = ( output[motorPinNumber] & 0x02 );
	motorPIN_output[motorPinNumber][2] = ( output[motorPinNumber] & 0x04 );
	motorPIN_output[motorPinNumber][3] = ( output[motorPinNumber] & 0x08 );
};

static void countUp(bool isForward, char motorPinNumber){

  switch (isForward)
  {
  case 1:
    {
      count[motorPinNumber] = (count[motorPinNumber] != 3) ? count[motorPinNumber] + 1 : 0 ;
    }
    break;
  
  case 0:
    {
      count[motorPinNumber] = (count[motorPinNumber] != 0) ? count[motorPinNumber] - 1 : 3 ;
    }
    break;
  }

}