#include <stdio.h>
#include "TechLoja.h"

int main() {
    pedido *vet;
    char nomeArquivo[30];
    int tam;
    int contador = 0;

    scanf("%s", nomeArquivo);
    scanf("%d", &tam);

    vet = alocaVet(tam);
    if(!vet)
    {
        printf("Erro ao alocar o vetor");
        return 1;
    }

    //MERGESORT//
    carregaPedidos(vet, tam, nomeArquivo);
    mergeSort(vet, 0, tam-1, &contador);
    printf("\nPedidos Ordenados por Id (Crescente) - Total de Chamadas mergeSort: %d\n", contador);
    imprimePedidos(vet, tam);

    //QUICKSORT//
    contador = 0;
    carregaPedidos(vet, tam, nomeArquivo);
    quickSort(vet, 0, tam-1, &contador);
    printf("\nPedidos Ordenados por Valor (Decrescente) - Total de Chamadas quickSort: %d\n", contador);
    imprimePedidos(vet, tam);

    return 0;
}
