#include "orientation.cpp"
#include "pathsegment.cpp"

#ifndef MOTION_COORDINATOR_H
#define MOTION_COORDINATOR_H

class MotionCoordinator {
private:
  Orientation currentOrientation;
  PathSegment pathSegmentList[5];
  PathSegment* currentPathSegment;
  double currentRelativePathSegment;
  double mmPerSecond;

public:
  MotionCoordinator(double mmPerSecond);

  void updateOrientation(Orientation newOrientation);

  Vector calculatePenOffset(double deltaTime);

  PathSegment findClosestPathSegment();

  PathSegment makePathSegmentRelative(PathSegment pathSegment);
};

#endif /* MOTION_COORDINATOR_H */
