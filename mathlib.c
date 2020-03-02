#include "mathlib.h"

//Given two(2) numbers, returns the max.
double max(double a, double b){
    if(a>b)
        return a;
    else
        return b;
}

//ReLU activation function
double ReLU(double x){
    return max(0, x);
}

//Sigmoid activation function
double sigmoid(double x){
    return 1 / (1 + exp(-x));
}

//Derivative sigmoid activation function
double dSigmoid(double x){
    double r = 1-x;
    return (x * r);
}
