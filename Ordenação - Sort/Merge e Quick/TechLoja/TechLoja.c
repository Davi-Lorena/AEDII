#include <stdio.h>
#include <stdlib.h>
#include "TechLoja.h"

typedef struct pedido {
int id_pedido;
float valor;
char nome[50];
} pedido;

//Aloca um vetor de tamanho tam de pedidos
//Retorna o vetor alocado ou NULL
pedido *alocaVet(int tam) {
pedido *vet = malloc(sizeof(pedido) * tam);

if(!vet) return NULL;

return vet;
}

//Insere os pedidos do arquivo no vetor
void carregaPedidos(pedido *vet, int tam, char nomeArquivo[30]) {
    FILE *arq = fopen(nomeArquivo, "r");
    int i = 0;

    if(!arq) return;

    while(!feof(arq) && i < tam) {
        fscanf(arq, "%d;%f;%[^\n]", &vet[i].id_pedido, &vet[i].valor, vet[i].nome);
        i++;
    }
    
    fclose(arq);

}

//Imprime o vetor
//printf("%d\t%0.2f\t%s\n" ...
void imprimePedidos(pedido *vet, int tam) {
    for(int i = 0; i < tam; i++)
        printf("%d\t%0.2f\t%s\n", vet[i].id_pedido, vet[i].valor, vet[i].nome);
}

//ordena um vetor em ordem crescente pelo id do pedido utilizando o método mergesort
//a variável contador conta quantas vezes a função mergeSort foi chamada
void mergeSort(pedido *vet, int inicio, int fim, int *contador) {
    
    (*contador)++;
    if( inicio < fim) {
    int meio = (inicio + fim ) / 2;
    mergeSort(vet, inicio, meio, contador);
    mergeSort(vet, meio+1, fim, contador);
    merge(vet, inicio, meio, fim);
    }
}

void merge(pedido *vet, int inicio, int meio, int fim) {
    int i, j, k,
    tam = fim - inicio + 1,
    vet1 = inicio,
    vet2 = meio + 1,
    fim1 = 0,
    fim2 = 0;
    pedido *temp;

    temp = malloc(sizeof(pedido) * tam);

    if(!temp) return; 

    for(i = 0; i < tam; i++){
        if(!fim1 && !fim2) {
            if(vet[vet1].id_pedido < vet[vet2].id_pedido) 
                temp[i] = vet[vet1++];
            else temp[i] = vet[vet2++];

             if(vet1 > meio) fim1 = 1;
            if(vet2 > fim) fim2 = 1;
        } else {
            
            if(!fim1) 
                temp[i] = vet[vet1++];
            else
                temp[i] = vet[vet2++];
        }
    }

    for(j = 0, k = inicio; j < tam; j++, k++) 
        vet[k] = temp[j];

    free(temp);
}

//ordena um vetor em ordem decrescente pelo método quicksort
//a variável contador conta quantas vezes a função quickSort foi chamada
void quickSort(pedido *vet, int inicio, int fim, int *contador) {
    (*contador)++;
    if(inicio < fim) {
        int pivo = particiona(vet, inicio, fim);
        quickSort(vet, inicio, pivo-1, contador);
        quickSort(vet, pivo + 1, fim, contador);
        }

}

int particiona(pedido *vet, int inicio, int fim) {
    int i, pos = inicio; 
    pedido aux, pivo = vet[inicio];

    for(i = inicio + 1; i <= fim; i++) {
        if(vet[i].valor > pivo.valor) {
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
    vet[pos] = pivo;
    return pos;
}