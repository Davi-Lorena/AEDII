#include "AVL.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Jogador {
    int id, pontuacao, fb;
    char nome[100];
    jogador *fEsq, *fDir, *pai;
};

struct AVL {
    jogador *sentinela; 
    int totalJogadores, totalRotacaoSimples, totalRotacaoDupla; 
};

//Função que aloca uma árvore AVL
arvAVL *alocaArvore() {
    arvAVL *arv = malloc(sizeof(arvAVL));
    if(!arv) return NULL;
    // Sentinela não pode ser inicializado com NULL 
    arv->sentinela = malloc(sizeof(jogador));
    if(!arv->sentinela) 
    {     
    free(arv);
    return NULL;
    }
    arv->sentinela->fb = arv->sentinela->id = arv->sentinela->pontuacao = 0;

    arv->sentinela->fDir = arv->sentinela->fEsq = arv->sentinela->pai = NULL;

    arv->totalJogadores = arv->totalRotacaoDupla = arv->totalRotacaoSimples = 0;

    return arv;
}

//Função que aloca um jogador novo
jogador *alocaNo(int pontuacao, int id, char nome[]) {
    jogador *novoJogador = malloc(sizeof(jogador));
    if(!novoJogador) return NULL;

    novoJogador->fb = 0;
    novoJogador->id = id;
    strcpy(novoJogador->nome, nome);
    novoJogador->pontuacao = pontuacao;
    novoJogador->pai = novoJogador->fEsq = novoJogador->fDir = NULL;

    return novoJogador;
}

//Função que lê os dados do arquivo, aloca um novo nó e chama a inserção
//Retorna 1 se a função não conseguir inserir todos os elementos na árvore
//Retorna 0 se terminou bem
int montaRanking(char *nomeArquivo, arvAVL *arv) {
    int id, pontuacao;
    char nome[100];
    jogador *novo;

    FILE *arq = fopen(nomeArquivo, "r");
    if(!arq) return 1;

    while (fscanf(arq, "%d %d %[^\n]", &id, &pontuacao, nome) == 3)
    {
        novo = alocaNo(pontuacao, id, nome);
        if(!novo) 
        { 
            fclose(arq);
            return 1;
        }
        insereJogador(arv, novo);
    }
    
    fclose(arq);
    return 0;
}

//Função iterativa que insere um novo jogador na árvore e chama a função que ajusta o fb
void insereJogador(arvAVL *arv, jogador *novoJogador) {
    jogador *aux = arv->sentinela->fDir, *paiAux;

    if(!aux) {
        arv->sentinela->fDir = novoJogador;
        novoJogador->pai = arv->sentinela;
        arv->totalJogadores++;
        return;
    }

    while(aux) {
        paiAux = aux;
        if(aux->pontuacao < novoJogador->pontuacao) 
            aux = aux->fDir;
        else aux = aux->fEsq;
    }

    if(paiAux->pontuacao > novoJogador->pontuacao) 
        paiAux->fEsq = novoJogador;
    else paiAux->fDir = novoJogador;

    novoJogador->pai = paiAux;
    arv->totalJogadores++;
    ajustaFB_insercao(arv, novoJogador);
}

//Função que remove um nó da árvore AVL
//retorna 1 se o nó foi removido
//retorna 0 se o elemento não foi encontrado na árvore
int removeJogador(arvAVL *arv, int codigo) {
    jogador *aux = arv->sentinela->fDir;

    // Árvore Vazia 
    if(!aux) return 0;

    // Busca pelo nó a ser removido 
    while(aux && aux->pontuacao != codigo) {
        if(aux->pontuacao < codigo) 
            aux = aux->fDir;
        else aux = aux->fEsq;
    }

    // Nó não encontrado 
    if(!aux) return 0;

    // Se for nó com dois filhos 
    if(aux->fEsq && aux->fDir) {
        jogador *pred = aux->fEsq;

        while(pred->fDir) 
            pred = pred->fDir;
         

        aux->pontuacao = pred->pontuacao;
        aux->id = pred->id;
        strcpy(aux->nome, pred->nome);
        aux = pred;

    } 

    // Se o nó tiver um filho 
    if(aux->fEsq || aux->fDir) {
        if(aux->fEsq) {
            if(aux->pai->fEsq == aux) 
                aux->pai->fEsq = aux->fEsq;
            else aux->pai->fDir = aux->fEsq;
            aux->fEsq->pai = aux->pai;
        } else {
            if(aux->pai->fEsq == aux)
                aux->pai->fEsq = aux->fDir;
            else aux->pai->fDir = aux->fDir;
            aux->fDir->pai = aux->pai;
        }
    }

    // Nó folha
    if(!aux->fEsq && !aux->fDir) {
        if(aux->pai->fEsq == aux)
            aux->pai->fEsq = NULL;
        else aux->pai->fDir = NULL;
    }

    ajustaFB_remocao(arv, aux->pai, aux->pontuacao);
    arv->totalJogadores--;
    free(aux);
    return 1;

}

