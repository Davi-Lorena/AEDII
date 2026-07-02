#include <stdio.h>
#include <stdlib.h>

int bubble(int *vet, int tam) {
    int i, j, aux;

    for(i = 0; i < tam; i++) {
        for (j = 1; j < tam; j++) {
            if(vet[j-1] > vet[j]) {
                aux = vet[j-1];
                vet[j-1] = vet[j];
                vet[j] = aux;
            }
        }
    }
}

void bubbleInteligente(int *vet, int tam) {
    int i, j, aux, boolean;

    for(i = 0; i < tam; i++) {
        boolean = 0;
        for(j = 1; j < tam - i; j++) {
            if(vet[j-1] > vet[j]) {
                aux = vet[j-1];
                vet[j-1] = vet[j];
                vet[j] = aux;
                boolean = 1;
            }
        }
        if(!boolean) return;
    }
}

void selection(int *vet, int tam) {
    int i, j, aux, menor;

    for(i = 0; i < tam - 1; i++) {
        menor = i;
        for(j = i + 1; j < tam; j++) {
            if(vet[j] < vet[menor])
                menor = j;
        }

        aux = vet[menor];
        vet[menor] = vet[i];
        vet[i] = aux;
    }
}

void insertion(int *vet, int tam) {
    int i, j, aux;

    for(i = 0; i < tam; i++) {
        aux = vet[i];
        j = i -1;

        while(j >= 0 && aux < vet[j]) {
            vet[j + 1] = vet[j]; 
            j--;
        }

        vet[j+1] = aux;

    }
}


void mergeSort(int *vet, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;

        mergeSort(vet, inicio, meio);
        mergeSort(vet, meio+1, fim);
        merge(vet, inicio, meio, fim);
    }
}

void merge(int *vet, int inicio, int meio, int fim) {
    int i, j, k, *temp, 
    tam = fim - inicio + 1,
    inicioVetor1 = inicio,
    inicioVetor2 = meio + 1,
    fim1 = 0, fim2 = 0;

    for(i = 0; i < fim; i++) {
        if(!fim1 && !fim2) {
            if(vet[inicioVetor1] < vet[inicioVetor2])
                temp[i] = vet[inicioVetor1++];
            else temp[i] = vet[inicioVetor2++];

            if(inicioVetor1 > meio) fim1 = 1;
            if(inicioVetor2 > fim) fim2 = 1;
        } else {
            if(!fim1) 
                temp[i] = vet[inicioVetor1++];
            else temp[i] = vet[inicioVetor2++];
        }
    }

    for(j = 0, k = inicio; j < tam; j++, k++) {
        vet[k] = temp[j];
    }
}


void quickSort(int *vet, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particiona(vet, inicio, fim);
        quickSort(vet, inicio, pivo-1);
        quickSort(vet, inicio, pivo+1);
    }
}

int particiona(int *vet, int inicio, int fim) {
    int pivo = vet[inicio],
    pos = inicio, i, aux;

    for(i = inicio + 1; i <= fim; i++) {
        if(vet[i] < pivo) {
            pos++;
            if(pos != i) {
                aux = vet[i];
                vet[i] = vet[pos];
                vet[pos] = aux; 
            }
        } 

    }

    aux = vet[inicio];
    vet[inicio] = vet[pos];
    vet[pos] = aux;

    return pos;
}