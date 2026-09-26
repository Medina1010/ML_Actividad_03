#define BLD_IMPLEMENTATION
#include "bld.h"

int main(int argc, char** argv) {
  rebuild(argc, argv);
  cmd("gcc "
      "$(gsl-config --cflags) "
      "$(gsl-config --libs) "
      "gsl_wrapper.c image_wrapper.c main.c "
      "-o main");
  cmd("./main");
  return 0;
}
