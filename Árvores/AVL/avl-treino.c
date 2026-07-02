#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

typedef struct no {
    int chave, fb;
    noAVL *fEsq, *fDir, *pai;
} noAVL;

typedef struct AVL {
    noAVL *sentinela;
} arvAVL;

noAVL *alocaNo(int codigo) {
    noAVL *novoNo = malloc(sizeof(novoNo));
    if(!novoNo) return NULL;

    novoNo->chave = codigo;
    novoNo->fb = 0;
    novoNo->fDir = novoNo->fEsq = novoNo->pai = NULL;

    return novoNo;
}

//Função que aloca uma árvore AVL
arvAVL *alocaArvore() {
    arvAVL *arv = malloc(sizeof(arvAVL));
    if(!arv) return;

    arv->sentinela = alocaNo(-100);
    if(!arv->sentinela) return NULL;

    return arv;
}


//Função que lê os dados do arquivo, aloca um novo nó e chama a inserção
//Retorna 1 se a função não conseguir inserir todos os elementos na árvore
//Retorna 0 se terminou bem
int carregaArvore(char *nomeArquivo, arvAVL *arv) {
     FILE *arq;
    int chave;
    noAVL *novoNo;

    arq = fopen(nomeArquivo, "r");

    while(!feof(arq)) {
        fscanf(arq, "%d", &chave);
        novoNo = alocaNo(chave);
        insereNo(arv, novoNo);
    }

    return 0;
}

//Função iterativa que insere um novo elemento na árvore e chama a função que ajusta o fb
void insereNo(arvAVL *arv, noAVL *novoNo) {
    if(!arv->sentinela->fDir) {
        arv->sentinela->fDir = novoNo;
        novoNo->pai = arv->sentinela;
        return;
    }

    noAVL *aux = arv->sentinela->fDir, *pai = NULL;

    while(aux) {
        pai = aux;

        if(aux->chave < novoNo->chave) 
            aux = aux->fDir;
        else aux = aux->fEsq;
    }

    if(pai->chave < novoNo->chave)
        pai->fDir = novoNo;
    else pai->fEsq = novoNo;

    novoNo->pai = pai;

    ajustaFBInsercao(arv, novoNo);
} 

int removeNo(arvAVL *arv, int chave) {
    if(!arv->sentinela->fDir) return 0;

    noAVL *aux = arv->sentinela->fDir, *pai = NULL;
    int valorRemover;

    while(aux && aux->chave != chave) {
        pai = aux;

        if(chave > aux->chave)
            aux = aux->fDir;
        else aux = aux->fEsq;
    }

    if(!aux) return 0;

    if(aux->fEsq && aux->fDir) {
        noAVL *pred = aux->fEsq;

        while(pred->fDir)
            pred = pred->fDir;

        aux->chave = pred->chave;
        aux = pred;
    }

    pai = aux->pai;
    valorRemover = aux->chave;

    if(aux->fEsq || aux->fDir) {
        if(aux->fEsq) {
            if(aux == aux->pai->fEsq)
                aux->pai->fEsq = aux->fEsq;
            else aux->pai->fDir = aux->fEsq;
            aux->fEsq->pai = aux->pai;
        } else {
            if(aux == aux->pai->fEsq)
                aux->pai->fEsq = aux->fDir;
            else aux->pai->fDir = aux->fDir;
            aux->fDir->pai = aux->pai;
        }

    } else {
        if (pai->fEsq == aux)
            pai->fEsq = NULL;
        else
            pai->fDir = NULL;
    } 

    free(aux);
    ajustaFBRemocao(arv, pai, chave);
}

//Função que ajusta o fb após a inserção e chama o balanceamento, caso necessário
void ajustaFBInsercao(arvAVL *arv, noAVL *novoNo) {
    noAVL *aux = novoNo->pai, 
    *filho = novoNo;

    while(aux != arv->sentinela) {
        if(filho == aux->fEsq)
            aux->fb--;
        else aux->fb++;

        if(!aux->fb) return;
        else if (aux->fb == 2 || aux->fb == -2) {
            balanceamento(arv, aux);
            return;
        }
        filho = aux;
        aux = aux->pai;
    }
}

