#include <Encoder.h>

#include <Servo.h>

Servo servoLeft;
Servo servoRight;

int pos = 0;

int servo0Pin = 2;
int servo1Pin = 3;

Encoder knobLeft(4, 5);
Encoder knobRight(6, 7);
 
float positionLeft  = -999;
float positionRight = -999;

void setup() {
  servoLeft.attach(servo0Pin);
  servoRight.attach(servo1Pin);
  
  Serial.begin (9600);
}

void loop() {
  
  long newLeft, newRight;
  newLeft = knobLeft.read() / 3.0;
  newRight = knobRight.read() / 3.0;
  
  if (newLeft != positionLeft) {
    positionLeft = newLeft;
    servoLeft.write(positionLeft);
  }
  
  if (newRight != positionRight) {
    positionRight = newRight;
    servoRight.write(positionRight);
  }
  
  delay(15);
}

