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
*/
int main()
{
    int w1count,wchoice, wsize=0, MATTAM=0, layercount, *neuronsLayer, decisionchoice, poolchoice, modelchoice;
    /*
    *   w1count     - number of input weights
    *   wchoice     - type of the input weights, choice decided by the user, matrices or doubles
    *   wsize       - size of the window that will iterate over the matrices
    *   MATTAM      - controls the TAM of the matrices
    *   layercount  - number of layers
    *   decisionchoice - controls the answer of the  user for if-statements
    *   poolchoice  - determines the pooling method
    *   modelchoice - selects the model
    */
    char *str = (char*)malloc(sizeof(char)*strTAM);         //String to control the messages
    double *w1;                                             //Doubles Array
    double **w2;                                            //Matrices Array
    layer *layers;                                          //Array of layers, not counting with the input weights
    layer output = createOutputLayer(2);                    //Our output layer will have 2 neurons

    /**/
    //Select input weights, its type & fill them.
    menu(1);
    modelchoice = printmodelopt();

    menu(2);
    printf("Number of input weights(w1count): ");fflush(stdin);scanf("%i", &w1count);
    printf("\n%i input weights, select its type:\n1 - Doubles(w1).\n2 - Matrices(w2).\nType: ", w1count);fflush(stdin);scanf("%i", &wchoice);
    if(wchoice==2) {printf("\nEnter the size of the filter matrix, assuming square matrices(e.g. 2 = 2x2; 3 = 3x3)\nSize: "); scanf("%i", &wsize);printf("\nSelect the pooling method:\n1 - Max Pooling.\n2 - Average Pooling.\nChoice: "); scanf("%i", &poolchoice);}
    if(wchoice!=1&&wchoice!=2)return 0;

    srand(time(NULL));
    if(wchoice==2){ //Matrix
        int tempsize;
        str = "in the matrices ?";
        printf("\nType in the size of the Matrices, assuming square matrices(e.g. 5 = 5x5; 7 = 7x7): ");fflush(stdin);scanf("%i", &MATTAM);
        tempsize = (MATTAM)*(MATTAM);

        w2 = (double**) malloc(sizeof(double*)*w1count);
        for(int i=0;i<w1count;++i){
            w2[i] = (double*)malloc(sizeof(double)*tempsize);
            for(int j=0;j<tempsize;++j){
                w2[i][j] = (double)((rand()%30)-10);
            }
        }
    }
    else{ //Doubles
        str = "in the doubles ?";
        w1 = (double*) malloc(sizeof(double)*w1count);
        for(int i=0; i<w1count; ++i)
            w1[i] = (double)((rand()%30)-10);
    }
    showWeights(str, wchoice, w1count, MATTAM, w1, w2);

    int matrixTAM = MATTAM; //Size of the matrix

    int memsize = wsize*wsize; //Filter matrix

    int cvsize = convolvSize(MATTAM,wsize); //Convolution step
    int cvmemsize = cvsize*cvsize;

    int poolsize = convolvSize(cvsize, wsize); //Pooling step
    int poolmemsize = poolsize*poolsize;
    /**/
    //Design the Network(Model)(Layers, Type(FC,Conv,...)
    switch(modelchoice){
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
            output = assignOutputWeights(output, layers[layercount-1].tamneurons);
            break;
        case 2:
            if(wchoice!=2) {printf("\nThis design needs matrices as input weights.\n"); return 0;}

            printf("\n1 - Automatically set the layers and neurons, 3 layers with 3 neurons each.\n2 - Set the layers and neurons in each.\nNo matter what, the last layer will be a Flatten Layer.\nSelect one from above: ");scanf("%i", &decisionchoice);
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
                (layers+i)->neurons = (neuron *)malloc(sizeof(neuron)*((layers+i)->tamneurons));
                for(int j=0;j<(layers+i)->tamneurons;++j){
                    (layers+i)->neurons[j].filter = (double *)malloc(sizeof(double)*memsize);
                    for(int k=0;k<memsize;++k){
                        (layers+i)->neurons[j].filter[k] = randomNumberFilter(); //Values between -1, 0 & 1
                    }
                }
                if(decisionchoice==2){
                    int k;
                    printf("\nLayer %i, select type:\n1. Convolution.\n2. Flatten Layer.\nSelect: ", i);scanf("%i", &k);
                    if(k==1)
                        (layers+i)->layertype = 2;
                    else if(k==2)
                        (layers+i)->layertype = 1;
                }
                else{
                    if(i==layercount-1)
                        (layers+i)->layertype = 1; //Last layer will be a flatten layer
                    else
                        (layers+i)->layertype = 2; //All the other layers will be convolution
                }
            }
            output = assignOutputWeights(output, layers[layercount-1].tamneurons);
            break;
        default:
            printf("\nTemplate not defined yet...\n\n\n");
            return 0;
            break;
    }

    /**/
    //Compute the operations between different layers...
    menu(3);
    if(modelchoice==1){
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
    else if(modelchoice==2){
        int firstflattenlayer = 1;
        int firstflattenlayersecond = 1;
        for(int i=0;i<layercount;++i){
            if(layers[i].layertype == 1 && firstflattenlayer == 1){
                int weights = layers[i-1].tamneurons*matrixTAM*matrixTAM;
                for(int j=0;j<(layers+i)->tamneurons;++j){
                    (layers+i)->neurons[j].weight = (double *)malloc(sizeof(double)*weights);
                    for(int k=0;k<weights;++k){
                        (layers+i)->neurons[j].weight[k] = (double)(rand()%2);
                    }
                }
            }
            else if((layers+i)->layertype == 1 && firstflattenlayer != 1){
                int weights = layers[i-1].tamneurons;
                for(int j=0;j<(layers+i)->tamneurons;++j){
                    (layers+i)->neurons[j].weight = (double *)malloc(sizeof(double)*weights);
                    for(int k=0;k<weights;++k){
                        (layers+i)->neurons[j].weight[k] = (double)(rand()%2);
                    }
                }
            }
            for(int j=0;j<(layers+i)->tamneurons;++j){
                printf("\nLayer %i, neuron %i.\n", i, j);
                if((layers+i)->layertype == 2){
                    double *tempmatrix = (double*)malloc(sizeof(double)*memsize);
                    if(i==0){
                        double *convmatrix = (double*)malloc(sizeof(double)*cvmemsize);
                        int posx=0,posy=0,counter=0;
                        double buffer;
                        for(int l=0;l<cvmemsize;++l){
                            buffer = 0.0f;
                            for(int k=0;k<w1count;++k){
                                for(int n=0;n<wsize;++n){
                                    for(int o=0;o<wsize;++o){
                                        tempmatrix[(wsize*n)+o] = w2[k][((posy + n) * MATTAM) + posx + o];
                                    }
                                }
                                buffer += addMatrices(tempmatrix, layers[i].neurons[j].filter, wsize);
                            }
                            counter++;
                            posx++;
                            if(counter+wsize>MATTAM) {posy++;posx=0;counter=0;}
                            *(convmatrix+l) = buffer;
                        }
                        //Pooling Layer
                        counter=posx=posy=0;
                        double tempv;
                        layers[i].neurons[j].mvalue = (double*)malloc(sizeof(double)*poolmemsize);
                        for(int l=0;l<poolmemsize;++l){
                            tempv = 0.0f;
                            for(int n=0;n<wsize;++n){
                                for(int o=0;o<wsize;++o){
                                    tempmatrix[(wsize*n)+o] = convmatrix[((posy + n) * cvsize) + posx + o];
                                }
                            }
                            counter++;
                            posx++;
                            if(counter+wsize>cvsize) {posy++;posx=0;counter=0;}

                            if(poolchoice==1) tempv = getAverage(tempmatrix, wsize);
                            else if(poolchoice==2) tempv = getMajor(tempmatrix, wsize);
                            layers[i].neurons[j].mvalue[l] = tempv;
                        }
                        free(convmatrix);
                    }
                    else{
                        double *convmatrix = (double*)malloc(sizeof(double)*cvmemsize);
                        int posx=0,posy=0,counter=0;
                        double buffer;
                        for(int l=0;l<cvmemsize;++l){
                            buffer = 0.0f;
                            for(int k=0;k<(layers[i-1].tamneurons);++k){
                                for(int n=0;n<wsize;++n){
                                    for(int o=0;o<wsize;++o){
                                        tempmatrix[(wsize*n)+o] = layers[i-1].neurons[k].mvalue[((posy + n) * matrixTAM) + posx + o];
                                    }
                                }
                                buffer += addMatrices(tempmatrix, layers[i].neurons[j].filter, wsize);
                            }
                            counter++;
                            posx++;
                            if(counter+wsize>MATTAM) {posy++;posx=0;counter=0;}
                            *(convmatrix+l) = buffer;
                        }
                        //Pooling Layer
                        counter=posx=posy=0;
                        double tempv;
                        layers[i].neurons[j].mvalue = (double*)malloc(sizeof(double)*poolmemsize);
                        for(int l=0;l<poolmemsize;++l){
                            tempv = 0.0f;
                            for(int n=0;n<wsize;++n){
                                for(int o=0;o<wsize;++o){
                                    tempmatrix[(wsize*n)+o] = convmatrix[((posy + n) * cvsize) + posx + o];
                                }
                            }
                            counter++;
                            posx++;
                            if(counter+wsize>cvsize) {posy++;posx=0;counter=0;}

                            if(poolchoice==1) tempv = getAverage(tempmatrix, wsize);
                            else if(poolchoice==2) tempv = getMajor(tempmatrix, wsize);
                            layers[i].neurons[j].mvalue[l] = tempv;
                        }
                        free(convmatrix);
                    }

                    PrintArray(layers[i].neurons[j].filter, wsize);
                    PrintArray(layers[i].neurons[j].mvalue, poolsize);
                    system("pause");
                    free(tempmatrix);
                }
                else if((layers+i)->layertype == 1){
                    double buffer = 0.0f;

                    if(firstflattenlayersecond==1){ //First flatten layer.
                        firstflattenlayer = 0;
                        int localmem = matrixTAM*matrixTAM;
                        int weights = layers[i-1].tamneurons*localmem;
                        double *valuearray = (double*)malloc(sizeof(double)*weights);
                        for(int k=0;k<layers[i-1].tamneurons;++k)
                            for(int l=0;l<localmem;++l)
                                valuearray[(k*localmem)+l] = layers[i-1].neurons[k].mvalue[l];

                        for(int k=0;k<weights;++k)
                            buffer+=(*(valuearray+k))*(layers[i].neurons[j].weight[k]);
                    }
                    else{
                        for(int k=0;k<layers[i-1].tamneurons;++k)
                            buffer+=(layers[i-1].neurons[k].value)*(layers[i].neurons[j].weight[k]);
                    }
                    layers[i].neurons[j].value = ReLU(buffer);
                    printf("Flatten Layer\n");
                }
            }
            if(firstflattenlayer==0)
                firstflattenlayersecond = 0;
            cvsize = convolvSize(poolsize,wsize);
            cvmemsize = cvsize*cvsize;
            matrixTAM = poolsize;
            poolsize = convolvSize(cvsize, wsize);
            poolmemsize = poolsize*poolsize;
        }
        for(int i=0;i<output.tamneurons;++i){
            double sum=0;
            for(int j=0;j<layers[layercount-1].tamneurons;++j)
                sum += (layers[layercount-1].neurons[j].value)*(output.neurons[i].weight[j]);
            output.neurons[i].value=sigmoid(sum);
        }
    }

    /**/
    //Design the output
    menu(4);
    showNeurons(layercount, layers);
    showOutput(output);

    printf("\n\n\n\nEnd of the program...");
    return 0;
}
