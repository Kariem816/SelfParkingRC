#include <Servo.h>
Servo scanservo;
#define trig 2
#define echo A1 

float realdis(int trigpin,int echopin){//ultrasonic function to return the distance
digitalWrite(trigpin,HIGH);
delayMicroseconds(10);
digitalWrite(trigpin,LOW);
return (pulseIn(echopin,HIGH))*343.0/10000.0/2.0;
delay(60);
}


void servo_scan(int leftangle,float leftdist,int backangle,float backdist,int rightangle,float rightdist,Servo mys){//function to sit the servo for 3 entered angles to measure each distance 
  mys.write(leftangle);
  delay(60);
  leftdist = realdis(2,A1);
  mys.write(backangle);
  delay(60);
  backdist = realdis(2,A1);
  mys.write(rightangle);
  delay(60);
  rightdist = realdis(2,A1);
  }

void setup() {
scanservo.attach(3);
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
}
void loop() {
float backdis;
float rightdis;
float leftdis;
servo_scan(45,leftdis,90,backdis,135,rightdis,scanservo);
delay(60);      
}
