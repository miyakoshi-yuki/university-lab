const unsigned char MotorPIN1 = 2; // 青
const unsigned char MotorPIN2 = 3; // ピンク
const unsigned char MotorPIN3 = 4; // 黄
const unsigned char MotorPIN4 = 5; // オレンジ

void setup(){
  
  pinMode(MotorPIN1, OUTPUT);  // デジタルピンを出力に設定
  pinMode(MotorPIN2, OUTPUT);
  pinMode(MotorPIN3, OUTPUT);
  pinMode(MotorPIN4, OUTPUT);
  // Serial.begin(9600);
}
void loop(){
  //   for(int i = 0; i<1000; i++){
  //   turnStepperMotor(0);
  //   delay(2);
  // }
  // delay(1000);
  for(int i = 0; i<10000; i++){
    turnStepperMotor(1);
    delay(20);
  }
  // delay(1000);
  // for(int i = 0; i<1000; i++){
  //   turnStepperMotor(2);
  //   delay(1);
  // }
  // delay(1000);
  
  // for(int i = 0; i<10; i++){
  //   turnStepperMotor(0);
  //   delay(500);
  // }
  // delay(1000);
  // for(int i = 0; i<10; i++){
  //   turnStepperMotor(1);
  //   delay(500);
  // }
  // delay(1000);
  // for(int i = 0; i<10; i++){
  //   turnStepperMotor(2);
  //   delay(500);
  // }
  // delay(1000);
}

static unsigned char count = 0;
static bool isHalf = true;

static void onePhaseOn();
static void twoPhaseOn();

void turnStepperMotor(int x){
	switch (x){
	case 0:
		{
			onePhaseOn();
		}
		break;

	case 1:
		{
			twoPhaseOn();
		}
		break;

	case 2:
		{
      if (isHalf){
        onePhaseOn();
        count = (count != 0) ? count - 1 : 3 ;
      }else{
        twoPhaseOn();
      }
      isHalf = !isHalf ;
		}
		break;

	default:
		break;
	}
}

static unsigned char output;

static void onePhaseOn(){
	output = 0x01 << count ;
	bool a = ( output & 0x01 );
	bool b = ( output & 0x02 );
	bool c = ( output & 0x04 );
	bool d = ( output & 0x08 );

  digitalWrite(MotorPIN1,a);
  digitalWrite(MotorPIN2,b);
  digitalWrite(MotorPIN3,c);
  digitalWrite(MotorPIN4,d);
// Serial.println(count);
// Serial.print(a);
// Serial.print(b);
// Serial.print(c);
// Serial.println(d);

	count = (count != 3) ? count + 1 : 0 ;

}

static void twoPhaseOn(){
	output = (count != 3) ? 0x03 << count : 0x09 ;
	bool a = ( output & 0x01 );
	bool b = ( output & 0x02 );
	bool c = ( output & 0x04 );
	bool d = ( output & 0x08 );

  digitalWrite(MotorPIN1,a);
  digitalWrite(MotorPIN2,b);
  digitalWrite(MotorPIN3,c);
  digitalWrite(MotorPIN4,d);
  // Serial.println(count);
  // Serial.print(a);
  // Serial.print(b);
  // Serial.print(c);
  // Serial.println(d);

  count = (count != 3) ? count + 1 : 0 ;

}