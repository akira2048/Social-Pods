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

int servo_angles[2][2][2] = {};
int calib[2][2][2] = {};

VarSpeedServo servo[2][2][2];

//プロトタイプ宣言
//プログラミング例
void forward();
void turn_right();
void onedari();
void te_huru();

//High Level functions
void arm_move(int FR, int LR, int delta_angle, int _speed = 50);
void arm_moveTo(int FR, int LR, int angle, int _speed = 50);
void crawl(int delta_angle, int _speed = 50);
void initialize_pose();

//Low Level Function
void servo_move(int FR, int LR, int AC, int delta_angle, boolean isWait = true, int _speed = 50);
void servo_move_to(int FR, int LR, int AC, int angle, boolean isWait = true, int _speed = 50);


void setup(){

  servo[F][R][A].attach(2);
  servo[F][R][C].attach(3);
  servo[F][L][A].attach(4);
  servo[F][L][C].attach(5);
  servo[R][R][A].attach(10);
  servo[R][R][C].attach(11);
  servo[R][L][A].attach(12);
  servo[R][L][C].attach(13);
  
  initialize_pose();

}

void loop(){

  //initialize_pose();

  //delay(10000);

  //onedari();

  //forward();

  calibration(F,R,A,-30);
  calibration(F,L,A,-28);
  calibration(R,R,A,30);
  calibration(R,L,A,30);
  
  te_huru();
  forward();
  turn_right();

}


//High Level Function
void initialize_pose(){
  servo_move_to(F,R,A,0, false);
  servo_move_to(F,R,C,0, false);
  servo_move_to(F,L,A,0, false);
  servo_move_to(F,L,C,0, false);
  servo_move_to(R,R,A,0, false);
  servo_move_to(R,R,C,0, false);
  servo_move_to(R,L,A,0, false);
  servo_move_to(R,L,C,0, true);
}

void arm_move(int FR, int LR, int delta_angle, int _speed = 50){
  servo_move_to(FR, LR, C, 30, true, _speed);
  servo_move(FR, LR, A, delta_angle, true, _speed);
  servo_move_to(FR, LR, C, 0, true, _speed);
}

void arm_move_to(int FR, int LR, int angle, int _speed = 50){
  servo_move_to(FR, LR, C, 30, true, _speed);
  servo_move_to(FR, LR, A, angle, true, _speed);
  servo_move_to(FR, LR, C, 0, true, _speed);
}

void crawl(int delta_angle, int _speed = 50) {
  servo_move(F,R,A,delta_angle, false);
  servo_move(F,L,A,delta_angle, false);
  servo_move(R,L,A,delta_angle, false);
  servo_move(R,R,A,delta_angle, true);
};

//Low Level Function
void servo_move(int FR, int LR, int AC, int delta_angle, boolean isWait = true, int _speed = 50) {
  if(AC == 0){
    servo_angles[FR][LR][AC] += delta_angle*(LR*2-1);
  } else if (AC == 1) {
    servo_angles[FR][LR][AC] += delta_angle*(((FR+LR)%2)*2-1);
  }
  // check angle range
  if(servo_angles[FR][LR][AC] < -90) {
    servo_angles[FR][LR][AC] = -90;
  } else if (servo_angles[FR][LR][AC] > 90) {
    servo_angles[FR][LR][AC] = 90;
  }
   servo[FR][LR][AC].write(DEFAULT_POS-servo_angles[FR][LR][AC], _speed, isWait);
}

void servo_move_to(int FR, int LR, int AC, int angle, boolean isWait = true, int _speed = 50) {

  if(AC == 0){
    servo_angles[FR][LR][AC] = angle*(LR*2-1) + calib[FR][LR][AC];
  } else if (AC == 1) {
    servo_angles[FR][LR][AC] = angle*(((FR+LR)%2)*2-1) + calib[FR][LR][AC];
  }
  // check angle range
  if(servo_angles[FR][LR][AC] < -90) {
    servo_angles[FR][LR][AC] = -90;
  } else if (servo_angles[FR][LR][AC] > 90) {
    servo_angles[FR][LR][AC] = 90;
  }
  if(AC == 0){
    servo[FR][LR][AC].write(DEFAULT_POS-servo_angles[FR][LR][AC], _speed, isWait);
  } else if (AC == 1) {
    servo[FR][LR][AC].write(DEFAULT_POS-servo_angles[FR][LR][AC], _speed, isWait);
  }
}

void calibration(int FR , int LR, int AC, int calib_value){
  if(AC == 0){
    calib[FR][LR][AC] = calib_value*(LR*2-1);
  } else if (AC == 1) {
    calib[FR][LR][AC] = calib_value*(((FR+LR)%2)*2-1);
  }
}

void te_huru(){

  servo_move(REAR, LEFT, CLAW, 40, true);
  servo_move(FRONT, RIGHT, CLAW, 40, true);
  servo_move(FRONT, RIGHT, ARM, 20, true);

  int count = 10;

  while(count > 0){
    
    servo_move(FRONT, RIGHT, ARM, -40, true);
    servo_move(FRONT, RIGHT, ARM, 40, true);
    count--; 
  }
}

void dolphin(){

  int count = 10;

  while(count > 0){

    servo_move(FRONT, RIGHT, CLAW, -40, false);
    servo_move(FRONT, LEFT,  CLAW, -40, true);
    servo_move(REAR, RIGHT, CLAW, -40, false);
    servo_move(REAR, LEFT,  CLAW, -40, true);

    servo_move(FRONT, RIGHT, CLAW, 40, false);
    servo_move(FRONT, LEFT,  CLAW, 40, true);
    servo_move(REAR, RIGHT, CLAW, 40, false);
    servo_move(REAR, LEFT,  CLAW, 40, true);
    
    count--;
  }
  
}

void onedari() {

  servo_move_to(FRONT, RIGHT, CLAW, -45, false);
  servo_move_to(FRONT, LEFT,  CLAW, -45, false);
  servo_move_to(REAR,  RIGHT, CLAW,  15, false);
  servo_move_to(REAR,  LEFT,  CLAW,  15, true);

  int count = 10;

  while(count > 0){

    servo_move(FRONT, RIGHT, ARM, -10, false, 40);
    servo_move(FRONT, LEFT,  ARM, -10, true,  40);
    servo_move(FRONT, RIGHT, ARM, 10, false,  40);
    servo_move(FRONT, LEFT,  ARM, 10, true,   40);
    
    count--;
  }
  
}


void forward(){  

  int count = 0;
  
  arm_move_to(F,R,-30);
  arm_move_to(R,R, 30);
  arm_move_to(F,L,-15);  
  arm_move_to(R,L, 15);
  
  while(count < 10){

    //reference : http://makezine.jp/blog/2016/12/robot-quadruped-arduino-program.html
    arm_move(F,R,30); //step2
    crawl(-15);      //step3
    arm_move(R,L,30); //step4
    arm_move(F,L,30); //step5
    crawl(-15);      //step6
    arm_move(R,R,30); //step1

    count++;
  }
}

void turn_right(){
  int count = 0;
  while( count < 3 ){
    arm_move(F,R,-30);
    arm_move(F,L,30);
    arm_move(R,L,30);
    arm_move(R,R,-30);
    initialize_pose();
    count++;
  }
}
