#ifndef BLD_H
#define BLD_H

int cmd(char *prompt);
int rebuild(int argc, char **argv);
int std_compile(char *name);

#ifdef BLD_IMPLEMENTATION

#include <stdlib.h>
#include <stdio.h>

int cmd(char *prompt) {
  printf("[BLD]: %s\n", prompt);
  return system(prompt);
}

int rebuild(int argc, char **argv) {
  if (argc == 1) {
    std_compile("bld");
    cmd("./bld RBD");
    exit(0);
  }
  return 0;
}

int std_compile(char *name) {
  char compile_cmd_fmt[] = "gcc -o %s %s.c";
  char compile_cmd[sizeof(compile_cmd_fmt) + 2 * strlen(name)];
  sprintf(compile_cmd, compile_cmd_fmt, name, name);
  return cmd(compile_cmd);
}

#endif // BLD_IMPLEMENTATION

#endif // BLD_H
