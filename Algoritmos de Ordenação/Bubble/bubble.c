#include <stdio.h> 
#include <stdlib.h> 

int *bubble(int *vet, int tam) {
int i, j, aux;

for(i = 0; i < tam; i++) 
    for(j = 1; j < tam; j++) 
        if(vet[j] < vet[j - 1]){ 
            aux = vet[j];
            vet[j] = vet[j - 1];
            vet[j - 1] = aux;
         }

    return vet;
}