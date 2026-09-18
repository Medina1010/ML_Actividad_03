#define BLD_IMPLEMENTATION
#include "bld.h"

int main(int argc, char** argv) {
  rebuild(argc, argv);
  /*
  cmd("gcc $(gsl-config --cflags) $(gsl-config --libs) "
      "src/main.c "
      "-o src/main");
  cmd("src/main");
  */
  cmd("python main.py");
  return 0;
}
