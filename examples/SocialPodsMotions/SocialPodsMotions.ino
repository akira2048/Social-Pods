#include <SociaPod.h>

// Prototype declaration
void runrun(int degree = 20, int count = 5);
void runrun2(int degree = 30, int count = 5);
void iraira(int count = 20);
void kanashimi(int count = 20);
void kurekure(int count = 10);
void bunbun(int count = 10);
void kunekune(int count = 10);

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
  calibrateTo(F, R, S, -30);
  calibrateTo(R, R, S, 30);
  calibrateTo(F, L, S, -30);
  calibrateTo(R, L, S, 30);

  initializePose();
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
  kurekure();
  delay(500);
  bunbun();
  delay(500);
  kunekune();
  delay(500);
}

void runrun(int degree = 20, int count = 5){
  int i = 0;  // counter

  // initialization
  servoMoveTo(F, L, S, -30, false);
  servoMoveTo(F, R, S, -30, false);
  servoMoveTo(R, L, S, 30, 0, false);
  servoMoveTo(R, R, S, 30, 0, false);
  servoMoveTo(F, L, C, 0, false);
  servoMoveTo(F, R, C, 0, false);
  servoMoveTo(R, L, C, 0, false);
  servoMoveTo(R, R, C, 0, true);

  // first motion
  servoMove(F, R, S, degree, false);
  servoMove(R, R, S, degree, false);
  servoMove(F, L, S, degree*(-1), false);
  servoMove(R, L, S, degree*(-1), true);

  // repetitive motion
  while(i < count){
    delay(850);
    servoMove(F, R, S, degree*(-2), false);
    servoMove(R, R, S, degree*(-2), false);
    servoMove(F, L, S, degree*2, false);
    servoMove(R, L, S, degree*2, true);
    delay(550);
    servoMove(F, R, S, degree*2, false);
    servoMove(R, R, S, degree*2, false);
    servoMove(F, L, S, degree*(-2), false);
    servoMove(R, L, S, degree*(-2), true);
    i++;
  }
}

void runrun2(int degree = 30, int count = 5){
  int i = 0;  // counter

  // initialization
  servoMoveTo(F, L, S, -30, false);
  servoMoveTo(F, R, S, -30, false);
  servoMoveTo(R, L, S, 30, 0, false);
  servoMoveTo(R, R, S, 30, 0, false);
  servoMoveTo(F, L, C, 0, false);
  servoMoveTo(F, R, C, 0, false);
  servoMoveTo(R, L, C, 0, false);
  servoMoveTo(R, R, C, 0, true);

  // first motion
  servoMoveTo(F, R, C, degree, false);
  servoMoveTo(R, R, C, degree, false);
  servoMoveTo(F, L, C, -degree, false);
  servoMoveTo(R, L, C, -degree, true);

  // repetitive motion
  while(i < count){
    delay(550);
    servoMoveTo(F, R, C, -degree, false);
    servoMoveTo(R, R, C, -degree, false);
    servoMoveTo(F, L, C, degree, false);
    servoMoveTo(R, L, C, degree, true);
    delay(550);
    servoMoveTo(F, R, C, degree, false);
    servoMoveTo(R, R, C, degree, false);
    servoMoveTo(F, L, C, -degree, false);
    servoMoveTo(R, L, C, -degree, true);
    i++;
  }
}

void iraira(int count = 20){
  int i = 0;  // counter

  // initialization
  servoMoveTo(F, L, S, -30, false);
  servoMoveTo(F, R, S, -30, false);
  servoMoveTo(R, R, S, 30, 0, false);
  servoMoveTo(R, L, S, 30, 0, false);
  servoMoveTo(F, L, C, 0, false);
  servoMoveTo(F, R, C, 0, false);
  servoMoveTo(R, L, C, 0, false);
  servoMoveTo(R, R, C, 0, true);
  armMoveTo(R, R, -50, 150);
  armMoveTo(F, L, 40, 150);
  servoMoveTo(R, R, C, 20, true, 70);
  delay(100);

  //main motion
  while(i < count){
    servoMoveTo(F, L, C, 30, true, 145);
    servoMoveTo(F, L, C, -10, true, 145);
    i++;
  }
}

void kanashimi(int count = 20){
  int i= 0; // counter

  // initialization
  servoMoveTo(R, L, S, -20, false, 100);
  servoMoveTo(R, R, S, -20, false, 100);
  servoMoveTo(F, R, S, 50, false, 100);
  servoMoveTo(F, L, S, 50, false, 100);
  servoMoveTo(R, L, C, -20, false, 100);
  servoMoveTo(R, R, C, -20, false, 100);
  servoMoveTo(F, L, C, 50, false, 30);
  servoMoveTo(F, R, C, 50, true, 30);
  delay(100);

  //main motion
  while(i < count){
    servoMoveTo(F, R, C, 65, false, 60);
    servoMoveTo(F, L, C, 65, true, 60);
    delay(50);
    servoMoveTo(F, R, C, 50, false, 60);
    servoMoveTo(F, L, C, 50, true, 60);
    delay(50);
    i++;
  }
}

void kurekure(int count = 10) {

  // initialization
  servoMoveTo(F, R, C, -45, false);
  servoMoveTo(F, L,  C, -45, false);
  servoMoveTo(R,  R, C,  15, false);
  servoMoveTo(R,  L,  C,  15, true);

  int i = 0; // counter

  // main motion
  while(i < count){

    servoMove(F, R, S, -10, false, 40);
    servoMove(F, L, S, -10, true,  40);
    servoMove(F, R, S, 10, false,  40);
    servoMove(F, L, S, 10, true,   40);
    
   i++;
  }
  
}

void bunbun(int count = 10){

  // initialization
  servoMoveTo(R, L, C, 40, true);
  servoMoveTo(F, R, C, 40, true);
  servoMoveTo(F, R, S, 20, true);

 int i = 0; // counter

  // main motion
  while(i < count){
    
    servoMove(F, R, S, -40, true);
    servoMove(F, R, S, 40, true);
    i++;
  }
}

void kunekune(int count = 10){

  int i = 0;  //counter

  // main motion
  while(i < count){

    servoMoveTo(F, R, C, -40, false);
    servoMoveTo(F, L,  C, -40, true);
    servoMoveTo(R, R, C, -40, false);
    servoMoveTo(R, L,  C, -40, true);

    servoMove(F, R, C, 40, false);
    servoMove(F, L,  C, 40, true);
    servoMove(R, R, C, 40, false);
    servoMove(R, L,  C, 40, true);
    
    i++;
  }
  
}
