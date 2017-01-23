#include "hostcommunicator.h"
#include "Arduino.h"

HostCommunicator::HostCommunicator() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Setup");
}

HostCommand* HostCommunicator::getCommandQueue() {
  return NULL;
}
