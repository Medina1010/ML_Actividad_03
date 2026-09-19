#define BLD_IMPLEMENTATION
#include "bld.h"

int main(int argc, char** argv) {
  rebuild(argc, argv);
  cmd("cd src && ./bld");
  return 0;
}
