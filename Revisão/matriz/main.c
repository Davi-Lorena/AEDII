#include <stdio.h>
#include "matriz.h"

int main() {
    int **mat;
    int linhas, colunas, aux;
    int totalElementos;//entre 15 e 20
    FILE *arq;
    char nomeArquivo[30];

    scanf("%s", nomeArquivo);

    arq = fopen(nomeArquivo, "r");
    if (!arq)
    {
        printf("Erro ao abrir o arquivo.");
        return 0;
    }

    fscanf(arq, "%d", &linhas);
    fscanf(arq, "%d", &colunas);

    mat = alocaMatriz(linhas, colunas);
    if (!mat)
    {
        printf("Erro ao alocar matriz.");
        return 0;
    }

    aux = preencheMatriz(mat, linhas, colunas, arq);
    fclose(arq);
    if (aux == 0)
    {
        printf("Erro ao preencher a matriz.");
        return 0;
    }

    totalElementos = verificaElementos(mat, linhas, colunas);

    printf("O total de elementos entre 15 e 20 e: %d", totalElementos);

    desalocaMatriz(mat, linhas);

    return 1;
}
