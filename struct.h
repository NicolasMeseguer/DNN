#ifndef _STRUCT_H_
#define _STRUCT_H_

#include "header.h"

typedef struct neuron{
    double value;
    double *weight;
    double *filter;
    double *mvalue;
    double bias;
}neuron;

typedef struct layer{
    int tamneurons;
    neuron *neurons;
    int layertype;
    /*
    * 0 = Output Layer
    * 1 = Fully Connected
    * 2 = Convolution Layer
    *
    */
}layer;

layer createOutputLayer(int neurons);
layer assignOutputWeights(layer output, int previousLayerNeurons, int choice, int filtersize);
int convolvSize(int MSize, int WSize);

#endif // _STRUCT_H_
