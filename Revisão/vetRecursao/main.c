#include <stdio.h>
#include "vetRecursao.h"

int main() {
    FILE *arq;
    char nomeArquivo[30];
    int tam;
    float *vet;

    scanf("%s", nomeArquivo);

    arq = fopen(nomeArquivo, "r");
    if (!arq)
        return 1;

    fscanf(arq, "%d\n", &tam);
    vet = alocaVetor(tam);
    if (!vet)
        return 1;

    preencheVetor(vet, tam, arq);

    inverteVetor(vet, 0, tam-1);

    imprimeVetor(vet, tam);

    return 0;
}
