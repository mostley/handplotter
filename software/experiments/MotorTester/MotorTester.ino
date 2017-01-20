
#include "DRV8825.h"

DRV8825 stepperLeft = DRV8825(400, 10, 11);
DRV8825 stepperRight = DRV8825(400, 12, 14);
int angle = 0;

int enablePin = 15;

void setup() {
  //stepperLeft.setRPM(120);
  //stepperLeft.setMicrostep(DRV8825::MAX_MICROSTEP);

  //stepperRight.setRPM(120);
  //stepperRight.setMicrostep(DRV8825::MAX_MICROSTEP);

  pinMode(13, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH);
}

void loop() {
  stepperLeft.rotate(angle);
  stepperRight.rotate(angle);
  
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

