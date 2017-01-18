#include "orientation.cpp"

#ifndef SENSOR_FUSOR_H
#define SENSOR_FUSOR_H

class SensorFusor {
private:

  Orientation lastAbsoluteOrientationUpdate;
  Orientation aggregatedOrientationChanges;
  bool hasOrientationData;

public:

  SensorFusor();

  Orientation readOrientationChange();
  Orientation calculateNewAbsoluteOrientation();
  void setAbsoluteOrientation(Orientation newAbsoluteOrientation);
}

#endif  /* SENSOR_FUSOR_H */
