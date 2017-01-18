#include "sensorfusor.h"

SensorFusor::SensorFusor() {
  this.hasOrientationData = false;
  this->aggregatedOrientationChanges = Orientation(Vector(0, 0), 0);
}

Orientation SensorFusor::readOrientationChange() {
  //TODO read mouse data change
  return Orientation();
}

Orientation SensorFusor::calculateNewAbsoluteOrientation() {
  this->aggregatedOrientationChanges += this->readOrientationChange();
  return this->lastAbsoluteOrientationUpdate + this->aggregatedOrientationChanges;
}

void SensorFusor::setAbsoluteOrientation(Orientation newAbsoluteOrientation) {
  this->lastAbsoluteOrientationUpdate = newAbsoluteOrientation;
  this->aggregatedOrientationChanges = Orientation(Vector(0, 0), 0);
}
