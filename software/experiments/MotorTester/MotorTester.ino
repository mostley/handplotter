
#include "DRV8825.h"

DRV8825 stepperLeft = DRV8825(400, 3, 4);
DRV8825 stepperRight = DRV8825(400, 5, 6);
int angle = 0;

int enablePin = 15;

void setup() {
  //stepperLeft.setRPM(120);
  stepperLeft.setMicrostep(16);

  //stepperRight.setRPM(120);
  stepperRight.setMicrostep(16);

  pinMode(13, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH);
}

void loop() {
  stepperRight.rotate(-angle);
  stepperLeft.rotate(angle);
  
  if (angle > 0) {
    angle = -90;
  } else {
    angle = 90;
  }
  
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}

