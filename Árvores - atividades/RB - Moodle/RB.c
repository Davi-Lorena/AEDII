//
// Created by Vanessa on 22/05/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "RB.h"

typedef struct RB {
    noRB *sentinelaRaiz;
    noRB *sentinelaFolha;
} rb;
typedef struct NO {
    int chave, alturaPreto;
    char cor;
    noRB *fEsq, *fDir, *pai;
} noRB;

//Função que aloca um novo nó
noRB *alocaNo(rb *arv, int chave) {
    noRB *novo = malloc(sizeof(noRB));
    if(!novo) return NULL;

    novo->chave = chave;
    novo->cor = 'V';
    novo->alturaPreto = 0;
    novo->fEsq = novo->fDir = arv->sentinelaFolha;
    novo->pai = NULL;

    return novo;
}

//Função que aloca uma árvore RB
rb *alocaArvore() {
    rb *arv = malloc(sizeof(rb));
    if(!arv) return NULL;

    arv->sentinelaFolha = alocaNo(arv, -1000);
    if(!arv->sentinelaFolha) return NULL;

    arv->sentinelaRaiz = alocaNo(arv, -100);
    if(!arv->sentinelaRaiz) return NULL;

    arv->sentinelaRaiz->cor = arv->sentinelaFolha->cor = 'P';

    return arv;
}


//Função iterativa que insere um novo nó na árvore e chama a função que ajusta o balanceamento
void insereNo(rb *arv, noRB *novoNo) {
    if(arv->sentinelaRaiz->fDir == arv->sentinelaFolha) {
        arv->sentinelaRaiz->fDir = novoNo;
        novoNo->pai = arv->sentinelaRaiz;
        novoNo->cor = 'P';
        return;
    }

    noRB *aux = arv->sentinelaRaiz->fDir, *pai;

    while(aux != arv->sentinelaFolha) {
        pai = aux;
        if(aux->chave < novoNo->chave) 
            aux = aux->fDir;
        else aux = aux->fEsq;
    }

    if(pai->chave > novoNo->chave) 
        pai->fEsq = novoNo;
    else pai->fDir = novoNo;

    novoNo->pai = pai;

    balanceamentoInsercao(arv, novoNo);

}

