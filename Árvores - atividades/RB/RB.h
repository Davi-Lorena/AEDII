//
// Created by Vanessa.
//

#ifndef RB_RB_H
#define RB_RB_H

typedef struct RB rb;
typedef struct NO noRB;

//Função que aloca uma árvore RB
rb *alocaArvore();

//Função que aloca um novo nó
noRB *alocaNo(rb *arv, int chave);

int carregaArvore(char *nomeArquivo, rb *arv);

//Função iterativa que insere um novo nó na árvore e chama a função que ajusta o balanceamento
void insereNo(rb *arv, noRB *novoNo);

//Função que remove um nó da árvore RB
//retorna 1 se o nó foi removido
//retorna 0 se o elemento não foi encontrado na árvore
int removeNo(rb *arv, int valor);

//Percorre a árvore em pré-ordem
//printf("%d -- %s\n", chave, cor)
void percorrePreOrdem(rb *arv, noRB *aux);

//Função que retorna a raiz da árvore
noRB *retornaRaiz(rb *arv);

//FUNÇÕES DE BALANCEAMENTO DA RUBRO NEGRA//

//Função que corrige o balanceamento após a inserção
void balanceamentoInsercao(rb *arv, noRB *novoNo);

//Função que corrige o balanceamento após a remoção
void balanceamentoRemocao(rb *arv, noRB *NoSucessor, noRB *NoPai);

//Rotação à direita
void rotacaoDireita(rb *arv, noRB *noDesbalanceado);

//Rotação à esquerda
void rotacaoEsquerda(rb *arv, noRB *noDesbalanceado);

#endif //RB_RB_H
