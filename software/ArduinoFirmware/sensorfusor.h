#include "orientation.cpp"

#ifndef SENSOR_FUSOR_H
#define SENSOR_FUSOR_H

class SensorFusor {
private:

  Orientation lastAbsoluteOrientationUpdate;
  bool hasOrientationData;

public:

  SensorFusor();

  Orientation calculateNewAbsoluteOrientation();

  void setAbsoluteOrientation(Orientation newAbsoluteOrientation) {
    this.lastAbsoluteOrientationUpdate = newAbsoluteOrientation;
  }
}

#endif  /* SENSOR_FUSOR_H */
