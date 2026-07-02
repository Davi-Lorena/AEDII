//
// Created by Vanessa on 08/04/2025.
//

#ifndef MERGEQUICK_TECHLOJA_H
#define MERGEQUICK_TECHLOJA_H

typedef struct pedido pedido;

//Aloca um vetor de tamanho tam de pedidos
//Retorna o vetor alocado ou NULL
pedido *alocaVet(int tam);

//Insere os pedidos do arquivo no vetor
void carregaPedidos(pedido *vet, int tam, char nomeArquivo[30]);

//Imprime o vetor
//printf("%d\t%0.2f\t%s\n" ...
void imprimePedidos(pedido *vet, int tam);

//ordena um vetor em ordem crescente pelo id do pedido utilizando o método mergesort
//a variável contador conta quantas vezes a função mergeSort foi chamada
void mergeSort(pedido *vet, int inicio, int fim, int *contador);
void merge(pedido *vet, int inicio, int meio, int fim);

//ordena um vetor em ordem decrescente pelo método quicksort
//a variável contador conta quantas vezes a função quickSort foi chamada
void quickSort(pedido *vet, int inicio, int fim, int *contador);
int particiona(pedido *vet, int inicio, int fim);


#endif //MERGEQUICK_TECHLOJA_H
