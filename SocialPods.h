#include<VarSpeedServo.h>

//======================================//
//           Constant Numbers           //
//======================================//
// Do Not Touch!!! //

#define DEFAULT_POS 90

// Front-Rear/Left-Right/SHOULDER-Claw
  #define FRONT 0
  #define REAR 1
  #define LEFT 0
  #define RIGHT 1
  #define SHOULDER 0
  #define CLAW 1

// short ver.
  #define F 0
  #define R 1
  #define L 0
//#define R 1
  #define S 0
  #define C 1

//======================================//
//               Variables              //
//======================================//

extern int servo_angles[2][2][2];
extern int calib[2][2][2];
extern VarSpeedServo servo[2][2][2];

//example codes
void forward(int speed = 50, int loop = 1);
void turnRight(int speed = 50);

//======================================//
//         Prototype Declaration        //
//======================================//

//High Level functions
void armMove(int FR, int LR, int delta_angle, int _speed = 50);
void armMoveTo(int FR, int LR, int angle, int _speed = 50);
void initializePose();

//Low Level Function
void servoMove(int FR, int LR, int SC, int delta_angle, bool isWait = true, int _speed = 50);
void servoMove(int FR, int LR, int SC, int delta_angle, int _speed);
void servoMoveTo(int FR, int LR, int SC, int angle, bool isWait = true, int _speed = 50);
void servoMoveTo(int FR, int LR, int SC, int angle, int _speed);
void calibrateTo(int FR, int LR, int SC, int calib_value);
