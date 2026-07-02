#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

struct no {
    int chave, fb;
    noAVL *pai, *fEsq, *fDir;
};

struct AVL {
    noAVL *sentinela;
    int totalElementos;
};

arvAVL *alocaArvore(){

    arvAVL *novaArvore = malloc(sizeof(arvAVL));
    if(!novaArvore) return NULL;

    novaArvore->sentinela = alocaNo(-1000); // Valor convencionado para cada caso 
    novaArvore->totalElementos = 0;

    return novaArvore;
}

noAVL *alocaNo(int cod) {
    noAVL *novoNo = malloc(sizeof(noAVL));
    if(!novoNo) return NULL;

    novoNo->chave = cod;
    novoNo->fb = 0;
    novoNo->fDir = novoNo->fEsq = novoNo->pai = NULL;

    return novoNo;
}

int carregaArvore(char *nomeArq, arvAVL *arv) {
    FILE *arq;
    int chave;
    noAVL *novoNo;

    arq = fopen(nomeArq, "r");

    while(!feof(arq)) {
        fscanf(arq, "%d", &chave);
        novoNo = alocaNo(chave);
        insereNo(arv, novoNo);
    }

    return 0;
}

void insereNo(arvAVL *arv, noAVL *novoNo) {
    if(!arv->sentinela->fDir) {
        arv->sentinela->fDir = novoNo;
        novoNo->pai = arv->sentinela;
        return;
    }

    noAVL *aux = arv->sentinela->fDir, *pai;

    while(aux) {
        pai = aux;
        if(novoNo->chave < aux->chave)
            aux = aux->fEsq;
        else aux = aux->fDir;
    }

    if(novoNo->chave < pai->chave)  
        pai->fEsq = novoNo;
    else pai->fDir = novoNo;

    novoNo->pai = pai;
    arv->totalElementos++;

    ajustaFBInsercao(arv, novoNo);
}

void ajustaFBInsercao(arvAVL *arv, noAVL *novoNo) {
    noAVL *aux = novoNo->pai;

    if(novoNo->chave < aux->chave) 
        aux->fb--;
    else aux->fb++;

    while(aux != arv->sentinela && aux->fb != 0 && aux->fb != 2 && aux->fb != -2) {
        aux = aux->pai;

        if(aux->chave < aux->pai->chave) 
            aux->pai->fb--;
        else aux->pai->fb++;
    }
    
    if(aux->pai->fb == 2 || aux->pai->fb == -2) {
        balanceamento(arv, aux->pai);
    }
}

void ajustaFBRemocao(arvAVL *arv, noAVL *noPai, int chaveRemovida) {
    if(noPai == arv->sentinela) 
        return;
    
    if(chaveRemovida < noPai->chave) 
        noPai->fb--;
    else noPai->fb++;

    while(noPai != arv->sentinela->fDir && noPai->fb == 0) {
        noPai = noPai->pai;

        if(chaveRemovida < noPai->chave) 
            noPai->fb--;
        else noPai->fb++;
    }

    if(noPai->fb == 2 || noPai->fb == -2) 
        balanceamento(arv, noPai);
    
    if(noPai != arv->sentinela->fDir && noPai->fb == 0) 
        ajustaFBRemocao(arv, noPai, chaveRemovida);
    
}

void balanceamento(arvAVL *arv, noAVL *noDesbalanceado) {
noAVL *noFilho;

if(noDesbalanceado->fb == 2) { // Direita maior que a esquerda   
    noFilho = noDesbalanceado->fDir;
    if(noFilho->fb == -1) {
        noAVL *neto = noFilho->fEsq;
        int fbNeto = neto->fb;
        rotacaoDireita(arv, noFilho);
        rotacaoEsquerda(arv, noDesbalanceado);

        // Ajustando os FBs 
        if(fbNeto == 0) {
            noDesbalanceado->fb = 0;
            noFilho->fb = 0;
            neto->fb = 0;
        } else if(fbNeto == -1) {
            noDesbalanceado->fb = 0;
            noFilho->fb = 1;
            neto->fb = 0;
        } else {
            noDesbalanceado->fb = -1;
            noFilho->fb = 0;
            neto->fb = 0;
        }

    } else {
        int fbFilho = noFilho->fb;
        rotacaoEsquerda(arv, noDesbalanceado);
        if (fbFilho == 0) {
            noDesbalanceado->fb = 0;
        } else {
            noDesbalanceado->fb = 1;
            noFilho->fb = -1;
        }
    }
}
else {
        noFilho = noDesbalanceado->fEsq;

        if (noFilho->fb == 1) {
            // Rotação Dupla (Esquerda no filho, depois Direita no desbalanceado)
            noAVL *neto = noFilho->fDir;
            int fbNeto = noFilho->fDir->fb;
            rotacaoEsquerda(arv, noFilho);
            rotacaoDireita(arv, noDesbalanceado);

        if(fbNeto == 0) {
            noDesbalanceado->fb = 0;
            noFilho->fb = 0;
            neto->fb = 0;
        } else if(fbNeto == -1) {
            noDesbalanceado->fb = 1;
            noFilho->fb = 0;
            neto->fb = 0;
        } else {
            noDesbalanceado->fb = 0;
            noFilho->fb = -1;
            neto->fb = 0;
        }

        }
        else {
            // Rotação Simples à Direita
            int fbFilho = noFilho->fb;
            rotacaoDireita(arv, noDesbalanceado);

            if(fbFilho == 0) {
                noDesbalanceado->fb = -1;
                noFilho->fb = 1;
            } else {
                noDesbalanceado->fb = 0;
                noFilho->fb = 0;
            }

        }
    }

}


void rotacaoEsquerda(arvAVL *arv, noAVL *noDesbalanceado){
noAVL *filho = noDesbalanceado->fDir;
noDesbalanceado->fDir = filho->fEsq;

if(filho->fEsq) {
    filho->fEsq->pai = noDesbalanceado;
}
filho->pai = noDesbalanceado->pai;

if(noDesbalanceado->pai == arv->sentinela) 
    arv->sentinela->fDir = filho;
else if (noDesbalanceado == noDesbalanceado->pai->fEsq) 
    noDesbalanceado->pai->fEsq = filho;
else 
    noDesbalanceado->pai->fDir = filho;

filho->fEsq = noDesbalanceado;
noDesbalanceado->pai = filho;
    
}

void rotacaoDireita(arvAVL *arv, noAVL *noDesbalanceado) {
    noAVL *filho = noDesbalanceado->fEsq;

    noDesbalanceado->fEsq = filho->fDir;
    if(filho->fDir) 
        filho->fDir->pai = noDesbalanceado;
    filho->pai = noDesbalanceado->pai;

    if(noDesbalanceado->pai == arv->sentinela) 
        arv->sentinela->fDir = filho; 
    else if(noDesbalanceado == noDesbalanceado->pai->fEsq) 
        noDesbalanceado->pai->fEsq = filho;
    else 
        noDesbalanceado->pai->fDir = filho;

    filho->fDir = noDesbalanceado;
    noDesbalanceado->pai = filho;
    
}

void percorrePreOrdem(noAVL *aux) {
    printf("%d (%d) \t", &aux->chave, &aux->fb);
    percorrePreOrdem(aux->fEsq);
    percorrePreOrdem(aux->fDir);
}


noAVL *retornaRaiz(arvAVL *arv) {
    return arv->sentinela->fDir;
}