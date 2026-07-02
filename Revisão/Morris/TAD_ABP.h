//
// Created by Vanessa on 08/11/2024.
//

#ifndef INC_6_ARVORE_TAD_ABP_H
#define INC_6_ARVORE_TAD_ABP_H

typedef struct arvore abp;
typedef struct no noABP;

//Cria uma nova árvore com raiz nula
abp *criaArvore();

//Retorna a raiz da árvore
noABP *retornaRaiz(abp *arvore);

//Cria um novo nó
noABP *criaNo(int valor);

//Insere um novo nó na árvore
void insere(abp *arvore, noABP *novoNo);

//Travessia Morris
void travessiaMorris(abp *arvore);

//Encontra o nó predecessor de um nó da árvore
noABP *predecessor(noABP *no);

//Retorna a chave de um determinado nó
int getChave(noABP *no);

//Retorna um determinado nó, passando sua chave
//Retorna NULL caso o elemento não exista na árvore
noABP *getNo(abp *arvore, int chave);


#endif //INC_6_ARVORE_TAD_ABP_H
