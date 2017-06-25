#include "TransitionMatrix.h"
#include "MatrixMultip.h"
#include "Epsilon.h"

int trans_init(Matrix &transition, Matrix &input) {
  const int side = input.cols;

  for (int i = 0; i < transition.m; i++) {
    transition.e[i + i * transition.m] = 1.0;
  }//identity mantrix
  for (int j = 0; j < side; j++) {
    for (int i = 1; i < side; i++) {
      transition.e[i + j * transition.m] = - input.e[i + j * input.m];
      if (cmp(input.e[i + j * input.m], 0.0) == 0) {
        transition.e[i + j * input.m] = 0.0;
      }
    }
  }

  return 0;
}
