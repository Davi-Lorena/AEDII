//
// Created by Vanessa on 10/02/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

//Função que aloca dinamicamente uma matriz com n linhas e n colunas
//Retorna a matriz alocada
int** alocaMatriz(int linhas, int colunas) {
    int **mat = (int**) malloc(sizeof(int*) * linhas);

    for(int i = 0; i < linhas; i++) 
        mat[i] = (int*) malloc(sizeof(int*) * colunas);
    
    return mat;
}

//Função que preenche uma matriz de inteiros a partir dos dados de um arquivo
//Retorna 1 caso a matriz inteira tenha sido preenchida
//Retorna 0 caso contrário
int preencheMatriz(int **mat, int linhas, int colunas, FILE *arq) {
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            fscanf(arq, "%d", &mat[i][j]);
        }
    }
    
    if(mat[linhas-1][colunas-1]) {
            return 1;
        }
        return 0;
}

//Função que percorre a matriz e computa a quantidade de elementos entre 15 e 20
//Retorna o total de elementos
int verificaElementos(int **mat, int linhas, int colunas) {
    int total = 0;
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            if(mat[i][j] >= 15 && mat[i][j] <= 20) total++;
        }
    }
return total;
}

//Função que desaloca a matriz
void desalocaMatriz(int **mat, int linhas){
    for(int i = 0; i < linhas; i++) {
        free(mat[i]);
    }

    free(mat);
}
