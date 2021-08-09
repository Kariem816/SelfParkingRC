#include <Servo.h>

Servo scanservo;
int done = 0;
const int led = 12;
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

float realdis(int trigpin, int echopin){//ultrasonic function to measure distance 
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  int duration = pulseIn(echopin, HIGH);
  return (duration * 343.0 / 20000.0);
  delay(60);
}

void move_backwards(int in1,int in2,int en){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(en,255);
}
void stop(int in11,int in22,int en1){
digitalWrite(in11,LOW);
digitalWrite(in22,LOW);
digitalWrite(en1,LOW);  
}

void servo_scan(int leftangle, float leftdist, int backangle, float backdist, int rightangle, float rightdist, Servo mys){//function to set the servo for 3 entered angles to measure each distance 
  mys.write(leftangle);
  delay(60);
  leftdist = realdis(trig, echo);
  Serial.print("Left distance = ");
  Serial.println(leftdist);
  mys.write(backangle);
  delay(60);
  backdist = realdis(trig, echo);
  Serial.print("Back distance = ");
  Serial.println(backdist);
  mys.write(rightangle);
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
  if(done==0){
  float backdist;
  float rightdist;
  float leftdist;
  servo_scan(45, leftdist, 90, backdist, 135, rightdist, scanservo);
  delay(60);

    if(rightdist > sideDistMax && leftdist > sideDistMax && backdist > backDistMax){
      // go back
      move_backwards(inA1,inA2,enA);
      move_backwards(inB1,inB2,enB);
    }
    else if(backdist < backDistMax){
      stop(inA1,inA2,enA);
      stop(inB1,inB2,enB);
      done = 1;
      }
    else if(rightdist > sideDistMax){
      //go back & right
      move_backwards(inB1,inB2,enB);
      stop(inA1,inA2,enA);
    }
    else if(leftdist > sideDistMax){
      // go back & left
      move_backwards(inA1,inA2,enA);
      stop(inB1,inB2,enB);
    }
    else{
      //go back
      move_backwards(inA1,inA2,enA);
      move_backwards(inB1,inB2,enB);
    }
     delay(Movetime); 
  } 
  else{digitalWrite(led,HIGH);}
}
