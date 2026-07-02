#include <stdio.h>
#include <stdlib.h>

//Imprime um vetor na tela
//Recebe um vetor de inteiros e o tamanho do vetor
//printf("%d ", vet[i])
void imprimeVetor(int *vet, int tam) {
    for(int i = 0; i < tam; i++) {
        printf("%d ", vet[i]);
    }
}


//Cria um vetor com dados aleatórios entre os valores min e max
//Recebe o tamanho do vetor, valor mínimo e valor máximo e a semente
//Retorna um vetor de inteiros
int *geraVetorAleatorio(int tam, int min, int max, int semente) {
    int *vet = malloc(sizeof(int) * tam);
    int i;
    if(!vet) return NULL;

    srand(semente);

    for(i = 0; i < tam; i++) {
        vet[i] = rand() % (max - min + 1) + min;
    }

    return vet;
}