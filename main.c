#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define strTAM 155 //Default size for Strings

/*
*   Knowledge:
*       Small input activations (-10, 10)
*
*
*   Objectives:
*       Random weights
*
*
*/
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

void showWeights(char *str, int wchoice, int w1count, int MTAM, double *w1, double **w2){
    char opt;
    printf("\nWould you like to see the input weights generated %s (Y/N) - ", str);fflush(stdin);scanf("%c", &opt);
    if(opt=='Y'||opt=='y'){
        if(wchoice==2) {
            printf("\n\n--------------------");
            int memsize = MTAM*MTAM;
            for(int i=0; i<w1count; i++){
                printf("\nw%i:\n", i);
                for(int j=0;j<memsize;++j){
                    printf("%f ", *(*(w2)+j));
                    if(j!=0 && (j+1)%MTAM==0)
                        printf("\n");
                }
            printf("--------------------");
            }
        }
        else{
            printf("\n\n--------------------");
            for(int i=0;i<w1count;++i){
                printf("\nw%i:   %f",i,*(w1+i));
                printf("\n--------------------");
            }
            printf("\n\n");
        }
    }
}

void showNeurons(int layercount, layer *layers){
    char opt;
    printf("Would you like to see all the Neurons in the model ?(Y/N): ");fflush(stdin);scanf("%c", &opt);
    if(opt=='Y' || opt=='y'){
        for(int i=0;i<layercount;++i){
            for(int j=0;j<(layers+i)->tamneurons;++j)
                printf("\nNeuron %i-%i: %f",i,j,layers[i].neurons[j].value);
            printf("\n\n");
        }
    }

}

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
                *(*(*(w2)+i)+j) = (double)((rand()%20)-10);
        }
    }
    else{ //Doubles
        *str = "in the doubles ?";
        *w1 = (double*) malloc(sizeof(double)*numbweights);
        for(int i=0; i<numbweights; ++i)
            *(*(w1)+i) = (double)((rand()%20)-10);
    }
}

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
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

//Derivative sigmoid activation function
double dSigmoid(double x) {
    double r = 1-x;
    return (x * r);
}

void menu(int opt){
    switch(opt){
        case 1:
            printf("--------------------\nSTEP 1 - Input Weights\n--------------------\n");
            break;
        case 2:
            printf("\n--------------------\nSTEP 2 - Design Model\n--------------------\n");
            break;
        case 3:
            printf("\n--------------------\nSTEP 3 - Operations Weights\n--------------------\n");
            break;
        case 4:
            printf("\n--------------------\nSTEP 4 - Output\n--------------------\n");
            break;
    }
    return;
}

int printmodelopt(){
    int choice;
    printf("1 - FC, 3 layers, 3 neuron each.");
    printf("\n2 - TBD.");
    printf("\n3 - TBD.");
    printf("\n4 - TBD.");
    printf("\n5 - TBD.");
    printf("\nSelect one of the templates: ");fflush(stdin);scanf("%i", &choice);
    return choice;
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

void showOutput(layer outputLayer){
    for(int i=0;i<outputLayer.tamneurons;++i){
        printf("\nOutput neuron %i: %f", i, outputLayer.neurons[i].value);
    }
}

int main()
{
    int w1count,wchoice, MATTAM, layercount;
    /*
    *   w1count     - number of input weights
    *   wchoice     - type of the input weights, choice decided by the user, matrices or doubles
    *   MATTAM      - controls the TAM of the matrices
    *   layercount  - number of layers
    */
    char *str = (char*)malloc(sizeof(char)*strTAM);         //String to control the messages
    double *w1;                                             //Doubles Array
    double **w2;                                            //Matrices Array
    layer *layers;                                          //Array of layers, not counting with the input weights
    layer output = createOutputLayer(2);                      //Our output layer will have 2 neurons

    /**/
    //Select input weights, its type & fill them.
    menu(1);
    printf("Number of input weights(w1count): ");fflush(stdin);scanf("%i", &w1count);
    printf("\n%i input weights, select its type:\n1 - Doubles(w1).\n2 - Matrices(w2).\nType: ", w1count);fflush(stdin);scanf("%i", &wchoice);
    if(wchoice!=1&&wchoice!=2) return 0; fillWeights(&w1, &w2, w1count, wchoice, &str, &MATTAM); showWeights(str, wchoice, w1count, MATTAM, w1, w2);

    /**/
    //Design the Network(Model)(Layers, Type(FC,Conv,...)
    menu(2);
    switch(printmodelopt()){
        case 1:
            layercount = 3; //3 layers & 3 neurons each layer .3*3
            layers = (layer*)malloc(sizeof(layer)*layercount);
            for(int i=0;i<layercount;++i){
                (layers+i)->tamneurons = layercount; //Assuming we have 3 neurons in each layer
                (layers+i)->neurons = (neuron *)malloc(sizeof(neuron)*((layers+i)->tamneurons));  //In each layer we have neurons[tamneurons]
                for(int j=0;j<(layers+i)->tamneurons;++j){
                    if(i==0){
                        (layers+i)->neurons[j].weight = (double *)malloc(sizeof(double)*w1count);
                        for(int k=0;k<w1count;++k){
                            (layers+i)->neurons[j].weight[k] = (double)(rand()%2);
                        }
                    }
                    else{
                        (layers+i)->neurons[j].weight = (double *)malloc(sizeof(double)*layercount);
                        for(int k=0;k<layercount;++k){
                            (layers+i)->neurons[j].weight[k] = (double)(rand()%2);
                        }
                    }
                }
                (layers+i)->layertype = 1;
            }
            output = assignOutputWeights(output, layercount);
            break;
        default:
            printf("\nTemplate not defined yet...\n\n\n");
            return 0;
            break;
    }

    /**/
    //Compute the operations between different layers...
    menu(3);
    for(int i=0;i<layercount;++i){
        if((layers+i)->layertype == 1){
            for(int j=0;j<(layers+i)->tamneurons;++j){
                double buffer=0;
                if(i==0)
                    for(int k=0;k<w1count;++k)
                        buffer+=(*(w1+k))*(layers[i].neurons[j].weight[k]);
                else
                    for(int k=0;k<(layers+i-1)->tamneurons;++k)
                        buffer+=(layers[i-1].neurons[k].value)*(layers[i].neurons[j].weight[k]);
                layers[i].neurons[j].value = ReLU(buffer);
            }
        }
    }

    //Compute operations for the output layer
    for(int i=0;i<output.tamneurons;++i){
        double sum=0;
        for(int j=0;j<layers[layercount-1].tamneurons;++j)
            sum += (layers[layercount-1].neurons[j].value)*(output.neurons[i].weight[j]);
        output.neurons[i].value=sigmoid(sum);
    }

    /**/
    //Design the output
    menu(4);
    showNeurons(layercount, layers);
    showOutput(output);

    printf("\n\n\n\nEnd of the program...");
    return 0;
}
