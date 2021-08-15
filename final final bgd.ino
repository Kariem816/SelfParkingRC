#include <Servo.h>
#define backangle 90
#define leftangle 0
#define rightangle 180
#define Movetime_back 300
#define Movetime_twist 500
#define motor_power 255

Servo scanservo;

const float sideDistMax = 30;
const float backDistMax = 20;

const int servo_pin = 10;
const int trig = 9;
const int echo = 8;

// indicator LED
const int led = 13;

// motor 1 - left
const int enA = 4;
const int inA1 = 2;
const int inA2 = 3;

// motor 2 - right
const int enB = 5;
const int inB1 = 7;
const int inB2 = 6;

int leftdist, backdist, rightdist;

float realdis() {
  //ultrasonic function to measure distance 
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  float duration = pulseIn(echo, HIGH);
  return (duration * 0.034 / 2.0);
  delay(60);
}

void move_backwards() {
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  analogWrite(enB, motor_power);
  analogWrite(enA, motor_power);
}

void twist_left() {
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  analogWrite(enB, motor_power);
  analogWrite(enA, motor_power);
}

void twist_right() {
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  analogWrite(enB, motor_power);
  analogWrite(enA, motor_power);
}

void stop_RC() {
  digitalWrite(enB, LOW);
  digitalWrite(enA, LOW);
}

int measureAvg(){
  int distavg=0;
  for(int i=0;i<10;i++)
  {
    distavg += realdis(); 
  }
    distavg=distavg/10;
    return distavg;
}

void servo_scan() {
  //function to set the servo for 3 entered angles to measure each distance 
  scanservo.write(leftangle);
  delay(1000);
  leftdist = measureAvg();
  Serial.print("left dist = ");
  Serial.println(leftdist);
  scanservo.write(backangle);
  delay(1000);
  backdist = measureAvg();
  Serial.print("back dist = ");
  Serial.println(backdist);
  scanservo.write(rightangle);
  delay(1000);
  rightdist = measureAvg();
  Serial.print("right dist = ");
  Serial.println(rightdist);

}


void setup() {
  scanservo.attach(servo_pin);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  Serial.begin(9600);

  pinMode(enA, OUTPUT);
  pinMode(inA1, OUTPUT);
  pinMode(inA2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(inB1, OUTPUT);
  pinMode(inB2, OUTPUT);

}

void loop() {
  servo_scan();
  bool x, y, z;
  if (leftdist > sideDistMax) {x = true;}
  else {x = false;}
  if (rightdist > sideDistMax) {y = true;}
  else y = false;
  if (backdist > backDistMax) {z = true;}
  else {z = false;}

  if (x == false && y == false) {
    // can't park
    Serial.println("can't park");
  }
  else {
    if (z == false) {
      // parked
      Serial.println("parked");
    }
    else
    {
      if (x == true && y == true) {
        move_backwards();
        delay(Movetime_back);
        stop_RC();
        Serial.println("moving backwards");
        delay(1000);
      }
      else {
        if (x == true) {
          twist_left();
          delay(Movetime_twist);
          stop_RC();
          Serial.println("moving left");
          delay(1000);
        }
        else {
          twist_right();
          delay(Movetime_twist);
          stop_RC();
          Serial.println("moving right");
          delay(1000);
        }
      }
    }
  }
}
