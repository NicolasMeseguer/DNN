#include "struct.h"
layer createOutputLayer(int neurons){
    layer output;
    output.layertype = 0;
    output.tamneurons = neurons;
    output.neurons = (neuron *)malloc(sizeof(neuron)*neurons);
    return output;
}

layer assignOutputWeights(layer output, int previousLayerNeurons, int choice, int filtersize){
    for(int i=0;i<output.tamneurons;++i){
        if(choice==1){
            output.neurons[i].weight = (double *)malloc(sizeof(double)*previousLayerNeurons);
            for(int j=0;j<previousLayerNeurons;++j){
                output.neurons[i].weight[j] = (double)(rand()%2);
            }
        }
        else{
            int memsize = filtersize*filtersize;
            output.neurons[i].filter = (double*)malloc(sizeof(double)*memsize);
            for(int j=0;j<memsize;++j){
                output.neurons[i].filter[j] = (double)((rand()%3)-2);
            }
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
