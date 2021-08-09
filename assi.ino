#include <Servo.h>

Servo scanservo;

const int trig = 13;
const int echo = A1; 
const int sideDistMax = 50;
const int backDistMax = 50;
const int Movetime = 1000;

// motor 1
const int enA = 3;
const int inA1 = 2;
const int inA2 = 4;

// motor 2
const int enB = 5;
const int inB1 = 6;
const int inB2 = 7;

void turnServo(int angle_1, int angle_2, Servo mys){
  for (int pos = angle_1; pos <= angle_2; pos += 1) {
      mys.write(pos);
      delay(15);
    }
}

float realdis(int trigpin, int echopin){//ultrasonic function to measure distance 
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  int duration = pulseIn(echopin, HIGH);
  return (duration * 343.0 / 20000.0);
  delay(60);
}

void servo_scan(int leftangle, float leftdist, int backangle, float backdist, int rightangle, float rightdist, Servo mys){//function to set the servo for 3 entered angles to measure each distance 
  turnServo(0, leftangle, mys);
  delay(60);
  leftdist = realdis(trig, echo);
  Serial.print("Left distance = ");
  Serial.println(leftdist);
  turnServo(leftangle, backangle, mys);
  delay(60);
  backdist = realdis(trig, echo);
  Serial.print("Back distance = ");
  Serial.println(backdist);
  turnServo(backangle, rightangle, mys);
  delay(60);
  rightdist = realdis(trig, echo);
  Serial.print("Right distance = ");
  Serial.println(rightdist);
}

void setup() {
  scanservo.attach(3);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  float backdist;
  float rightdist;
  float leftdist;
  int done = 0;
  servo_scan(45, leftdist, 90, backdist, 135, rightdist, scanservo);
  delay(60);

  while(done = 0){
    if(rightdist > sideDistMax && leftdist > sideDistMax && backdist > backDistMax)
      // go back
    else if(backdist < backDistMax){
      // stop
      done = 1;
      }
    else if(rightdist > sideDistMax)
      //go back & right
    else if(leftdist > sideDistMax)
      // go back & left
    else{
      //go back
    }
  }
  for (int pos = 180; pos >= 0; pos -= 1) {
    scanservo.write(pos);
    delay(15);
    }
}
