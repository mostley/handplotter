#include "orientation.cpp"

#ifndef MOTION_COORDINATOR_H
#define MOTION_COORDINATOR_H

class MotionCoordinator {
private:
  Orientation currentOrientation;
  PathSegment[] pathSegmentList;
  PathSegment* currentPathSegment;
  double currentPathSegmentProgress;
  double mmPerSecond;

public:
  MotionCoordinator(double mmPerSecond);

  void updateOrientation(Orientation newOrientation);

  Vector calculatePenOffset(double deltaTime);
};

#endif /* MOTION_COORDINATOR_H */
