#include "orientation.cpp"
#include "path.cpp"

#ifndef HOST_COMMAND_CPP
#define HOST_COMMAND_CPP

int ERROR = 0;
int HOST_COMMAND_ORIENTATION_UPDATE = 1;
int HOST_COMMAND_PATH_UPDATE = 2;
int HOST_COMMAND_PENSTATE_UPDATE = 3;

struct HostCommand {

public:
  int type;
  int x;
  int y;
  int z;
  int w;
  int x2;
  int y2;
  int penState;

  HostCommand(x, y, z, w) {
    this.type = HOST_COMMAND_ORIENTATION_UPDATE;
    this.x = x;
    this.y = y;
    this.z = z;
    this.w = w;
  }

  HostCommand(x1, y1, x2, y2) {
    this.type = HOST_COMMAND_PATH_UPDATE;
    this.x = x1;
    this.y = y1;
    this.x2 = x2;
    this.y2 = y2;
  }

  HostCommand(int penState) {
    this.type = HOST_COMMAND_PENSTATE_UPDATE;
    this.penState = penState;
  }

  Orientation getOrientation() {
    return Orientation(this.x, this.y, this.z, this.w);
  }

  Path getPath() {
    return Path(this.x, this.y, this.x2, this.y2);
  }
}

#endif  /* HOST_COMMAND_CPP */
