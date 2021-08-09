#include <Servo.h>
Servo scanservo;
#define trig 2
#define echo A1 

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
  turnServo(leftangle, backangle, mys);
  delay(60);
  backdist = realdis(trig, echo);
  turnServo(backangle, rightangle, mys);
  delay(60);
  rightdist = realdis(trig, echo);
}

void setup() {
  scanservo.attach(3);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  float backdis;
  float rightdis;
  float leftdis;
  servo_scan(45, leftdis, 90, backdis, 135, rightdis, scanservo);
  delay(60);
  
  
  for (int pos = 180; pos >= 0; pos -= 1) {
    scanservo.write(pos);
    delay(15);
    }
}
