//セットアップ用
//angle = 90

int pos = 90;

#include<Servo.h>

Servo FR1;
Servo FR2;

Servo FL1;
Servo FL2;

Servo RR1;
Servo RR2;

Servo RL1;
Servo RL2;

void setup(){
 Serial.begin(9600);

  FR1.attach(2);
  FR2.attach(3);
  FL1.attach(4);
  FL2.attach(5);

  RR1.attach(10);
  RR2.attach(11);
  RL1.attach(12);
  RL2.attach(13);
}


void loop(){
 //if (Serial.available() > 0){
  // int pos = Serial.read();
// for (pos = 0; pos <= 180; pos += 15) {
    FR1.write(pos);
    FR2.write(pos);
    FL1.write(pos);
    FL2.write(pos);

    RR1.write(pos);
    RR2.write(pos);
    RL1.write(pos);
    RL2.write(pos);

 //   delay(100);
 }
/*
  for (pos = 180; pos >= 0; pos -= 15) {
    AA.write(pos);
    AB.write(pos);
    BA.write(pos);
    BB.write(pos);

    CA.write(pos);
    CB.write(pos);
    DA.write(pos);
    DB.write(pos);

    delay(100);
  }

 // }
*/
//}
