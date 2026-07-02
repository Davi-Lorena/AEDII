//
// Created by Vanessa on 13/03/2024.
//

#ifndef AULA3_TAD_ES_H
#define AULA3_TAD_ES_H

//Imprime um vetor na tela
//Recebe um vetor de inteiros e o tamanho do vetor
//printf("%d ", vet[i])
void imprimeVetor(int *vet, int tam);


//Cria um vetor com dados aleatórios entre os valores min e max
//Recebe o tamanho do vetor, valor mínimo e valor máximo e a semente
//Retorna um vetor de inteiros
int *geraVetorAleatorio(int tam, int min, int max, int semente);

#endif //AULA3_TAD_ES_H
