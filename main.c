#include "header.h"
#include "struct.h"
#include "visual.h"
#include "mathlib.h"

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
