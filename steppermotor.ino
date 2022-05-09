/*
 * File:   steppermotor.ino
 * Author: Yuki Miyakoshi
 */
 
/*
 * ステッピングモーターを回転させる関数
 * turnStepperMotor(char excitation,bool isForward)
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
 * 返り値:
 * なし
 */



// #define MotorPIN1 2 // 青
// #define MotorPIN2 3 // ピンク
// #define MotorPIN3 4 // 黄
// #define MotorPIN4 5 // オレンジ

// void setup(){
  
//   pinMode(MotorPIN1, OUTPUT);  // デジタルピンを出力に設定
//   pinMode(MotorPIN2, OUTPUT);
//   pinMode(MotorPIN3, OUTPUT);
//   pinMode(MotorPIN4, OUTPUT);
// Serial.begin(9600);
// }
// void loop(){

// turnStepperMotor(3,0);

// delay(800);
// // Serial.println(count);
// // Serial.print(a);
// // Serial.print(b);
// // Serial.print(c);
// // Serial.println(d);

// }

static char count = 0;
static bool isHalf = true;

static void onePhaseOn(bool isForward);
static void twoPhaseOn(bool isForward);

void turnStepperMotor(char excitation,bool isForward){
	switch (excitation){
  case 0:
    break;
    
	case 1:
		{
			onePhaseOn(isForward);
		}
		break;

	case 2:
		{
			twoPhaseOn(isForward);
		}
		break;

	case 3:
		{
      if (isHalf){
        onePhaseOn(isForward);
        if(isForward){
          count = (count != 0) ? count - 1 : 3 ;
        }      
      }else{
        twoPhaseOn(isForward);
        if(!isForward){
          count = (count != 3) ? count + 1 : 0 ;
        }
      }
      isHalf = !isHalf ;
      
		}
		break;
	}

}

static unsigned char output;
static void countUp(bool isForward);

static void onePhaseOn(bool isForward){
	output = 0x01 << count ;
	bool a = ( output & 0x01 );
	bool b = ( output & 0x02 );
	bool c = ( output & 0x04 );
	bool d = ( output & 0x08 );

  digitalWrite(MotorPIN1,a);
  digitalWrite(MotorPIN2,b);
  digitalWrite(MotorPIN3,c);
  digitalWrite(MotorPIN4,d);

  countUp(isForward);

}

static void twoPhaseOn(bool isForward){
  
  output = (count != 3) ? 0x03 << count : 0x09 ;
	bool a = ( output & 0x01 );
	bool b = ( output & 0x02 );
	bool c = ( output & 0x04 );
	bool d = ( output & 0x08 );

  digitalWrite(MotorPIN1,a);
  digitalWrite(MotorPIN2,b);
  digitalWrite(MotorPIN3,c);
  digitalWrite(MotorPIN4,d);

  countUp(isForward);

}

static void countUp(bool isForward){

  switch (isForward)
  {
  case 1:
    {
      count = (count != 3) ? count + 1 : 0 ;
    }
    break;
  
  case 0:
    {
      count = (count != 0) ? count - 1 : 3 ;
    }
    break;
  }

}