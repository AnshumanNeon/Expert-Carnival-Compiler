#include <stdio.h>

bool print_error(int line, int col, const char* msg) {
  printf("%d:%d %s", line, col, msg);
  return true;
}