//Função que atualiza a pontuação de um jogador
//Para tanto, o jogador deverá ser removido da AVL e, posteriormente, inserido novamente com a nova pontuação
//Retorna 1 se a atualização ocorreu
//Retorna 0 caso contrário
int atualizaPontuacao(arvAVL *arv, int pontuacaoAtual, int novaPontuacao) {
    jogador *aux = arv->sentinela->fDir, *jogadorPontuacaoNova;

    while(aux && aux->pontuacao != pontuacaoAtual) {
        if(aux->pontuacao < pontuacaoAtual)
            aux = aux->fDir;
        else aux = aux->fEsq;
    }

    if(!aux) return 0;

    jogadorPontuacaoNova = alocaNo(novaPontuacao, aux->id, aux->nome);
    if(!jogadorPontuacaoNova) return 0;
    removeJogador(arv, pontuacaoAtual);
    insereJogador(arv, jogadorPontuacaoNova);

    return 1;
}

//Função que imprime as informações da árvore
//Total jogadores, total rotações simples, total rotações duplas, nessa ordem, uma informação por linha
void estatisticasAVL(arvAVL *arv) {
    printf("%d\n", arv->totalJogadores);
    printf("%d\n", arv->totalRotacaoSimples);
    printf("%d\n", arv->totalRotacaoDupla);
}

//Percorre a árvore em pré-ordem
//printf("%d %d %s -- %d\n", pontuação, id, nome, fb)
void percorrePreOrdem(jogador *aux) {
    if(!aux) return;
    printf("%d %d %s -- %d\n", aux->pontuacao, aux->id, aux->nome, aux->fb);
    percorrePreOrdem(aux->fEsq);
    percorrePreOrdem(aux->fDir);
}

//Função que imprime na tela os top X jogadores do ranking
//Impressão em ordem decrescente
//o valor de X é informado pelo usuário
//printf("%d\n", pontuação)
void topX(jogador *aux, int *X) {
    if (!aux || *X <= 0) return;
    topX(aux->fDir, X);
    if (*X > 0) {
        printf("%d\n", aux->pontuacao);
        (*X)--;
    }
    if(*X > 0)
        topX(aux->fEsq, X);
}

//Função que mostra o ranking todo (ordem decrescente)
//printf("%d %d %s\n", pontuação, id, nome);
void mostraRanking(jogador *aux) {
    if(!aux) return;
    mostraRanking(aux->fDir);
    printf("%d %d %s\n", aux->pontuacao, aux->id, aux->nome);
    mostraRanking(aux->fEsq);
}

//Retorna raiz da árvore
jogador *retornaRaiz(arvAVL *arv) {
    return arv->sentinela->fDir;
}


//*****FUNÇÕES AVL******///

//Função que ajusta o fb após a inserção e chama o balanceamento, caso necessário
void ajustaFB_insercao(arvAVL *arv, jogador *novoJogador) {
    jogador *aux = novoJogador;
    jogador *pai = aux->pai;

    while(pai != arv->sentinela) {
        if(aux == pai->fEsq) 
            pai->fb--;
        else pai->fb++;

        if(!pai->fb) break;
        if(pai->fb == 2 || pai->fb == -2) {
            balanceamento(arv, pai);
            break;
        }

        aux = pai;
        pai = pai->pai;

    }
}

