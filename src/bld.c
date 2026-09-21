#define BLD_IMPLEMENTATION
#include "bld.h"

int main(int argc, char** argv) {
  rebuild(argc, argv);
  cmd("gcc $(gsl-config --cflags) gsl_wrapper.c image_wrapper.c main.c -O2 -ffast-math "
      "$(gsl-config --libs) -o main");
  cmd("./main");
  return 0;
}
