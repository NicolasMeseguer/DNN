#ifndef _STRUCT_H_
#define _STRUCT_H_

#include "header.h"

typedef struct neuron{
    double value;
    double *weight;
    double bias;
}neuron;

typedef struct layer{
    int tamneurons;
    neuron *neurons;
    int layertype;
    /*
    * 0 = Output Layer
    * 1 = Fully Connected
    *
    */
}layer;

void fillWeights(double **w1, double ***w2, int numbweights, int wchoice, char **str, int *MTAM);
layer createOutputLayer(int neurons);
layer assignOutputWeights(layer output, int previousLayerNeurons);

#endif // _STRUCT_H_
