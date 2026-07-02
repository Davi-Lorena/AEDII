#include <stdio.h>
#include "TAD_ABP.h"

int main() {
    FILE *arq;
    char nomeArquivo[30];
    abp *arvore;
    noABP *novoNo, *aux, *pred;
    int valor;

    scanf("%s", nomeArquivo);

    arq = fopen(nomeArquivo, "r");
    if (!arq)
    {
        printf("Erro ao carregar arquivo");
        return 1;
    }

    arvore = criaArvore();
    if (!arvore)
    {
        printf("Erro ao alocar a árvore");
        return 1;
    }

    //Criando a árvore binária de pesquisa
    while(fscanf(arq, "%d\n", &valor) == 1)
    {
        novoNo = criaNo(valor);
        if (!novoNo)
        {
            printf("Erro ao alocar novo nó");
            return 1;
        }
        insere(arvore, novoNo);
    }

    //Imprimir em ordem utilizando a travessia de Morris
    travessiaMorris(arvore);
    printf("\n");

    //Gerar a árvore de soma maior
    somaMaior(arvore);

    //Imprimir em ordem utilizando a travessia de Morris
    travessiaMorris(arvore);

    return 0;
}
