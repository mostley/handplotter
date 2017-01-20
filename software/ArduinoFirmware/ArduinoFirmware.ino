#include "vector.cpp"
#include "orientation.cpp"
#include "hostcommunicator.h"
#include "sensorfusor.h"
#include "motioncoordinator.h"
#include "motorcontroller.h"

CommandListener commandListener;
MotorController motorController;
MotionCoordinator motionCoordinator;
SensorFusor sensorFusor;

bool intialOrientationSetup = false
Orientation previousAbsoluteOrientation;

void setup() {
  commandListener = new CommandListener();
  sensorFusor = new SensorFusor();
  motionCoordinator = new MotionCoordinator();
  DRV8825 stepperLeft(200, 3, 4);
  DRV8825 stepperRight(200, 5, 6);
  motorController = new MotorController(stepperLeft, stepperRight);
}

void loop() {

  /*HostCommand[] hostCommands = commandListener.getCommandQueue();

  int hostCommandCount = sizeof(hostCommands)/sizeof(*hostCommands);
  for (int i=0; i<hostCommandCount; i++) {
    handleHostCommand(hostCommands[i]);
  }

  if (!sensorFusor.hasOrientationData {
    return;
  }

  Orientation currentAbsoluteOrientation = sensorFusor.calculateNewAbsoluteOrientation();
  if (intialOrientationSetup) {
    Vector newPenOffset = motionCoordinator.calculateNewPenOffset(previousAbsoluteOrientation, currentAbsoluteOrientation, currentPath);
    motorController.updatePenOffset(newPenOffset);

    motorController.update(deltaTime);
  } else {
    intialOrientationSetup = true;
  }

  previousAbsoluteOrientation = currentAbsoluteOrientation;
  */

  motorController.update();
}

void handleHostCommand(HostCommand command) {
  if (command.type == HOST_COMMAND_ORIENTATION_UPDATE) {
    Orientation absoluteOrientationUpdateFromHost = command.getOrientation();
    sensorFusor.setAbsoluteOrientation(absoluteOrientationUpdateFromHost);
  } else {
    // TODO
  }
}

void main() {

}
