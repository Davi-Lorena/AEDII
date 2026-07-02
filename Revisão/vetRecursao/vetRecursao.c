
#include <stdio.h>
#include <stdlib.h>
#include "vetRecursao.h"

float *alocaVetor(int tam) {
    float *vet = (float *) malloc(tam * sizeof(float));
    return vet;
}

void preencheVetor(float *vet, int tam, FILE *arq) {
    for(int i = 0; i < tam; i++) 
        fscanf(arq, "%f", &vet[i]);
}

void imprimeVetor(float *vet, int tam) {
    for(int i = 0; i < tam; i++)
        printf("%f\n", vet[i]);
}

//  15
//  5
//  6
//  16

void inverteVetor(float *vet, int ini, int fim) {
    
    if(fim <= ini)
    return;
    
    float aux = vet[ini];
    vet[ini] = vet[fim];
    vet[fim] = aux; 
    

    inverteVetor(vet, ini+1, fim-1);

}
