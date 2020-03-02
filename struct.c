#include "struct.h"
void fillWeights(double **w1, double ***w2, int numbweights, int wchoice, char **str, int *MTAM){
    srand(time(NULL));
    if(wchoice==2){ //Matrix
        int memsize;
        *str = "in the matrices ?";
        printf("\nType in the size of the Matrices, assuming square matrices(e.g. 5 = 5x5; 7 = 7x7): ");fflush(stdin);scanf("%i", &(*MTAM));
        memsize = (*MTAM)*(*MTAM);
        *w2 = (double**) malloc(sizeof(double*)*numbweights);
        for(int i=0; i<numbweights; ++i){
            *(*(w2)+i) = (double*)malloc(sizeof(double)*memsize);
            for(int j=0; j<memsize; ++j)
                *(*(*(w2)+i)+j) = (double)((rand()%30)-10);
        }
    }
    else{ //Doubles
        *str = "in the doubles ?";
        *w1 = (double*) malloc(sizeof(double)*numbweights);
        for(int i=0; i<numbweights; ++i)
            *(*(w1)+i) = (double)((rand()%30)-10);
    }
}

layer createOutputLayer(int neurons){
    layer output;
    output.layertype = 0;
    output.tamneurons = neurons;
    output.neurons = (neuron *)malloc(sizeof(neuron)*neurons);
    return output;
}

layer assignOutputWeights(layer output, int previousLayerNeurons){
    for(int i=0;i<output.tamneurons;++i){
        output.neurons[i].weight = (double *)malloc(sizeof(double)*previousLayerNeurons);
        for(int j=0;j<previousLayerNeurons;++j){
            output.neurons[i].weight[j] = (double)(rand()%2);
        }
    }
    return output;
}
