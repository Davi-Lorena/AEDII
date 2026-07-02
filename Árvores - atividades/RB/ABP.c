//
// Created by Vanessa on 26/05/2026.
//

#include "ABP.h"
#include <stdio.h>
#include <stdlib.h>

struct no
{
    int chave;
    no *fEsq;
    no *fDir;
    no *pai;
};

struct arv
{
    no *sentinela;
    int totalElementos;
};

ABP *alocaArvore()
{
    ABP *novaArvore = (ABP*) malloc(sizeof(ABP));
    if (!novaArvore)
        return NULL;

    no *sentinela = alocaNo(-1000);
    if (!sentinela)
        return NULL;

    novaArvore->sentinela = sentinela;
    novaArvore->totalElementos = 0;

    return novaArvore;

}

no *alocaNo(int codigo)
{
    no *novoNo = (no*) malloc(sizeof (no));
    if (!novoNo)
        return NULL;
    novoNo->chave = codigo;
    novoNo->fEsq = NULL;
    novoNo->fDir = NULL;
    novoNo->pai = NULL;

    return novoNo;
}

int carregaArvore(char nomeArquivo[30], ABP *arv)
{
    FILE *arq = fopen(nomeArquivo, "r");
    if (!arq)
    {
        printf("Erro ao abrir o arquivo");
        return 0;
    }

    int codigo;
    no *novoNo;

    while(!feof(arq))
    {
        fscanf(arq, "%d", &codigo);
        novoNo = alocaNo(codigo);
        if (!novoNo)
            return 0;
        insereNo(arv, novoNo);
    }

    return 1;
}

void insereNo(ABP *arv, no *novoNo)
{
    if (arv->sentinela->fDir == NULL)
    {
        arv->sentinela->fDir = novoNo;
        novoNo->pai = arv->sentinela;
        arv->totalElementos++;
        return;
    }

    no *aux = arv->sentinela->fDir;
    no *pai = arv->sentinela->fDir;
    while (aux != NULL)
    {
        pai = aux;
        if (novoNo->chave < aux->chave)
            aux = aux->fEsq;
        else
            aux = aux->fDir;
    }
    if (novoNo->chave < pai->chave)
        pai->fEsq = novoNo;
    else
        pai->fDir = novoNo;

    novoNo->pai = pai;
}

void removeNo(ABP *arv, int chaveRemovida)
{
    no *pai;

    if (arv->sentinela->fDir == NULL)
        return;

    no *aux = arv->sentinela->fDir;
    while(aux != NULL && aux->chave != chaveRemovida)
    {
        if (chaveRemovida < aux->chave)
            aux = aux->fEsq;
        else
            aux = aux->fDir;
    }

    if (aux == NULL)
        return;

    if (aux->fEsq != NULL && aux->fDir != NULL) //nó tem dois filhos
    {
        no *predecessor = aux->fEsq;
        while(predecessor->fDir)
            predecessor = predecessor->fDir;
        //FAZ A CÓPIA
        aux->chave = predecessor->chave;
        aux = predecessor;
        chaveRemovida = predecessor->chave;
    }
    if (aux->fEsq == NULL && aux->fDir == NULL) //nó folha
    {
        pai = aux->pai;
        if (aux == pai->fEsq)
            pai->fEsq = NULL;
        else
            pai->fDir = NULL;
    }
    else //nó tem um filho
    {
        pai = aux->pai;
        if (aux->fEsq != NULL) //nó tem filho à esquerda
        {
            if (aux == pai->fEsq) //aux é filho da esquerda do pai
                pai->fEsq = aux->fEsq;
            else
                pai->fDir = aux->fEsq;
            aux->fEsq->pai = aux->pai;
        }
        else //nó tem filho à direita
        {
            if (aux == pai->fEsq) //aux é filho da esquerda do pai
                pai->fEsq = aux->fDir;
            else
                pai->fDir = aux->fDir;
            aux->fDir->pai = aux->pai;
        }

    }
    free(aux);
}

void percorrePreOrdem(no *aux)
{
    if (aux == NULL)
        return;
    printf("%d\n", aux->chave);
    percorrePreOrdem(aux->fEsq);
    percorrePreOrdem(aux->fDir);
}

no *retornaRaiz(ABP *arv)
{
    return arv->sentinela->fDir;
}