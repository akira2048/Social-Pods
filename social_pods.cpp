//Basic Motion
#include<VarSpeedServo.h>
#include<socialPods.h>

//======================================//
//               Variables              //
//======================================//
// Do Not Touch!!! //

int servoAngles[2][2][2] = {};
int calib[2][2][2] = {};
VarSpeedServo servo[2][2][2];

//======================================//
//          Example Functions           //
//======================================//

//reference : http://makezine.jp/blog/2016/12/robot-quadruped-arduino-program.html
void forward(int speed = 50){  

  armMoveTo(F,R,-30);
  armMoveTo(R,R, 30);
  armMoveTo(F,L,-15);  
  armMoveTo(R,L, 15);
  
  int count = 0;
  while(count < 10){

    armMove(F,R,30,speed);
    
    servoMove(F,R,S,deltaAngle, false, speed);
    servoMove(F,L,S,deltaAngle, false, speed);
    servoMove(R,L,S,deltaAngle, false, speed);
    servoMove(R,R,S,deltaAngle, true,  speed);
    
    armMove(R,L,30,speed);
    armMove(F,L,30,speed);

    servoMove(F,R,S,deltaAngle, false, speed);
    servoMove(F,L,S,deltaAngle, false, speed);
    servoMove(R,L,S,deltaAngle, false, speed);
    servoMove(R,R,S,deltaAngle, true,  speed);

    armMove(R,R,30,speed);

    count++;
  }
}

void turnRight(int speed = 50){
  int count = 0;
  while( count < 3 ){
    armMove(F,R,-30, speed);
    armMove(F,L,30, speed);
    armMove(R,L,30, speed);
    armMove(R,R,-30, speed);
    initializePose();
    count++;
  }
}

//======================================//
//     Wrapper Function Definitions     //
//======================================//
// Do Not Touch!!! //

//High Level Function
void initializePose(){
  servoMoveTo(F,R,S,0, false);
  servoMoveTo(F,R,C,0, false);
  servoMoveTo(F,L,S,0, false);
  servoMoveTo(F,L,C,0, false);
  servoMoveTo(R,R,S,0, false);
  servoMoveTo(R,R,C,0, false);
  servoMoveTo(R,L,S,0, false);
  servoMoveTo(R,L,C,0, true);
}

void armMove(int FR, int LR, int deltaAngle, int _speed = 50){
  servoMoveTo(FR, LR, C, 30, true, _speed);
  servoMove(FR, LR, S, deltaAngle, true, _speed);
  servoMoveTo(FR, LR, C, 0, true, _speed);
}

void armMoveTo(int FR, int LR, int angle, int _speed = 50){
  servoMoveTo(FR, LR, C, 30, true, _speed);
  servoMoveTo(FR, LR, S, angle, true, _speed);
  servoMoveTo(FR, LR, C, 0, true, _speed);
}

void crawl(int deltaAngle, int _speed = 50) {

};

//Low Level Function
void servoMove(int FR, int LR, int SC, int deltaAngle, bool isWait = true, int _speed = 50) {
  if(SC == 0){
    servoAngles[FR][LR][SC] += deltaAngle*(LR*2-1);
  } else if (SC == 1) {
    servoAngles[FR][LR][SC] += deltaAngle*(((FR+LR)%2)*2-1);
  }
  // check angle range
  if(servoAngles[FR][LR][SC] < -90) {
    servoAngles[FR][LR][SC] = -90;
  } else if (servoAngles[FR][LR][SC] > 90) {
    servoAngles[FR][LR][SC] = 90;
  }
   servo[FR][LR][SC].write(DEFAULT_POS-servoAngles[FR][LR][SC], _speed, isWait);
}

void servoMove(int FR, int LR, int SC, int deltaAngle, int _speed = 50) {
  if(SC == 0){
    servoAngles[FR][LR][SC] += deltaAngle*(LR*2-1);
  } else if (SC == 1) {
    servoAngles[FR][LR][SC] += deltaAngle*(((FR+LR)%2)*2-1);
  }
  // check angle range
  if(servoAngles[FR][LR][SC] < -90) {
    servoAngles[FR][LR][SC] = -90;
  } else if (servoAngles[FR][LR][SC] > 90) {
    servoAngles[FR][LR][SC] = 90;
  }
   servo[FR][LR][SC].write(DEFAULT_POS-servoAngles[FR][LR][SC], _speed);
}

void servoMoveTo(int FR, int LR, int SC, int angle, bool isWait = true, int _speed = 50) {

  if(SC == 0){
    servoAngles[FR][LR][SC] = angle*(LR*2-1) + calib[FR][LR][SC];
  } else if (SC == 1) {
    servoAngles[FR][LR][SC] = angle*(((FR+LR)%2)*2-1) + calib[FR][LR][SC];
  }
  // check angle range
  if(servoAngles[FR][LR][SC] < -90) {
    servoAngles[FR][LR][SC] = -90;
  } else if (servoAngles[FR][LR][SC] > 90) {
    servoAngles[FR][LR][SC] = 90;
  }
  if(SC == 0){
    servo[FR][LR][SC].write(DEFAULT_POS-servoAngles[FR][LR][SC], _speed, isWait);
  } else if (SC == 1) {
    servo[FR][LR][SC].write(DEFAULT_POS-servoAngles[FR][LR][SC], _speed, isWait);
  }
}

void servoMoveTo(int FR, int LR, int SC, int angle, int _speed = 50) {

  if(SC == 0){
    servoAngles[FR][LR][SC] = angle*(LR*2-1) + calib[FR][LR][SC];
  } else if (SC == 1) {
    servoAngles[FR][LR][SC] = angle*(((FR+LR)%2)*2-1) + calib[FR][LR][SC];
  }
  // check angle range
  if(servoAngles[FR][LR][SC] < -90) {
    servoAngles[FR][LR][SC] = -90;
  } else if (servoAngles[FR][LR][SC] > 90) {
    servoAngles[FR][LR][SC] = 90;
  }
  if(SC == 0){
    servo[FR][LR][SC].write(DEFAULT_POS-servoAngles[FR][LR][SC], _speed);
  } else if (SC == 1) {
    servo[FR][LR][SC].write(DEFAULT_POS-servoAngles[FR][LR][SC], _speed);
  }
}

void calibration(int FR , int LR, int SC, int calib_value){
  if(SC == 0){
    calib[FR][LR][SC] = calib_value*(LR*2-1);
  } else if (SC == 1) {
    calib[FR][LR][SC] = calib_value*(((FR+LR)%2)*2-1);
  }
}
