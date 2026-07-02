#include <stdio.h>
#include <stdlib.h>

int *bubble(int *vet, int tam) {
    int i, j, aux;

    for(i = 0; i < tam; i++) {
        for(int j = 1; j < tam; j++) {
            if(vet[j - 1] > vet[j]) {
                aux = vet[j-1];
                vet[j-1] = vet[j];
                vet[j] = aux;
            }
        }
    }

    return vet;
}

int *bubbleInteligente(int *vet, int tam) {
    int j, i, aux, boolean;

    for(i = 0; i < tam; i++) {
        boolean = 0;
        for(j = 1; j < tam - i; j++) {
            if(vet[j-1] > vet[j]){
                aux = vet[j-1];
                vet[j-1] = vet[j];
                vet[j] = aux;
                boolean = 1;
            }
        }
        if(!boolean) return;
    }
    return vet;
}

int *selection(int *vet, int tam) {
    int menor, i, j, aux;
    
    for(i = 0; i < tam - 1; i ++) {
        menor = i; 
        for(j = i + 1; j < tam; j++) {
            if(vet[j] < vet[menor])
                menor = j;
        }

        aux = vet[menor];
        vet[menor] = vet[i];
        vet[i] = aux;

    }
    
    return vet;
}

int *insertion(int *vet, int tam) {
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

    return vet;
}

int *mergeSort(int *vet, int inicio, int fim) {
if(inicio >= fim) return;

int meio = (inicio + fim) / 2;

mergeSort(vet, inicio, meio);
mergeSort(vet, meio+1, fim);
merge(vet, inicio, meio, fim);

}

void merge(int *vet, int inicio, int meio, int fim) {
    int i, j, k, 
    *temp,
    tam = fim - inicio + 1,
    inicioVetor1 = inicio,
    inicioVetor2 = meio + 1,
    fim1 = 0, fim2 = 0;

    temp = malloc(sizeof(int) * fim);
    if(!temp) return;

    for(i = 0; i < tam; i++) {
        if(!fim1 && !fim2) {
            if(vet[inicioVetor1] < vet[inicioVetor2]) {
                temp[i] = vet[inicioVetor1];
                inicioVetor1++;
            } else {
                temp[i] = vet[inicioVetor2];
                inicioVetor2++;
            }

            if(inicioVetor1 > meio) fim1 = 1;
            if(inicioVetor2 > fim) fim2 = 1;
        } else {
            if(!fim1){
                temp[i] = vet[inicioVetor1++];
            } else temp[i] = vet[inicioVetor2++];
        }
    }

    for(j = 0, k = inicio; j < tam; j++, k++) {
        vet[k] = temp[j];
    }

    free(temp);

}

void quickSort(int *vet, int inicio, int fim) {
    if(inicio > fim) return; 
    int pivo = particiona(vet, inicio, fim);
    quickSort(vet, inicio, pivo -1);
    quickSort(vet, pivo+1, fim);

}

int particiona(int *vet, int inicio, int fim) {
    int pivo = vet[inicio],
    pos = inicio,
    aux,
    i;

    for(i = inicio + 1; i <= fim; i++) {
        if(vet[i] < pivo) {
            pos++;

            if(i != pos) {
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

int hash(int valor, int tam) {
    return valor % tam;
}

void hashABerto(int *l, int valor, int tam) {
int chave = hash(valor, tam);

while(l[chave] != 0) { 
 chave = hash(chave + 1, tam);
}

insereLista(l, chave);

}