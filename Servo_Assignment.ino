#include <Servo.h>

Servo myservo;
const int trig = 7;
const int echo = 8;

void SerialReadServo(){
  String value;
  int pos = 0, angle;
  while(Serial.available()){
    value += (char)Serial.read();
    delay(10);
  }
  angle = value.toInt();
  if(angle != 0){
    Serial.println(angle);
    for (pos = 0; pos <= angle; pos += 1) {
      myservo.write(pos);
      delay(15);
    }
    for (pos = angle; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
  }
  delay(500);
}

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
}

void loop() {
  SerialReadServo();
}
