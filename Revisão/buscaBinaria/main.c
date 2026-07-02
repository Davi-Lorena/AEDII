#include <stdio.h>
#include "buscaBinaria.h"

int main() {
    FILE *arq;
    char nomeArquivo[30];
    int tam, valor, pos;
    int *vet;

    scanf("%s", nomeArquivo);
    scanf("%d", &valor);

    arq = fopen(nomeArquivo, "r");
    if (!arq)
        return 1;

    fscanf(arq, "%d\n", &tam);
    vet = alocaVetor(tam);
    if (!vet)
        return 1;


    preencheVetor(vet, tam, arq);

    imprimeVetor(vet, tam);

    pos = buscaBinaria(vet, 0, tam-1, valor);
    if (pos == -1)
        printf("Elemento nao encontrado no vetor\n");
    else
        printf("Elemento encontrado na posicao %d do vetor\n", pos);

    return 0;
}
