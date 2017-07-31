#include <SociaPod.h>

void runrun(int degree = 20);
void runrun2(int degree = 30);
void iraira();
void kanashimi();

void setup() {
  
  servo[F][R][S].attach(2);
  servo[F][R][C].attach(3);
  servo[F][L][S].attach(4);
  servo[F][L][C].attach(5);
  servo[R][R][S].attach(10);
  servo[R][R][C].attach(11);
  servo[R][L][S].attach(12);
  servo[R][L][C].attach(13);
  
  // Calibrate motor defualt position here
  calibration(F, R, S, -30);
  calibration(R, R, S, 30);
  calibration(F, L, S, -30);
  calibration(R, L, S, 30);

  initialize_pose();
}

void loop() {
  
  runrun();
  delay(500);
  runrun2();
  delay(500);
  iraira();
  delay(500);
  kanashimi();
  delay(500);
}

void runrun(int degree = 20){
  int count = 0;

  // initialization
  servo_move_to(F, L, S, -30, false);
  servo_move_to(F, R, S, -30, false);
  servo_move_to(R, L, S, 30, 0, false);
  servo_move_to(R, R, S, 30, 0, false);
  servo_move_to(F, L, C, 0, false);
  servo_move_to(F, R, C, 0, false);
  servo_move_to(R, L, C, 0, false);
  servo_move_to(R, R, C, 0, true);

  // first motion
  servo_move(F, R, S, degree, false);
  servo_move(R, R, S, degree, false);
  servo_move(F, L, S, degree*(-1), false);
  servo_move(R, L, S, degree*(-1), true);

  // repetitive motion
  while(count < 5){
    delay(850);
    servo_move(F, R, S, degree*(-2), false);
    servo_move(R, R, S, degree*(-2), false);
    servo_move(F, L, S, degree*2, false);
    servo_move(R, L, S, degree*2, true);
    delay(550);
    servo_move(F, R, S, degree*2, false);
    servo_move(R, R, S, degree*2, false);
    servo_move(F, L, S, degree*(-2), false);
    servo_move(R, L, S, degree*(-2), true);
    count++;
  }
}

void runrun2(int degree = 30){
  int count = 0;

  // initialization
  servo_move_to(F, L, S, -30, false);
  servo_move_to(F, R, S, -30, false);
  servo_move_to(R, L, S, 30, 0, false);
  servo_move_to(R, R, S, 30, 0, false);
  servo_move_to(F, L, C, 0, false);
  servo_move_to(F, R, C, 0, false);
  servo_move_to(R, L, C, 0, false);
  servo_move_to(R, R, C, 0, true);

  // first motion
  servo_move_to(F, R, C, degree, false);
  servo_move_to(R, R, C, degree, false);
  servo_move_to(F, L, C, -degree, false);
  servo_move_to(R, L, C, -degree, true);

  // repetitive motion
  while(count < 5){
    delay(550);
    servo_move_to(F, R, C, -degree, false);
    servo_move_to(R, R, C, -degree, false);
    servo_move_to(F, L, C, degree, false);
    servo_move_to(R, L, C, degree, true);
    delay(550);
    servo_move_to(F, R, C, degree, false);
    servo_move_to(R, R, C, degree, false);
    servo_move_to(F, L, C, -degree, false);
    servo_move_to(R, L, C, -degree, true);
    count++;
  }
}

void iraira(){
  int count = 0;

  // initialization
  servo_move_to(F, L, S, -30, false);
  servo_move_to(F, R, S, -30, false);
  servo_move_to(R, R, S, 30, 0, false);
  servo_move_to(R, L, S, 30, 0, false);
  servo_move_to(F, L, C, 0, false);
  servo_move_to(F, R, C, 0, false);
  servo_move_to(R, L, C, 0, false);
  servo_move_to(R, R, C, 0, true);
  arm_move_to(R, R, -50, 150);
  arm_move_to(F, L, 40, 150);
  servo_move_to(R, R, C, 20, true, 70);
  delay(100);

  //main motion
  while(count < 20){
    servo_move_to(F, L, C, 30, true, 145);
    servo_move_to(F, L, C, -10, true, 145);
    count++;
  }
}

void kanashimi(){
  int count = 0;

  // initialization
  servo_move_to(R, L, S, -20, false, 100);
  servo_move_to(R, R, S, -20, false, 100);
  servo_move_to(F, R, S, 50, false, 100);
  servo_move_to(F, L, S, 50, false, 100);
  servo_move_to(R, L, C, -20, false, 100);
  servo_move_to(R, R, C, -20, false, 100);
  servo_move_to(F, L, C, 50, false, 30);
  servo_move_to(F, R, C, 50, true, 30);
  delay(100);

  //main motion
  while(count < 20){
    servo_move_to(F, R, C, 65, false, 60);
    servo_move_to(F, L, C, 65, true, 60);
    delay(50);
    servo_move_to(F, R, C, 50, false, 60);
    servo_move_to(F, L, C, 50, true, 60);
    delay(50);
    count++;
  }
}
