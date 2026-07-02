#include <stdio.h>
#include <stdlib.h>
#include "RB.h"

typedef struct RB {
    noRB *sentinelaRaiz, *sentinelaFolha;
    int totalElementos;
};

typedef struct NO {
    char cor;
    int chave; 
    noRB 
    *fEsq, 
    *fDir, 
    *pai;
};

//Função que aloca um novo nó
noRB *alocaNo( rb *arv, int chave) {
    noRB *novoNo = malloc(sizeof(noRB));
    if(!novoNo) return NULL;

    novoNo->chave = chave;
    novoNo->cor = 'V';
    novoNo->fDir = novoNo->fEsq = arv->sentinelaFolha;
    novoNo->pai = NULL;

    return novoNo;
}

//Função que aloca uma árvore RB
rb *alocaArvore() {
    rb *arv = malloc(sizeof(rb));
    if(!arv) return NULL;
    
    arv->sentinelaFolha = alocaNo(arv, -100);
    if(!arv->sentinelaFolha) return NULL;

    arv->sentinelaRaiz = alocaNo(arv, -1000);
    if(!arv->sentinelaRaiz) return NULL;

    arv->sentinelaFolha->cor = arv->sentinelaRaiz->cor = 'P';
    arv->totalElementos = 0;
    return arv;
}


int carregaArvore(char nomeArquivo[30], rb *arv)
{
    FILE *arq = fopen(nomeArquivo, "r");
    if (!arq)
    {
        printf("Erro ao abrir o arquivo");
        return 0;
    }

    int codigo;
    noRB *novoNo;

    while(!feof(arq))
    {
        fscanf(arq, "%d", &codigo);
        novoNo = alocaNo(arv, codigo);
        if (!novoNo)
            return 0;
        insereNo(arv, novoNo);
    }

    return 1;
}

//Função iterativa que insere um novo nó na árvore e chama a função que ajusta o balanceamento
void insereNo(rb *arv, noRB *novoNo) {
     if (arv->sentinelaRaiz->fDir == arv->sentinelaFolha)
    {
        arv->sentinelaRaiz->fDir = novoNo;
        novoNo->pai = arv->sentinelaRaiz;
        arv->totalElementos++;
        return;
    }

    noRB *aux = arv->sentinelaRaiz->fDir;
    noRB *pai = arv->sentinelaRaiz;

    while (aux != arv->sentinelaFolha)
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

    balanceamentoInsercao(arv, novoNo);
}

//Função que remove um nó da árvore RB
//retorna 1 se o nó foi removido
//retorna 0 se o elemento não foi encontrado na árvore
int removeNo(rb *arv, int valor) {
    if(arv->sentinelaRaiz->fDir == arv->sentinelaFolha) 
        return 0;
    
    noRB *aux = arv->sentinelaRaiz->fDir;
    char corNoRemovido;
    
    while(aux != arv->sentinelaFolha && aux->chave != valor) {
        if(aux->chave > valor)
            aux = aux->fEsq;
        else aux = aux->fDir;
    }

    if(aux == arv->sentinelaFolha) return 0;

    noRB *removido = aux, 
    *sucessor, 
    *pai;
    corNoRemovido = aux->cor;
    
    if(aux->fEsq != arv->sentinelaFolha && aux->fDir != arv->sentinelaFolha) {
        noRB *predecessor = aux->fEsq;
        while(predecessor->fDir != arv->sentinelaFolha)
            predecessor = predecessor->fDir;

        removido = predecessor; 
        corNoRemovido = removido->cor;
        
        aux->chave = predecessor->chave;
    }

    if(removido->fEsq != arv->sentinelaFolha)
        sucessor = removido->fEsq;
    else sucessor = removido->fDir;
    

    pai = removido->pai;
    if(sucessor != arv->sentinelaFolha)
        sucessor->pai = pai;
    
    if(removido->pai->fEsq == removido)
        removido->pai->fEsq = sucessor;
    else removido->pai->fDir = sucessor;


    if(corNoRemovido == 'P')
        balanceamentoRemocao(arv, sucessor, pai);
    free(removido);
    arv->totalElementos--;
    return 1;
}

//Percorre a árvore em pré-ordem
//printf("%d -- %s\n", chave, cor)
void percorrePreOrdem(rb *arv, noRB *aux) {
    if(aux == arv->sentinelaFolha) return; 
    printf("%d -- %s\n", aux->chave, aux->cor);
    percorrePreOrdem(arv, aux->fEsq);
    percorrePreOrdem(arv, aux->fDir);
}

//Função que retorna a raiz da árvore
noRB *retornaRaiz(rb *arv) {
    return arv->sentinelaRaiz->fDir;
}

//FUNÇÕES DE BALANCEAMENTO DA RUBRO NEGRA//

