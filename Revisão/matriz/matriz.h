//
// Created by Vanessa on 10/02/2025.
//

#include "stdio.h"

#ifndef QUESTAO1_MATRIZ_H
#define QUESTAO1_MATRIZ_H

//Função que aloca dinamicamente uma matriz com n linhas e n colunas
//Retorna a matriz alocada
int** alocaMatriz(int linhas, int colunas);

//Função que preenche uma matriz de inteiros a partir dos dados de um arquivo
//Retorna 1 caso a matriz inteira tenha sido preenchida
//Retorna 0 caso contrário
int preencheMatriz(int **mat, int linhas, int colunas, FILE *arq);

//Função que percorre a matriz e computa a quantidade de elementos entre 15 e 20
//Retorna o total de elementos
int verificaElementos(int **mat, int linhas, int colunas);

//Função que desaloca a matriz
void desalocaMatriz(int **mat, int linhas);

#endif //QUESTAO1_MATRIZ_H