//Função que remove um nó da árvore RB
//retorna 1 se o nó foi removido
//retorna 0 se o elemento não foi encontrado na árvore
int removeNo(rb *arv, int valor) {
    noRB *aux = arv->sentinelaRaiz->fDir;

    while(aux != arv->sentinelaFolha && aux->chave != valor) {
        if(aux->chave < valor)
            aux = aux->fDir;
        else aux = aux->fEsq;
    }

    if(aux == arv->sentinelaFolha) return 0;

    noRB *removido = aux, *pai, *sucessor; 
    char corRemovido = aux->cor;

    if(aux->fEsq != arv->sentinelaFolha && aux->fDir != arv->sentinelaFolha) {
        noRB *pred = aux->fEsq;

        while(pred->fDir != arv->sentinelaFolha)
            pred = pred->fDir;

        removido = pred;
        corRemovido = pred->cor;

        aux->chave = pred->chave;
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

    if(corRemovido == 'P')
        balanceamentoRemocao(arv, sucessor, pai);
    free(removido);
    return 1;


}

//Percorre a árvore em pré-ordem
//printf("%d -- %s\n", chave, cor)
void percorrePreOrdem(rb *arv, noRB *aux) {
    if(aux == arv->sentinelaFolha) return;
    printf("%d -- %c -- %d\n", aux->chave, aux->cor, aux->alturaPreto);
    percorrePreOrdem(arv, aux->fEsq);
    percorrePreOrdem(arv, aux->fDir);
}

//Função que retorna a raiz da árvore
noRB *retornaRaiz(rb *arv) {
    return arv->sentinelaRaiz->fDir;
}

//**FUNÇÕES DE BALANCEAMENTO DA RUBRO NEGRA**//

//Função que corrige o balanceamento após a inserção
void balanceamentoInsercao(rb *arv, noRB *novoNo) {
    noRB *tio; 
    while(novoNo->pai->cor == 'V') {
        if(novoNo->pai == novoNo->pai->pai->fEsq) {
            tio = novoNo->pai->pai->fDir;
            if(tio->cor == 'V') {
                novoNo->pai->cor = 'P';
                tio->cor = 'P';
                novoNo->pai->pai->cor = 'V';
                novoNo = novoNo->pai->pai;
            } else {
                if(novoNo == novoNo->pai->fDir) {
                    novoNo = novoNo->pai;
                    rotacaoEsquerda(arv, novoNo);
                }

                novoNo->pai->cor = 'P';
                novoNo->pai->pai->cor = 'V';
                rotacaoDireita(arv, novoNo->pai->pai);
            }
        } else {
            tio = novoNo->pai->pai->fEsq;
            if(tio->cor == 'V') {
                novoNo->pai->cor = 'P';
                tio->cor = 'P';
                novoNo->pai->pai->cor = 'V';
                novoNo = novoNo->pai->pai;
            } else {
                if(novoNo == novoNo->pai->fEsq) {
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
            if(irmao->cor == 'V') {
                irmao->cor = 'P';
                NoPai->cor = 'V';
                rotacaoEsquerda(arv, NoPai);
                irmao = NoPai->fDir;
            }

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
    else if (noDesbalanceado == noDesbalanceado->pai->fEsq)
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
    if(filho->fEsq != arv->sentinelaFolha)
        filho->fEsq->pai = noDesbalanceado;

    if(noDesbalanceado->pai == arv->sentinelaRaiz)
        arv->sentinelaRaiz->fDir = filho;
    else if(noDesbalanceado == noDesbalanceado->pai->fEsq) 
        noDesbalanceado->pai->fEsq = filho; 
    else noDesbalanceado->pai->fDir = filho; 

    noDesbalanceado->pai = filho;
    filho->fEsq = noDesbalanceado;
}

//**FUNÇÃO PARA OPERAÇÃO DE JUNÇÃO DE DUAS RB**//

//Função que une duas árvores RB, a partir de x
//T1 tem valores menores que x
//T2 tem valores maiores que x
rb* rb_join(rb *T1, rb *T2, int x) {
    rb *T3 = alocaArvore();
    if (!T3) return NULL;
 
    noRB *noX  = alocaNo(T3, x);
    if (!noX) return NULL;
 
    noRB *raiz1 = T1->sentinelaRaiz->fDir;
    noRB *raiz2 = T2->sentinelaRaiz->fDir;
 
    /* Garantia de que as alturas estão atualizadas */
    atualiza_Altura_Preto_RB(T1);
    atualiza_Altura_Preto_RB(T2);
 
    int h1 = (raiz1 != T1->sentinelaFolha) ? raiz1->alturaPreto : 0;
    int h2 = (raiz2 != T2->sentinelaFolha) ? raiz2->alturaPreto : 0;
 
    /* ── h1 == h2 ─────────────────────────────────────── */
    if (h1 == h2) {
        noX->cor = 'P';
        noX->pai = T3->sentinelaRaiz;
        noX->fEsq = (raiz1 != T1->sentinelaFolha) ? raiz1 : T3->sentinelaFolha;
        noX->fDir = (raiz2 != T2->sentinelaFolha) ? raiz2 : T3->sentinelaFolha;
        if (noX->fEsq != T3->sentinelaFolha) noX->fEsq->pai = noX;
        if (noX->fDir != T3->sentinelaFolha) noX->fDir->pai = noX;
        T3->sentinelaRaiz->fDir = noX;
 
    /* ── h1 > h2 ──────────────────────────────────────── */
    } else if (h1 > h2) {
        /* Instala raiz de T1 em T3 */
        T3->sentinelaRaiz->fDir = raiz1;
        raiz1->pai = T3->sentinelaRaiz;
 
        /* Desce borda direita de T1 procurando nó preto com alturaPreto == h2 */
        noRB *Y   = raiz1;
        noRB *pai = T3->sentinelaRaiz;
        while (Y != T1->sentinelaFolha &&
               !(Y->cor == 'P' && Y->alturaPreto == h2)) {
            pai = Y;
            Y   = Y->fDir;
        }
 
        /* Encaixa X como filho direito do pai de Y */
        noX->cor  = 'V';
        noX->pai  = pai;
        pai->fDir = noX;
 
        noX->fEsq = (Y != T1->sentinelaFolha) ? Y : T3->sentinelaFolha;
        noX->fDir = (raiz2 != T2->sentinelaFolha) ? raiz2 : T3->sentinelaFolha;
        if (noX->fEsq != T3->sentinelaFolha) noX->fEsq->pai = noX;
        if (noX->fDir != T3->sentinelaFolha) noX->fDir->pai = noX;
 
        if (pai->cor == 'V')
            balanceamentoInsercao(T3, noX);
 
    /* ── h2 > h1 (espelho) ────────────────────────────── */
    } else {
        T3->sentinelaRaiz->fDir = raiz2;
        raiz2->pai = T3->sentinelaRaiz;
 
        noRB *Y   = raiz2;
        noRB *pai = T3->sentinelaRaiz;
        while (Y != T2->sentinelaFolha &&
               !(Y->cor == 'P' && Y->alturaPreto == h1)) {
            pai = Y;
            Y   = Y->fEsq;
        }
 
        noX->cor  = 'V';
        noX->pai  = pai;
        pai->fEsq = noX;
 
        noX->fEsq = (raiz1 != T1->sentinelaFolha) ? raiz1 : T3->sentinelaFolha;
        noX->fDir = (Y != T2->sentinelaFolha) ? Y : T3->sentinelaFolha;
        if (noX->fEsq != T3->sentinelaFolha) noX->fEsq->pai = noX;
        if (noX->fDir != T3->sentinelaFolha) noX->fDir->pai = noX;
 
        if (pai->cor == 'V')
            balanceamentoInsercao(T3, noX);
    }
 
    /* Corrige sentinelas e atualiza alturas */
    atualiza_Sentinela_Folha(T1, T2, T3, T3->sentinelaRaiz->fDir);
    atualiza_Altura_Preto_RB(T3);
    T3->sentinelaRaiz->fDir->cor = 'P';
 
    return T3;
}

//Função recursiva que atualiza a altura de preto de todos os nós
int atualiza_Altura_Preto(rb *arv, noRB *noAux) {
     if (noAux == arv->sentinelaFolha) return 0;
 
    int altEsq = atualiza_Altura_Preto(arv, noAux->fEsq);
    int altDir = atualiza_Altura_Preto(arv, noAux->fDir);
    int alt    = (altEsq > altDir) ? altEsq : altDir;
 
    noAux->alturaPreto = (noAux->cor == 'P') ? alt + 1 : alt;
    return noAux->alturaPreto;
}

//Função que atualiza a altura de preto da árvore como sendo a altura de preto da raiz
void atualiza_Altura_Preto_RB(rb *arv) {
    atualiza_Altura_Preto(arv, arv->sentinelaRaiz->fDir);
}

//Função recursiva que atualiza o ponteiro sentinela folha após a junção de duas RB
void atualiza_Sentinela_Folha(rb *T1, rb *T2, rb *novaRB, noRB *aux) {
    if (aux == novaRB->sentinelaFolha) return;
    if (aux == T1->sentinelaFolha || aux == T2->sentinelaFolha) return;
 
    if (aux->fEsq == T1->sentinelaFolha || aux->fEsq == T2->sentinelaFolha)
        aux->fEsq = novaRB->sentinelaFolha;
    else
        atualiza_Sentinela_Folha(T1, T2, novaRB, aux->fEsq);
 
    if (aux->fDir == T1->sentinelaFolha || aux->fDir == T2->sentinelaFolha)
        aux->fDir = novaRB->sentinelaFolha;
    else
        atualiza_Sentinela_Folha(T1, T2, novaRB, aux->fDir);
}

