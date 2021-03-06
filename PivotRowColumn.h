/*
 * PivotRowColumn.h
 *
 *  Created on: 12 июня 2017 г.
 *      Author: valerius
 */

#ifndef PIVOTROWCOLUMN_H_
#define PIVOTROWCOLUMN_H_

#include "Matrix.h"

#define SHARED_MEM_SIZE 1024

int pivotRow(Matrix const &matrix);
int pivotColumn(Matrix const &matrix, const int row);

#endif /* PIVOTROWCOLUMN_H_ */
