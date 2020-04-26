#ifndef _MATHLIB_H_
#define _MATHLIB_H_

#include "header.h"

double max(double a, double b);
double ReLU(double x);
double sigmoid(double x);
double dSigmoid(double x);
double addMatrices(double *a, double *b, int MSize);
double getMajor(double *a, int MSize);

#endif // _MATHLIB_H_
