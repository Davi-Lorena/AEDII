#include <stdio.h>
#include "btreeIndex.h"

int main() {
    char nomeArquivo[30];
    int ordem, mat, qtd;

    scanf("%s", nomeArquivo);
    scanf("%d", &ordem);

    btree *indice = create_index(nomeArquivo, ordem);
    if (!indice)
        return -1;

    imprimeArvore(retornaRaiz(indice), 0);

    scanf("%d", &qtd);
    for(int i=0; i< qtd; i++)
    {
        scanf("%d", &mat);
        buscar_Aluno(indice, nomeArquivo, mat);
    }

    printf("\n");
    buscaMatricula(nomeArquivo, mat);

    return 0;
}
