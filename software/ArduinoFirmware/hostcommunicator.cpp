#include "hostcommunicator.h"

HostCommunicator::HostCommunicator() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Setup");
}

HostCommand[] HostCommunicator::getCommandQueue() {
  HostCommand result[0];
  return result;
}