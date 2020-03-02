#include "visual.h"

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

void showOutput(layer outputLayer){
    for(int i=0;i<outputLayer.tamneurons;++i){
        printf("\nOutput neuron %i: %f", i, outputLayer.neurons[i].value);
    }
}
