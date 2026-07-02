//
// Created by Vanessa on 26/05/2026.
//

#ifndef ABP_ABP_H
#define ABP_ABP_H

typedef struct no no;
typedef struct arv ABP;

//Função que aloca uma árvore AVL
ABP *alocaArvore();

no *alocaNo(int codigo);

//Função que lê os dados do arquivo, aloca um novo nó e chama a inserção
//Retorna 0 se a função não conseguir inserir todos os elementos na árvore
//Retorna 1 se terminou bem
int carregaArvore(char *nomeArquivo, ABP *arv);

//Função iterativa que insere um novo elemento na árvore e chama a função que ajusta o fb
void insereNo(ABP *arv, no *novoNo);

//Função iterativa que remove um elemento da árvore e chama a função que ajusta o fb
void removeNo(ABP *arv, int chaveRemovida);

//Percorre a árvore em pré-ordem
//printf("%d (%d) \t", &no->codigo, &no->fb);
void percorrePreOrdem(no *aux);

//Retorna raiz da árvore
no *retornaRaiz(ABP *arv);


#endif //ABP_ABP_H
