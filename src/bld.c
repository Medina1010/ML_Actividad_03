#define BLD_IMPLEMENTATION
#include "bld.h"

int main(int argc, char** argv) {
  rebuild(argc, argv);
  cmd("gcc $(gsl-config --cflags) -c gsl_wrapper.c image_wrapper.c main.c");
  cmd("gcc $(gsl-config --libs) -o main *.o");
  //cmd("rm *.o");
  cmd("./main");
  return 0;
}
