#include <stdio.h>
#include "ABP.h"

int main() {
    char nomeArquivo[30] = "entrada.txt";
    ABP *arv = alocaArvore();
    int ok = carregaArvore(nomeArquivo, arv);
    if (ok == 1)
    {
        printf("ARVORE APÓS INSERÇÕES\n");
        percorrePreOrdem(retornaRaiz(arv));
    }

/*
    removeNo(avl, 20);
    removeNo(avl, 15);
    removeNo(avl, 25);
    printf("ARVORE APÓS REMOÇÕES\n");
    percorrePreOrdem(retornaRaiz(avl));*/

    return 0;
}
