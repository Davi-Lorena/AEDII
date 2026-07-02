//
// Created by Vanessa on 08/11/2024.
//



#include "TAD_ABP.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct arvore{
    noABP *raiz;
} abp;

typedef struct no {
  noABP *fEsq, *fDir;
  int dado;  
} noABP;

//Cria uma nova árvore com raiz nula
abp *criaArvore() {
    abp *arv = (abp*) malloc(sizeof(abp));

    if(arv)
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

    if(no) {
    no->dado = valor;
    no->fDir = no->fEsq = NULL;
}

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
        if(aux->dado > novoNo->dado) 
            aux = aux->fEsq;
        else aux = aux->fDir;
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
        if (!aux->fEsq)
        {
            printf("%d \n", aux->dado);
            aux = aux->fDir;
        } else {
            pred = predecessor(aux);
            while(pred->fDir && pred->fDir != aux)
                pred = pred->fDir;

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

//Retorna o nó predecessor de um elemento na árvore
noABP *predecessor(noABP *no) {
    return no->fEsq;
}

//Retorna a chave de um determinado nó
int getChave(noABP *no) {
    return no->dado;
}

//Retorna um determinado nó, passando sua chave
//Retorna NULL caso o elemento não exista na árvore
noABP *getNo(abp *arvore, int chave) {
    noABP *aux = arvore->raiz; 

    while(aux && aux->dado != chave) {
        if(aux->dado > chave) aux = aux->fEsq;
        else aux = aux->fDir;
    }

  return aux;

}

//Retorna o nó sucessor de um elemento na árvore
noABP *sucessor(noABP *no) {
    return no->fDir; 
}

//Árvore de soma maior
// cada nó contém a soma de todos os nós maiores que aquele nó.
void somaMaior(abp *arvore) {
    noABP *aux = arvore->raiz, *suc = NULL;
    int soma = 0, temp;

    while(aux) {
        if(!aux->fDir) {
            temp = aux->dado;
            aux->dado = soma;
            soma += temp; 
            aux = aux->fEsq;
        } else {
            suc = sucessor(aux);
            while(suc->fEsq && suc->fEsq != aux) 
                suc = suc->fEsq;

        if(!suc->fEsq) {
            suc->fEsq = aux;
            aux = aux->fDir;
        } else {
            suc->fEsq = NULL;
            temp = aux->dado;
            aux->dado = soma;
            soma += temp;
            aux = aux->fEsq;
        }
        }
    }
}



