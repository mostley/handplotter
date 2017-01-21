#include "vector.cpp"
#include "orientation.cpp"
// #include "hostcommunicator.h"
#include "sensorfusor.h"
#include "motioncoordinator.h"
#include "motorcontroller.h"
#include "StepperDriver/DRV8825.h"


DRV8825 stepperLeft = DRV8825(400, 3, 4);
DRV8825 stepperRight = DRV8825(400, 5, 6);
int angle = 0;

// CommandListener commandListener;
MotorController motorController = MotorController(stepperLeft, stepperRight);
// MotionCoordinator motionCoordinator;
// SensorFusor sensorFusor;

bool intialOrientationSetup = false;
Orientation previousAbsoluteOrientation;

void setup() {
  //commandListener = CommandListener();
  //sensorFusor = SensorFusor();
  //motionCoordinator = MotionCoordinator();
}
int step_delay = 1000;

void loop() {
//  stepperRight.rotate(-angle);
//  stepperLeft.rotate(angle);
  motorController.updateTargetPosition(KinematicResult(45, 0));
  motorController.update(0);
  delay(step_delay);
  motorController.updateTargetPosition(KinematicResult(45, 45));
  motorController.update(0);
  delay(step_delay);
  motorController.updateTargetPosition(KinematicResult(0, 45));
  motorController.update(0);
  delay(step_delay);
  motorController.updateTargetPosition(KinematicResult(0, 0));
  motorController.update(0);
  delay(step_delay);
  
//  digitalWrite(13, HIGH);
//  delay(1000);
//  digitalWrite(13, LOW);
//  delay(1000);

//  HostCommand[] hostCommands = commandListener.getCommandQueue();
//
//  int hostCommandCount = sizeof(hostCommands)/sizeof(*hostCommands);
//  for (int i=0; i<hostCommandCount; i++) {
//    handleHostCommand(hostCommands[i]);
//  }
//
//  if (!sensorFusor.hasOrientationData {
//    return;
//  }
//
//  Orientation currentAbsoluteOrientation = sensorFusor.calculateNewAbsoluteOrientation();
//  if (intialOrientationSetup) {
//    Vector newPenOffset = motionCoordinator.calculateNewPenOffset(previousAbsoluteOrientation, currentAbsoluteOrientation, currentPath);
//    motorController.updatePenOffset(newPenOffset);
//
//    motorController.update(deltaTime);
//  } else {
//    intialOrientationSetup = true;
//  }
//
//  previousAbsoluteOrientation = currentAbsoluteOrientation;
}

//void handleHostCommand(HostCommand command) {
//  if (command.type == HOST_COMMAND_ORIENTATION_UPDATE) {
//    Orientation absoluteOrientationUpdateFromHost = command.getOrientation();
//    sensorFusor.setAbsoluteOrientation(absoluteOrientationUpdateFromHost);
//  } else {
//    // TODO
//  }
//}