//Função que ajusta o fb após a remoção e chama o balanceamento, caso necessário
void ajustaFB_remocao(arvAVL *arv, jogador *pai, int valorRemovido) {
    if(pai == arv->sentinela) return;

    if(valorRemovido < pai->pontuacao)
        pai->fb++;
    else pai->fb--;

    while(pai != arv->sentinela && pai->fb == 0) {
        pai = pai->pai;
        if(valorRemovido < pai->pontuacao) 
        pai->fb++;
        else pai->fb--;
    }

    if(pai->fb == 2 || pai->fb == -2)
        balanceamento(arv, pai);

    if(pai->pai != arv->sentinela && pai->pai->fb == 0)
        ajustaFB_remocao(arv, pai->pai, valorRemovido);
}

//Função que corrige o balamenceamento da árvore
//Cada rotação executada deve atualizar o totalRotações da árvore
void balanceamento(arvAVL *arv, jogador *noDesbalanceado) {
    jogador *filho; 

    if(noDesbalanceado->fb == 2) {
        filho = noDesbalanceado->fDir;

        if(filho->fb == -1) {
            jogador *neto = filho->fEsq;
            rotacaoDireita(arv, filho);
            rotacaoEsquerda(arv, noDesbalanceado);
            arv->totalRotacaoDupla++;

            if(neto->fb == 0) {
                noDesbalanceado->fb = filho->fb = neto->fb = 0;
            } else if(neto->fb == -1) {
                noDesbalanceado->fb = 0;
                filho->fb = 1;
                neto->fb = 0;
            } else {
                noDesbalanceado->fb = -1;
                filho->fb = neto->fb = 0;
            }

        } else {
            rotacaoEsquerda(arv, noDesbalanceado);
            arv->totalRotacaoSimples++;
            if(filho->fb == 1) { 
                noDesbalanceado->fb = filho->fb = 0;
            } else {
                noDesbalanceado->fb = 1;
                filho->fb = -1;
            }
        }
    } else {
        filho = noDesbalanceado->fEsq;
        if(filho->fb == 1) {
            jogador *neto = filho->fDir;
            rotacaoEsquerda(arv, filho);
            rotacaoDireita(arv, noDesbalanceado);
            arv->totalRotacaoDupla++;

            if(neto->fb == 0) {
                noDesbalanceado->fb = filho->fb = neto->fb = 0;
            } else if(neto->fb == -1) {
                noDesbalanceado->fb = 1;
                filho->fb = neto->fb = 0;
            } else {
                noDesbalanceado->fb = neto->fb = 0;
                filho->fb = -1;
            }
        } else {
            rotacaoDireita(arv, noDesbalanceado);
            arv->totalRotacaoSimples++;

            if(filho->fb == -1) {
                noDesbalanceado->fb = filho->fb = 0;
            } else {
                noDesbalanceado->fb = -1;
                filho->fb = 1;
            }
        }
    }

}

void rotacaoDireita(arvAVL *arv, jogador *noDesbalanceado) {
    jogador *filho = noDesbalanceado->fEsq;
    noDesbalanceado->fEsq = filho->fDir;

    if(filho->fDir)
        filho->fDir->pai = noDesbalanceado;
    
    filho->pai = noDesbalanceado->pai;
    
    if(noDesbalanceado->pai == arv->sentinela)
        arv->sentinela->fDir = filho;
    else if(noDesbalanceado == noDesbalanceado->pai->fDir)
        noDesbalanceado->pai->fDir = filho;
    else noDesbalanceado->pai->fEsq = filho;

    filho->fDir = noDesbalanceado;
    noDesbalanceado->pai = filho;

}

void rotacaoEsquerda(arvAVL *arv, jogador *noDesbalanceado) {
    jogador *filho = noDesbalanceado->fDir;
    noDesbalanceado->fDir = filho->fEsq;

    if(filho->fEsq) 
        filho->fEsq->pai = noDesbalanceado;
    filho->pai = noDesbalanceado->pai;

    if(noDesbalanceado->pai == arv->sentinela) 
        arv->sentinela->fDir = filho;
    else if(noDesbalanceado == noDesbalanceado->pai->fEsq) 
        noDesbalanceado->pai->fEsq = filho;
    else noDesbalanceado->pai->fDir = filho;

    filho->fEsq = noDesbalanceado;
    noDesbalanceado->pai = filho;
}