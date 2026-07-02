#include <stdio.h>
#include <stdlib.h>

void selection(int *vet, int tam) {
    int menor, i, j, aux;

    for(i = 0; i < tam - 1; i ++) {
        menor = i;
        for(j = i + 1; j <tam; j++) {
            if(vet[j] < vet[menor]) 
                menor = j;
        }
        
        aux = vet[menor];
        vet[menor] = vet[i];
        vet[i] = aux;    
    }
}