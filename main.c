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
*       wsize > MATTAM ? error:success;
*       MATTAM%wsize == 0
*
*/
int main()
{
    int w1count,wchoice, wsize, MATTAM, layercount, *neuronsLayer, decisionchoice;
    /*
    *   w1count     - number of input weights
    *   wchoice     - type of the input weights, choice decided by the user, matrices or doubles
    *   wsize       - size of the window that will iterate over the matrices
    *   MATTAM      - controls the TAM of the matrices
    *   layercount  - number of layers
    *   decisionchoice - controls the answer of the  user for if-statements
    */
    char *str = (char*)malloc(sizeof(char)*strTAM);         //String to control the messages
    double *w1;                                             //Doubles Array
    double **w2;                                            //Matrices Array
    layer *layers;                                          //Array of layers, not counting with the input weights
    layer output = createOutputLayer(2);                    //Our output layer will have 2 neurons

    /**/
    //Select input weights, its type & fill them.
    menu(1);
    printf("Number of input weights(w1count): ");fflush(stdin);scanf("%i", &w1count);
    printf("\n%i input weights, select its type:\n1 - Doubles(w1).\n2 - Matrices(w2).\nType: ", w1count);fflush(stdin);scanf("%i", &wchoice);
    if(wchoice==2) {printf("\nEnter the size of the filter matrix, assuming square matrices(e.g. 2 = 2x2; 3 = 3x3)\nSize: "); scanf("%i", &wsize);}
    if(wchoice!=1&&wchoice!=2){ return 0; } fillWeights(&w1, &w2, w1count, wchoice, &str, &MATTAM); showWeights(str, wchoice, w1count, MATTAM, w1, w2);

    /**/
    //Design the Network(Model)(Layers, Type(FC,Conv,...)
    menu(2);
    switch(printmodelopt()){
        case 1:
            if(wchoice!=1) {printf("\nThis design needs doubles as input weights.\n"); return 0;}

            printf("\n1 - Automatically set the layers and neurons.\n2 - Set the layers and neurons in each.\nSelect one from above: ");scanf("%i", &decisionchoice);
            if(decisionchoice==1){  //Default design, 3 layers, 3 neurons each.
                layercount = 3;
                neuronsLayer = (int *)malloc(sizeof(int)*layercount);

                for(int i=0;i<layercount;++i)
                    *(neuronsLayer+i) = 3;
            }
            else if(decisionchoice==2){ //Custom design.
                printf("\nType the layers the model will have: ");scanf("%i", &layercount);
                neuronsLayer = (int *)malloc(sizeof(int)*layercount);

                for(int i=0,k=0;i<layercount;++i){
                    printf("\nNeurons for layer %i: ", i+1);scanf("%i", &k);
                    *(neuronsLayer+i) = k;
                }
            }
            else{printf("\nNot a valid selection...\n"); return 0;}

            layers = (layer*)malloc(sizeof(layer)*layercount);
            for(int i=0;i<layercount;++i){
                (layers+i)->tamneurons = *(neuronsLayer+i);
                (layers+i)->neurons = (neuron *)malloc(sizeof(neuron)*((layers+i)->tamneurons));  //In each layer we have neurons[tamneurons]
                for(int j=0;j<(layers+i)->tamneurons;++j){
                    if(i==0){
                        (layers+i)->neurons[j].weight = (double *)malloc(sizeof(double)*w1count);
                        for(int k=0;k<w1count;++k){
                            (layers+i)->neurons[j].weight[k] = (double)(rand()%2);
                        }
                    }
                    else{
                        (layers+i)->neurons[j].weight = (double *)malloc(sizeof(double)*(layers[i-1].tamneurons));
                        for(int k=0;k<layers[i-1].tamneurons;++k){
                            (layers+i)->neurons[j].weight[k] = (double)(rand()%2);
                        }
                    }
                }
                (layers+i)->layertype = 1;
            }
            output = assignOutputWeights(output, layers[layercount-1].tamneurons, wchoice, 0);
            break;
        case 2:
            if(wchoice!=2) {printf("\nThis design needs matrices as input weights.\n"); return 0;}

            printf("\n1 - Automatically set the layers and neurons.\n2 - Set the layers and neurons in each.\nSelect one from above: ");scanf("%i", &decisionchoice);
            if(decisionchoice==1){  //Default design, 3 layers, 3 neurons each.
                layercount = 3;
                neuronsLayer = (int *)malloc(sizeof(int)*layercount);

                for(int i=0;i<layercount;++i)
                    *(neuronsLayer+i) = 3;
            }
            else if(decisionchoice==2){ //Custom design.
                printf("\nType the layers the model will have: ");scanf("%i", &layercount);
                neuronsLayer = (int *)malloc(sizeof(int)*layercount);

                for(int i=0,k=0;i<layercount;++i){
                    printf("\nNeurons for layer %i: ", i+1);scanf("%i", &k);
                    *(neuronsLayer+i) = k;
                }
            }
            else{printf("\nNot a valid selection...\n"); return 0;}

            layers = (layer*)malloc(sizeof(layer)*layercount);
            for(int i=0;i<layercount;++i){
                (layers+i)->tamneurons = *(neuronsLayer+i);
                (layers+i)->neurons = (neuron *)malloc(sizeof(neuron)*((layers+i)->tamneurons));  //In each layer we have neurons[tamneurons]
                for(int j=0;j<(layers+i)->tamneurons;++j){
                    int memsize = wsize*wsize;
                    (layers+i)->neurons[j].filter = (double *)malloc(sizeof(double)*memsize);
                    for(int k=0;k<memsize;++k){
                        (layers+i)->neurons[j].filter[k] = (double)((rand()%4)-1);
                    }
                }
                (layers+i)->layertype = 1;
            }

            output = assignOutputWeights(output, layers[layercount-1].tamneurons, wchoice, wsize);
            break;
        default:
            printf("\nTemplate not defined yet...\n\n\n");
            return 0;
            break;
    }

    /**/
    //Compute the operations between different layers...
    menu(3);
    if(wchoice==1){
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
                    layers[i].neurons[j].value = sigmoid(buffer);
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
    }
    else if(wchoice==2){
        int memsize = wsize*wsize;
        for(int i=0;i<layercount;++i){
            if((layers+i)->layertype == 1){
                for(int j=0;j<(layers+i)->tamneurons;++j){
                    if(i==0){
                        for(int k=0;k<w1count;++k){
                            double *tempmatrix = (double*)malloc(sizeof(double)*memsize);
                            int iterations = (MATTAM*MATTAM) / (wsize*wsize);
                            int counter=0;
                            int posx=0,posy=0;
                            for(int l=0;l<iterations;++l){ //4 hilos

                                for(int n=0;n<wsize;++n){
                                    for(int o=0;o<wsize;++o){
                                        tempmatrix[(wsize*n)+o] = w2[k][((posy + n) * MATTAM) + posx + o];
                                    }
                                }

                                counter++;
                                posx+=wsize;
                                if(counter%wsize==0) {posy+=wsize;posx=0;counter=0;}

                                //Operaciones de multiplicacion
                                printf("\nDentro del peso %i, en la submatriz %i la multiplico por el filtro de la neurona %i", k, l, j);
                            }
                        }
                    }
                    else{
                        //Resto de neuronas...
                    }
                }
            }
        }

        //Compute operations for the output layer
    }

    /**/
    //Design the output
    menu(4);
    showNeurons(layercount, layers);
    showOutput(output);

    printf("\n\n\n\nEnd of the program...");
    return 0;
}
