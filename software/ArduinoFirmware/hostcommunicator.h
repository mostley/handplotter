#include "orientation.cpp"
#include "hostcommand.cpp"

#ifndef HOST_COMMUNICATOR_H
#define HOST_COMMUNICATOR_H

class HostCommunicator {
public:

  HostCommunicator();

  HostCommand[] getCommandQueue();
}

#endif  /* HOST_COMMUNICATOR_H */
