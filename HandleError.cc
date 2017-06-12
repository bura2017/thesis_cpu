#include "HandleError.h"

#include <iostream>
#include <cstdlib>

void printError(const char *error, const char *file, int line) {
  std::cout <<"ERROR " << error << " in " << file << " at line " << line << std::endl;
  exit( EXIT_FAILURE );
}
void HandleNullError(const void *var, const char *file, int line) {
  if (var == NULL) {
    printError ("NULL", file, line);
  }
}