//Função que corrige o balanceamento após a inserção
void balanceamentoInsercao(rb *arv, noRB *novoNo) {
    while (novoNo->pai->cor == 'V')
    {
        if(novoNo->pai == novoNo->pai->pai->fEsq) {
            noRB *tio = novoNo->pai->pai->fDir;
            if(tio->cor == 'V') {
                novoNo->pai->cor = tio->cor = 'P';
                novoNo->pai->pai->cor = 'V';
                novoNo = novoNo->pai->pai;
            } else {
                if (novoNo == novoNo->pai->fDir) {
                novoNo = novoNo->pai;
                rotacaoEsquerda(arv, novoNo);
                }
                novoNo->pai->cor = 'P';
                novoNo->pai->pai->cor = 'V';
                rotacaoDireita(arv, novoNo->pai->pai);
            }
        } else {
            noRB *tio = novoNo->pai->pai->fEsq;
            if(tio->cor == 'V') {
                novoNo->pai->cor = tio->cor = 'P';
                novoNo->pai->pai->cor = 'V';
                novoNo = novoNo->pai->pai;
            } else {
                if (novoNo == novoNo->pai->fEsq) {
                    novoNo = novoNo->pai;
                    rotacaoDireita(arv, novoNo);
                }

                novoNo->pai->cor = 'P';
                novoNo->pai->pai->cor = 'V';
                rotacaoEsquerda(arv, novoNo->pai->pai);
            }
        }
    }
    
    arv->sentinelaRaiz->fDir->cor = 'P';
}

//Função que corrige o balanceamento após a remoção
void balanceamentoRemocao(rb *arv, noRB *NoSucessor, noRB *NoPai) {
    noRB *irmao;
    while(NoSucessor != arv->sentinelaRaiz->fDir && NoSucessor->cor == 'P') {
        if(NoSucessor == NoPai->fEsq) {
            irmao = NoPai->fDir;
            // Caso 1 -> Vai levar ao 2, 3 ou 4
            if(irmao->cor == 'V') {
                irmao->cor = 'P';
                NoPai->cor = 'V';
                rotacaoEsquerda(arv, NoPai);
                irmao = NoPai->fDir;
            }

            // Caso 2 
            if(irmao->fEsq->cor == 'P' && irmao->fDir->cor == 'P') {
                irmao->cor = 'V';
                NoSucessor = NoPai;
                NoPai = NoPai->pai;
            } else {
                if(irmao->fDir->cor == 'P') {
                irmao->fEsq->cor = 'P';
                irmao->cor = 'V';
                rotacaoDireita(arv, irmao);
                irmao = NoPai->fDir;
                }

                irmao->cor = NoPai->cor;
                NoPai->cor = 'P';
                irmao->fDir->cor = 'P';
                rotacaoEsquerda(arv, NoPai);
                NoSucessor = arv->sentinelaRaiz->fDir;
            }
        } else {
            irmao = NoPai->fEsq;
            if(irmao->cor == 'V') {
                irmao->cor = 'P';
                NoPai->cor = 'V';
                rotacaoDireita(arv, NoPai);
                irmao = NoPai->fEsq;
            }
            
            if(irmao->fEsq->cor == 'P' && irmao->fDir->cor == 'P') {
                irmao->cor = 'V';
                NoSucessor = NoPai;
                NoPai = NoPai->pai;
            } else {
                if(irmao->fEsq->cor == 'P') {
                    irmao->fDir->cor = 'P';
                    irmao->cor = 'V';
                    rotacaoEsquerda(arv, irmao);
                    irmao = NoPai->fEsq;
                }
                
                irmao->cor = NoPai->cor;
                NoPai->cor = 'P';
                irmao->fEsq->cor = 'P';
                rotacaoDireita(arv, NoPai);
                NoSucessor = arv->sentinelaRaiz->fDir;
            }
        }
    }
    NoSucessor->cor = 'P';
}

//Rotação à direita
void rotacaoDireita(rb *arv, noRB *noDesbalanceado) {
    noRB *filho = noDesbalanceado->fEsq;
    noDesbalanceado->fEsq = filho->fDir;

    filho->pai = noDesbalanceado->pai;
    if(filho->fDir != arv->sentinelaFolha)
        filho->fDir->pai = noDesbalanceado;

    if(noDesbalanceado->pai == arv->sentinelaRaiz)
        arv->sentinelaRaiz->fDir = filho;
    else if (noDesbalanceado->pai->fEsq == noDesbalanceado)
        noDesbalanceado->pai->fEsq = filho;
    else noDesbalanceado->pai->fDir = filho;

    filho->fDir = noDesbalanceado;
    noDesbalanceado->pai = filho;
}

//Rotação à esquerda
void rotacaoEsquerda(rb *arv, noRB *noDesbalanceado) {
    noRB *filho = noDesbalanceado->fDir;
    noDesbalanceado->fDir = filho->fEsq;

    filho->pai = noDesbalanceado->pai;
    if(filho->fEsq) 
        filho->fEsq->pai = noDesbalanceado;

    if(noDesbalanceado->pai == arv->sentinelaRaiz) 
        arv->sentinelaRaiz->fDir = filho; 
    else if(noDesbalanceado == noDesbalanceado->pai->fEsq) 
        noDesbalanceado->pai->fEsq = filho;
    else noDesbalanceado->pai->fDir = filho;

    noDesbalanceado->pai = filho; 
    filho->fEsq = noDesbalanceado;
}
