#include <stdio.h>
#include <stdlib.h> 

void insertion(int *vet, int tam) {
int j, i, aux;

for(i = 0; i < tam; i++) {
    aux = vet[i];
    j = i - 1;
    
    while(j >= 0 && aux < vet[j]) {
        vet[j + 1] = vet[j];
        j--;
    }
    vet[j + 1] = aux;
}

}