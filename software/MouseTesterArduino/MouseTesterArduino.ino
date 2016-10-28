
#include <Servo.h>

Servo servoLeft;
Servo servoRight;

int servo0Pin = 2;
int servo1Pin = 3;

void setup() {
  servoLeft.attach(servo0Pin);
  servoRight.attach(servo1Pin);
  
  Serial.begin (9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  if (Serial.available() > 0) {
    float x = Serial.parseFloat();
    Serial.read();
    float y = Serial.parseFloat();

    servoLeft.write(x);
    servoRight.write(y);
  }
   
  delay(15);
}

