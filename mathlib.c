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

//Given two contiguous matrices, multiply them and return the value
double addMatrices(double *a, double *b, int MSize){
    double tempvalue = 0.0f;
    int memsize = MSize*MSize;
    for(int i=0;i<memsize;++i){
        tempvalue += (*(a+i))*(*(b+i));
    }
    return tempvalue;
}

//Return the highest value given an array of size: MSize*MSize
double getMajor(double *a, int MSize){
    int memsize = MSize*MSize;
    double tempvalue = -DBL_MAX;
    for(int i=0;i<memsize;++i){
        if(*(a+i)>tempvalue) tempvalue = *(a+i);
    }
    return tempvalue;
}

//Return the average sum of all the items in the matrix
double getAverage(double *a, int MSize){
    int memsize = MSize*MSize;
    double tempvalue = 0;
    for(int i=0;i<memsize;++i){
        tempvalue += *(a+i);
    }
    return (double)tempvalue/memsize;
}

//Return a number between [-1, 0, 1]
double randomNumberFilter(){
    double r;
    double tempv = rand()%2;
    if(tempv==0) r=0.0f;
    else if(tempv==1) r=1.0f;

    return r;
}

double randomNumberOutput(){
    double r;
    double tempv = rand()%2;
    if(tempv==0) r=0.0f;
    else if(tempv==1) r=1.0f;

    return r;
}
