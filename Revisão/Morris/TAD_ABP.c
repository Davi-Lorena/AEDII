#include <stdio.h>
#include <stdlib.h>
#include "TAD_ABP.h"

typedef struct no {
    noABP *fEsq, *fDir;
    int dado;
} noABP;

typedef struct arvore{
noABP *raiz;
} abp;


//Cria uma nova árvore com raiz nula
abp *criaArvore() {
    abp *arv = (abp*) malloc(sizeof(abp));
    
    arv->raiz = NULL;

    return arv;
}

//Retorna a raiz da árvore
noABP *retornaRaiz(abp *arvore) {
    return arvore->raiz;
}

//Cria um novo nó
noABP *criaNo(int valor) {
    noABP *no = (noABP*) malloc(sizeof(noABP));
    no->fEsq = no->fDir = NULL;
    no->dado = valor;

    return no;
}

//Insere um novo nó na árvore
void insere(abp *arvore, noABP *novoNo) {
    noABP *aux = NULL, *pai = NULL;

    if(!arvore->raiz) {
        arvore->raiz = novoNo;
        return;
    }

    aux = arvore->raiz;

    while(aux) {
        pai = aux; 
        if(novoNo->dado > aux->dado) aux = aux->fDir;
        else aux = aux->fEsq;
    }

    if(pai->dado < novoNo->dado) 
        pai->fDir = novoNo;
    else pai->fEsq = novoNo;
}

//Travessia Morris
void travessiaMorris(abp *arvore) {
noABP *aux = arvore->raiz, *pred = NULL;

if(!aux) return;

while(aux) {
    if(!aux->fEsq) {
        printf("%d \n", aux->dado);
        aux = aux->fDir;
    } else {
         pred = aux->fEsq;
            while (pred->fDir && pred->fDir != aux) {
                pred = pred->fDir;
            }
            
            if(!pred->fDir) {
                pred->fDir = aux;
                aux = aux->fEsq;
            } else {
                pred->fDir = NULL;
                  printf("%d \n", aux->dado);
                aux = aux->fDir;
        }
    }
}

}

//Encontra o nó predecessor de um nó da árvore
noABP *predecessor(noABP *no) {
     noABP *aux, *pred;

    pred = aux = no->fEsq; 

    while(aux) {
        pred = aux;
        aux = aux->fDir;
    } 

    return pred;
}

//Retorna a chave de um determinado nó
int getChave(noABP *no) {
    return no->dado;
}

//Retorna um determinado nó, passando sua chave
//Retorna NULL caso o elemento não exista na árvore
noABP *getNo(abp *arvore, int chave) {
    if(arvore->raiz->dado == chave) return arvore->raiz;

    noABP *aux = arvore->raiz; 

    while(aux && aux->dado != chave) {
        if(aux->dado > chave) aux = aux->fEsq;
        else aux = aux->fDir;
    }

    if(!aux) return NULL;

    return aux;
}