// Função que ajusta o fb após a remoção de um nó 
void ajustaFBRemocao(arvAVL *arv, noAVL *pai, int chaveRemovida) {
    noAVL *aux = pai;

    while(aux != arv->sentinela) {
        if(chaveRemovida < aux->chave)
            aux->fb++;
        else aux->fb--;

        if(aux->fb == 2 || aux->fb == -2) {
            balanceamento(arv, aux);

            aux = aux->pai;

            if(aux->fb) return;

            aux = aux->pai;

            if(aux == arv->sentinela)
                chaveRemovida = 0;
            else if (aux->fEsq)
                chaveRemovida = aux->fEsq->chave;
            else chaveRemovida = aux->fDir->chave;
        } else if(aux->fb == 1 || aux->fb == -1) {
            return;
        } else {
            chaveRemovida = aux->chave;
            aux = aux->pai;
        }
    }
}

//Função que corrige o balamenceamento da árvore
void balanceamento(arvAVL *arv, noAVL *noDesbalanceado) {
    noAVL *filho, *neto;
    int fbNeto;

    if(noDesbalanceado->fb == 2) {
        filho = noDesbalanceado->fDir;
        if(filho->fb == -1) {
            neto = filho->fEsq;
            fbNeto = filho->fEsq->fb;
            rotacaoDireita(arv, filho);
            rotacaoEsquerda(arv, noDesbalanceado);

            if(fbNeto == 0) {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
                neto->fb = 0;
            } else if(fbNeto == -1) {
                noDesbalanceado->fb = 0;
                filho->fb = 1;
                neto->fb = 0;
            } else {
                noDesbalanceado->fb = -1;
                filho->fb = 0;
                neto->fb = 0;
            }
        } else {
            rotacaoEsquerda(arv, noDesbalanceado);
            if(filho->fb == 0) {
                noDesbalanceado->fb = 1;
                filho->fb = -1;
            } else {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
        }
    } else {
        filho = noDesbalanceado->fEsq;
        if(filho->fb == 1) {
            neto = filho->fDir;
            fbNeto = neto->fb;
            rotacaoEsquerda(arv, filho);
            rotacaoDireita(arv, noDesbalanceado);

            if(fbNeto == 0) {
                noDesbalanceado->fb = 0;
                filho->fb = 0;
                neto->fb = 0;
            } else if(fbNeto == -1) {
                noDesbalanceado->fb = 1;
                filho->fb = 0;
                neto->fb = 0;
            } else {
                noDesbalanceado->fb = 0;
                filho->fb = -1;
                neto->fb = 0;
            }
        } else {
            rotacaoDireita(arv, noDesbalanceado);
            if(filho->fb == 0) {
                noDesbalanceado->fb = -1;
                filho->fb = 1;
            } else {
                noDesbalanceado = 0;
                filho->fb = 0;
            }
        }
    }
}

//Função que realiza a rotação à direita no noDesbalanceado
void rotacaoDireita(arvAVL *arv, noAVL *noDesbalanceado) {
    noAVL *filho = noDesbalanceado->fEsq;
    noDesbalanceado->fEsq = filho->fDir;

    if(filho->fDir)
        filho->fDir->pai = noDesbalanceado;

    filho->pai = noDesbalanceado->pai;

    if(noDesbalanceado->pai == arv->sentinela->fDir)
        arv->sentinela->fDir = filho;
    else if (noDesbalanceado == noDesbalanceado->pai->fDir)
        noDesbalanceado->pai->fDir = filho;
    else noDesbalanceado->pai->fEsq = filho;

    noDesbalanceado->pai = filho;
    filho->fDir = noDesbalanceado;

}

//Função que realiza a rotação à esquerda no noDesbalanceado
void rotacaoEsquerda(arvAVL *arv, noAVL *noDesbalanceado) {
    noAVL *filho = noDesbalanceado->fDir;
    noDesbalanceado->fDir = filho->fEsq;
    if(filho->fEsq)
        filho->fEsq->pai = noDesbalanceado;

    filho->pai = noDesbalanceado->pai;

    if(noDesbalanceado->pai == arv->sentinela->fDir)
        arv->sentinela->fDir = filho;
    else if(noDesbalanceado == noDesbalanceado->pai->fDir)
        noDesbalanceado->pai->fDir = filho;
    else noDesbalanceado->pai->fEsq = filho;

    filho->fEsq = noDesbalanceado;
    noDesbalanceado->pai = filho;

}

//Percorre a árvore em pré-ordem
//printf("%d (%d) \t", &no->codigo, &no->fb);
void percorrePreOrdem(noAVL *aux);

//Retorna raiz da árvore
noAVL *retornaRaiz(arvAVL *arv);
