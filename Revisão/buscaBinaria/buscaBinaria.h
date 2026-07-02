//
// Created by Vanessa on 17/02/2025.
//

#ifndef QUESTAO6_BUSCABINARIA_H
#define QUESTAO6_BUSCABINARIA_H

#include <stdio.h>


int *alocaVetor(int tam);

void preencheVetor(int *vet, int tam, FILE *arq);

void imprimeVetor(int *vet, int tam);

int buscaBinaria(int *vet, int inicio, int fim, int valor);

#endif //QUESTAO6_BUSCABINARIA_H
