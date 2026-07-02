#include <stdio.h>
#include <stdlib.h>

void quickSort(int *vet, int inicio, int fim) {
    if(inicio < fim) {
        int pivo = particiona(vet, inicio, fim);
        quickSort(vet, inicio, pivo-1);
        quickSort(vet, pivo+1, fim);
    }
}

int particiona(int *vet, int inicio, int fim) {
    int i, aux,
    pivo = vet[inicio], // Escolhe o primeiro como referência
    pos = inicio; // 'pos' rastreia onde o pivô deveria estar

    for(i = inicio + 1; i <= fim; i++) {
        if(vet[i] < pivo) {
            pos++; // Há alguém menor que o pivô, altera sua posição no vetor 
            if(i != pos){ // Troca o elemento atual (i) pelo que está na ponta dos menores elementos, marcando o fim dessa metade esquerda do vetor
                aux = vet[i];
                vet[i] = vet[pos];
                vet[pos] = aux; 
            }
        }
    }

    // Aqui a posição do Pivô já foi encontrada e ele é colocado no seu lugar 
    aux = vet[inicio];
    vet[inicio] = vet[pos];
    vet[pos] = aux;

    return pos; // retorna a posição do pivô para prosseguir com o algoritmo 
}