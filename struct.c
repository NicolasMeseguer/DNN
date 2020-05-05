#include "struct.h"
layer createOutputLayer(int neurons){
    layer output;
    output.layertype = 0;
    output.tamneurons = neurons;
    output.neurons = (neuron *)malloc(sizeof(neuron)*neurons);
    return output;
}

layer assignOutputWeights(layer output, int previousLayerNeurons){
    srand(time(NULL));
    for(int i=0;i<output.tamneurons;++i){
        output.neurons[i].weight = (double *)malloc(sizeof(double)*previousLayerNeurons);
        for(int j=0;j<previousLayerNeurons;++j){
            output.neurons[i].weight[j] = randomNumberOutput();
        }
    }
    return output;
}

int convolvSize(int MSize, int WSize){
    int tempmatrixsize=0;
    for(int i=0;i<MSize;++i){
        if(i+WSize<=MSize) tempmatrixsize++;
    }
    return tempmatrixsize;
}
