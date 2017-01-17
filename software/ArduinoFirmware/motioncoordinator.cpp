
MotionCoordinator::MotionCoordinator(double mmPerSecond) {
  this->mmPerSecond = mmPerSecond;
}

void MotionCoordinator::updatePathSegmentList(PathSegment[] pathSegmentList) {
  this->pathSegmentList = pathSegmentList;
}

void MotionCoordinator::updateOrientation(Orientation newOrientation) {
  this->currentOrientation = newOrientation;
}

findClosestPathSegment(Vector position) {
  return PathSegment(0, 0);
}

Vector MotionCoordinator::calculatePenOffset(double deltaTime) {
  if (this->currentPathSegment == NULL) {
    this->currentPathSegment = this->findClosestPathSegment(this->currentOrientation.position);
  }

  double distanceToTravel = this->mmPerSecond * deltaTime;

  double segmentLength = this->currentPathSegment.length();
  double semgentLengthLeft = (1 - this->currentPathSegmentProgress) * segmentLength;
  double lengthToTravelOnSegment = semgentLengthLeft;
  if (distanceToTravel > semgentLengthLeft) {
    // go to another path position directly?
    // get next path and find point to travel to on that, hopefully minor error in movement
  } else if (semgentLengthLeft < distanceToTravel) {
    lengthToTravelOnSegment = distanceToTravel;
  }

  Vector direction = this->currentPathSegment.getNormalizedDirectionVector()
  Vector position = this->currentPathSegment.p1 + direction * (this->currentPathSegmentProgress * lengthToTravelOnSegment);

  return position;
}
