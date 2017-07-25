#include <social_pods.h>

void setup() {
  // put your setup code here, to run once:
  
  servo[F][R][S].attach(2);
  servo[F][R][C].attach(3);
  servo[F][L][S].attach(4);
  servo[F][L][C].attach(5);
  servo[R][R][S].attach(10);
  servo[R][R][C].attach(11);
  servo[R][L][S].attach(12);
  servo[R][L][C].attach(13);
  
  // Calibrate motor defualt position here
  

  initialize_pose();
}

void loop() {
  // put your main code here, to run repeatedly:

  forward(0);
}