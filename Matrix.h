/*
 * Matrix.h
 *
 *  Created on: 14 февр. 2017 г.
 *      Author: valerius
 */

#include <cmath>
#include "HandleError.h"

#ifndef MATRIX_H_
#define MATRIX_H_

#define MAX_BLOCKS 128
#define MAX_LENG 1024
#define BLOCK_SIZE 16

#define GCD(x,y) {double a = x;\
  double b = y;                \
  if (a < 0) {                 \
    a = -a;                    \
  }                            \
  if (a < epsilon) {           \
    a = b;                     \
  } else {                     \
  if (b < 0) {                 \
    b = -b;                    \
  }                            \
  while (b > epsilon) {        \
    double temp = b;           \
    b = a - b * floor(a / b);  \
    a = temp;                  \
  }                            \
  }                            \
  x /= a;                      \
  y /= a;}

struct Matrix {
  int rows;
  int cols;
  int supply;
  int m;
  double *e;

  Matrix(int rows, int cols, int supply = 0);
  Matrix (int rows, int cols, unsigned int flag, int supply = 0);
  Matrix(char const *file_name, int supply = 0);
  Matrix(Matrix const &input, int supply = 0);
  Matrix(Matrix const &input, unsigned int flag, int supply = 0);
  ~Matrix();
  void freeHost();
  int print(char const *filename) const;
  int print_task(char const *filename) const;
  int add_cuts(Matrix const &cuts);
  Matrix &operator=(Matrix const &matrix);
};


#endif /* MATRIX_H_ */
