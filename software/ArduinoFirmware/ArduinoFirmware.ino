#include "vector.cpp"
#include "orientation.cpp"
// #include "hostcommunicator.h"
#include "sensorfusor.h"
#include "motioncoordinator.h"
#include "motorcontroller.h"
#include "ik-solver.h"
#include "DRV8825.h"


DRV8825 stepperLeft = DRV8825(400, 3, 4);
DRV8825 stepperRight = DRV8825(400, 5, 6);

const double MM_PER_SECOND = 1;
const double ARM_LENGTH = 40;
Vector centerPoint = Vector(0, 100);

// CommandListener commandListener = CommandListener();
MotorController motorController = MotorController(stepperLeft, stepperRight);
//MotionCoordinator motionCoordinator = MotionCoordinator(MM_PER_SECOND);
IKSolver iksolver = IKSolver(Vector(0,0), centerPoint, ARM_LENGTH);
// SensorFusor sensorFusor = SensorFusor();

bool intialOrientationSetup = false;
Orientation previousAbsoluteOrientation;

void setup() {
}

int step_delay = 1000;

void loop() {
  KinematicResult targetPosition;
  
  targetPosition = iksolver.solve(Vector(10, 0));
  motorController.updateTargetPosition(targetPosition);
  motorController.update();
  delay(step_delay);
  
  
  targetPosition = iksolver.solve(Vector(10, 10));
  motorController.updateTargetPosition(targetPosition);
  motorController.update();
  delay(step_delay);
  
  
  targetPosition = iksolver.solve(Vector(0, 10));
  motorController.updateTargetPosition(targetPosition);
  motorController.update();
  delay(step_delay);
  
  
  targetPosition = iksolver.solve(Vector(10, 0));
  motorController.updateTargetPosition(targetPosition);
  motorController.update();
  delay(step_delay);
  
  /*motorController.updateTargetPosition(KinematicResult(45, 0));
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
  delay(step_delay);*/

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

