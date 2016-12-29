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

double STEPS_PER_MM = 10; //TODO calculate steps per MM

bool intialOrientationSetup = false
Orientation previousAbsoluteOrientation;

void setup() {
  commandListener = new CommandListener();
  sensorFusor = new SensorFusor();
  motionCoordinator = new MotionCoordinator();
  motorController = new MotorController(STEPS_PER_MM);
}

void loop() {

  HostCommand[] hostCommands = commandListener.getCommandQueue();

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