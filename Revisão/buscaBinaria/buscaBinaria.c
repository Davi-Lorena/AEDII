#include <stdio.h>
#include <stdlib.h>
#include "buscaBinaria.h"


int *alocaVetor(int tam) {
    int *vet = (int*) malloc(sizeof(int) * tam);

    return vet;
}

void preencheVetor(int *vet, int tam, FILE *arq) {
    for(int i = 0; i < tam; i++) {
        fscanf(arq, "%d", &vet[i]);
    }
}

void imprimeVetor(int *vet, int tam) {
    for(int i = 0; i < tam; i++) {
        printf("%d\n", vet[i]);
    }
}

int buscaBinaria(int *vet, int inicio, int fim, int valor) {
    int meio = (inicio + fim) / 2;
    int item = vet[meio];
    
    while(item != valor && meio >= inicio && meio <= fim) {
        if(valor > item)   
            meio++; 
        else meio--;

        item = vet[meio];
    } 

   if(item != valor) return -1;

   return meio;
}