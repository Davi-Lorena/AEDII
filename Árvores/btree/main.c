#include <stdio.h>
#include "btree.h"

int main() {
    char nomeArquivo[30] = "entrada.txt";
    int ordem = 4;
    btree *b = criaArvore(ordem);
    if(b == NULL)
    {
        printf("A ordem deve ser par\n");
        return 1;
    }

    populaBTree(nomeArquivo, b);
    imprimeArvore((retornaRaiz(b)), 0);
    printf("\n");
    return 0;
}
