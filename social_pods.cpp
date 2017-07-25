//Basic Motion
#include<VarSpeedServo.h>
#include<social_pods.h>

//======================================//
//               Variables              //
//======================================//
// Do Not Touch!!! //

int servo_angles[2][2][2] = {};
int calib[2][2][2] = {};
VarSpeedServo servo[2][2][2];

//======================================//
//          Example Functions           //
//======================================//

void forward(int speed = 50){  

  int count = 0;
  
  arm_move_to(F,R,-30);
  arm_move_to(R,R, 30);
  arm_move_to(F,L,-15);  
  arm_move_to(R,L, 15);
  
  while(count < 10){

    //reference : http://makezine.jp/blog/2016/12/robot-quadruped-arduino-program.html
    arm_move(F,R,30,speed); //step2
    crawl(-15, speed);      //step3
    arm_move(R,L,30,speed); //step4
    arm_move(F,L,30,speed); //step5
    crawl(-15, speed);      //step6
    arm_move(R,R,30,speed); //step1

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

//======================================//
//     Wrapper Function Definitions     //
//======================================//
// Do Not Touch!!! //

//High Level Function
void initialize_pose(){
  servo_move_to(F,R,S,0, false);
  servo_move_to(F,R,C,0, false);
  servo_move_to(F,L,S,0, false);
  servo_move_to(F,L,C,0, false);
  servo_move_to(R,R,S,0, false);
  servo_move_to(R,R,C,0, false);
  servo_move_to(R,L,S,0, false);
  servo_move_to(R,L,C,0, true);
}

void arm_move(int FR, int LR, int delta_angle, int _speed = 50){
  servo_move_to(FR, LR, C, 30, true, _speed);
  servo_move(FR, LR, S, delta_angle, true, _speed);
  servo_move_to(FR, LR, C, 0, true, _speed);
}

void arm_move_to(int FR, int LR, int angle, int _speed = 50){
  servo_move_to(FR, LR, C, 30, true, _speed);
  servo_move_to(FR, LR, S, angle, true, _speed);
  servo_move_to(FR, LR, C, 0, true, _speed);
}

void crawl(int delta_angle, int _speed = 50) {
  servo_move(F,R,S,delta_angle, false);
  servo_move(F,L,S,delta_angle, false);
  servo_move(R,L,S,delta_angle, false);
  servo_move(R,R,S,delta_angle, true);
};

//Low Level Function
void servo_move(int FR, int LR, int SC, int delta_angle, bool isWait = true, int _speed = 50) {
  if(SC == 0){
    servo_angles[FR][LR][SC] += delta_angle*(LR*2-1);
  } else if (SC == 1) {
    servo_angles[FR][LR][SC] += delta_angle*(((FR+LR)%2)*2-1);
  }
  // check angle range
  if(servo_angles[FR][LR][SC] < -90) {
    servo_angles[FR][LR][SC] = -90;
  } else if (servo_angles[FR][LR][SC] > 90) {
    servo_angles[FR][LR][SC] = 90;
  }
   servo[FR][LR][SC].write(DEFAULT_POS-servo_angles[FR][LR][SC], _speed, isWait);
}

void servo_move_to(int FR, int LR, int SC, int angle, bool isWait = true, int _speed = 50) {

  if(SC == 0){
    servo_angles[FR][LR][SC] = angle*(LR*2-1) + calib[FR][LR][SC];
  } else if (SC == 1) {
    servo_angles[FR][LR][SC] = angle*(((FR+LR)%2)*2-1) + calib[FR][LR][SC];
  }
  // check angle range
  if(servo_angles[FR][LR][SC] < -90) {
    servo_angles[FR][LR][SC] = -90;
  } else if (servo_angles[FR][LR][SC] > 90) {
    servo_angles[FR][LR][SC] = 90;
  }
  if(SC == 0){
    servo[FR][LR][SC].write(DEFAULT_POS-servo_angles[FR][LR][SC], _speed, isWait);
  } else if (SC == 1) {
    servo[FR][LR][SC].write(DEFAULT_POS-servo_angles[FR][LR][SC], _speed, isWait);
  }
}

void calibration(int FR , int LR, int SC, int calib_value){
  if(SC == 0){
    calib[FR][LR][SC] = calib_value*(LR*2-1);
  } else if (SC == 1) {
    calib[FR][LR][SC] = calib_value*(((FR+LR)%2)*2-1);
  }
}
