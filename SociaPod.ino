//基本モーション
#include<VarSpeedServo.h>

#define DEFAULT_POS 90

// Front-Rear/Left-Right/Arm-Claw
  #define FRONT 0
  #define REAR 1
  #define LEFT 0
  #define RIGHT 1
  #define ARM 0
  #define CLAW 1

// short ver.
  #define F 0
  #define R 1
  #define L 0
//#define R 1
  #define A 0
  #define C 1

int servoAngles[2][2][2] = {};

VarSpeedServo servo[2][2][2];

//プロトタイプ宣言

//プログラミング例
void forward();
void turn_right();

//High Level functions
void armMove(int FR, int LR, int deltaAngle, int _speed = 50);
void armMoveTo(int FR, int LR, int angle, int _speed = 50);
void crawl(int deltaAngle, int _speed = 50);
void initializePose();

//Low Level Function
void servoMove(int FR, int LR, int AC, int deltaAngle, boolean isWait = true, int _speed = 50);
void servoMoveTo(int FR, int LR, int AC, int angle, boolean isWait = true, int _speed = 50);


void setup(){

  servo[F][R][A].attach(2);
  servo[F][R][C].attach(3);
  servo[F][L][A].attach(4);
  servo[F][L][C].attach(5);
  
  servo[R][R][A].attach(10);
  servo[R][R][C].attach(11);
  servo[R][L][A].attach(12);
  servo[R][L][C].attach(13);

}

void loop(){

    initializePose();

    forward();

/*
    servoMoveTo(F,R,A, 15);
    servoMoveTo(F,R,A, -15);
    servoMove(F,R,A, 15);

    servoMove(F,R,C, 15);
    servoMove(F,R,C, -15);



    servoMoveTo(F,L,A, 15);
    servoMoveTo(F,L,A, -15);
    servoMove(F,L,A, 15);

    servoMove(F,L,C, 15);
    servoMove(F,L,C, -15);



    servoMoveTo(R,R,A, 15);
    servoMoveTo(R,R,A, -15);
    servoMove(R,R,A, 15);

    servoMove(R,R,C, 15);
    servoMove(R,R,C, -15);



    servoMoveTo(R,F,A, 15);
    servoMoveTo(R,F,A, -15);
    servoMove(R,F,A, 15);

    servoMove(R,F,C, 15);
    servoMove(R,F,C, -15);
    */
 
}


//High Level Function
void initializePose(){
  servoMoveTo(F,R,A,0, false);
  servoMoveTo(F,R,C,0, false);
  servoMoveTo(F,L,A,0, false);
  servoMoveTo(F,L,C,0, false);
  servoMoveTo(R,R,A,0, false);
  servoMoveTo(R,R,C,0, false);
  servoMoveTo(R,L,A,0, false);
  servoMoveTo(R,L,C,0, false);
  
}

void armMove(int FR, int LR, int deltaAngle, int _speed = 50){
  servoMoveTo(FR, LR, C, 30, true, _speed);
  servoMove(FR, LR, A, deltaAngle, true, _speed);
  servoMoveTo(FR, LR, C, 0, true, _speed);
}

void armMoveTo(int FR, int LR, int angle, int _speed = 50){
  servoMoveTo(FR, LR, C, 30, true, _speed);
  servoMoveTo(FR, LR, A, angle, true, _speed);
  servoMoveTo(FR, LR, C, 0, true, _speed);
}

void crawl(int deltaAngle, int _speed = 50) {
  servoMove(F,R,A,deltaAngle, false);
  servoMove(F,L,A,deltaAngle, false);
  servoMove(R,R,A,deltaAngle, false);
  servoMove(R,L,A,deltaAngle, true);
}

//Low Level Function
void servoMove(int FR, int LR, int AC, int deltaAngle, boolean isWait = true, int _speed = 50) {
  if(AC == 0){
    servoAngles[FR][LR][AC] += deltaAngle*(LR*2-1);
  } else if (AC == 1) {
    servoAngles[FR][LR][AC] += deltaAngle*(((FR+LR)%2)*2-1);
  }
  // check angle range
  if(servoAngles[FR][LR][AC] < -90) {
    servoAngles[FR][LR][AC] = -90;
  } else if (servoAngles[FR][LR][AC] > 90) {
    servoAngles[FR][LR][AC] = 90;
  }
  
   servo[FR][LR][AC].write(DEFAULT_POS-servoAngles[FR][LR][AC], _speed, isWait);
}

void servoMoveTo(int FR, int LR, int AC, int angle, boolean isWait = true, int _speed = 50) {

  if(AC == 0){
    servoAngles[FR][LR][AC] = angle*(LR*2-1);
  } else if (AC == 1) {
    servoAngles[FR][LR][AC] = angle*(((FR+LR)%2)*2-1);
  }

  // check angle range
  if(servoAngles[FR][LR][AC] < -90) {
    servoAngles[FR][LR][AC] = -90;
  } else if (servoAngles[FR][LR][AC] > 90) {
    servoAngles[FR][LR][AC] = 90;
  }
  if(AC == 0){
    servo[FR][LR][AC].write(DEFAULT_POS-servoAngles[FR][LR][AC], _speed, isWait);
  } else if (AC == 1) {
    servo[FR][LR][AC].write(DEFAULT_POS-servoAngles[FR][LR][AC], _speed, isWait);
  }
}


 //forward
void forward(){  
  armMove(R,R,30); //initialize

  int count = 0;

  initializePose();
  
  armMoveTo(F,R,-15);
  armMoveTo(R,R, 15);
  
  while(count < 10){

    armMove(F,R,30);
    crawl(-15);  
    armMove(R,L,30);                   //step4
    armMove(F,L,30);                   //step5
    crawl(-15);      //step6
    armMove(R,R,30);                   //step1

    count++;
  }
}

void turn_right(){
  int count = 0;
  while( count < 3 ){

    armMove(F,R,-30, false);
    armMove(F,L,-30, false);
    armMove(R,L,-30, false);
    armMove(R,R,-30, false);

    initializePose();

    count++;
  }
}

