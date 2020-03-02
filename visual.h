#ifndef _VISUAL_H_
#define _VISUAL_H_

#include "struct.h"
#include "header.h"

void menu(int opt);
int printmodelopt();
void showWeights(char *str, int wchoice, int w1count, int MTAM, double *w1, double **w2);
void showNeurons(int layercount, layer *layers);
void showOutput(layer outputLayer);

#endif // _VISUAL_H_
