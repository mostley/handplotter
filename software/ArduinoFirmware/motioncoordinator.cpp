#include "motioncoordinator.h"


MotionCoordinator::MotionCoordinator(double mmPerSecond) {
  this->mmPerSecond = mmPerSecond;
};

//void MotionCoordinator::updatePathSegmentList(PathSegment* pathSegmentList) {
//  this->pathSegmentList = pathSegmentList;
//}

void MotionCoordinator::updateOrientation(Orientation newOrientation) {
  this->currentOrientation = newOrientation;
}

PathSegment MotionCoordinator::findClosestPathSegment() {
  return PathSegment(Vector(0, 0), Vector(0, 0));
}

PathSegment MotionCoordinator::makePathSegmentRelative(PathSegment pathSegment) {
  return pathSegment * this->currentOrientation;
}

Vector MotionCoordinator::calculatePenOffset(double deltaTime) {
//  if (this->currentRelativePathSegment == NULL) {
//    this->currentRelativePathSegment = this->findClosestPathSegment();
//  }
//
//  double distanceToTravel = this->mmPerSecond * deltaTime;
//
//  double segmentLength = this->currentRelativePathSegment.length();
//  Vector pathTarget = this->currentRelativePathSegment.p2;
//  if (segmentLength > distanceToTravel) {
//    double lengthToTravelOnSegment = semgentLengthLeft;
//    Vector direction = this->currentRelativePathSegment.getNormalizedDirectionVector();
//    pathTarget = this->currentRelativePathSegment.p1 + direction * (this->currentRelativePathSegmentProgress * lengthToTravelOnSegment);
//  }

//  return pathTarget;
return Vector(0, 0);
}
