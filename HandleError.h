/*
 * HandleError.h
 *
 *  Created on: 14 февр. 2017 г.
 *      Author: valerius
 */

#ifndef HANDLEERROR_H_
#define HANDLEERROR_H_

#include "Matrix.h"

#define CHECK_NULL(X) HandleNullError (X, __FILE__, __LINE__)
#define ERROR(X) printError (X, __FILE__, __LINE__)

void printError(const char *error, const char *file, int line);
void HandleNullError(const void *var, const char *file, int line);

int checkCorrect (Matrix &input, Matrix &output);

#endif /* HANDLEERROR_H_ */
