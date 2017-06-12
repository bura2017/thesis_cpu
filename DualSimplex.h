/*
 * DualSimplex.h
 *
 *  Created on: 15 февр. 2017 г.
 *      Author: valerius
 */

#ifndef DUALSIMPLEX_H_
#define DUALSIMPLEX_H_

#include "HandleError.h"
#include "Matrix.h"

int cpuDualSimplex (Matrix &matrix);
int cpuDualSimplex (Matrix &matrix, Matrix &transition);

#endif /* DUALSIMPLEX_H_ */
