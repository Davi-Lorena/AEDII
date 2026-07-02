#ifndef AVL_AVL_H
#define AVL_AVL_H

typedef struct no noAVL;
typedef struct AVL arvAVL;

//Função que aloca uma árvore AVL
arvAVL *alocaArvore();

noAVL *alocaNo(int codigo);

//Função que lê os dados do arquivo, aloca um novo nó e chama a inserção
//Retorna 1 se a função não conseguir inserir todos os elementos na árvore
//Retorna 0 se terminou bem
int carregaArvore(char *nomeArquivo, arvAVL *arv);

//Função iterativa que insere um novo elemento na árvore e chama a função que ajusta o fb
void insereNo(arvAVL *arv, noAVL *novoNo);

int removeNo(arvAVL *arv, int chave);

//Função que ajusta o fb após a inserção e chama o balanceamento, caso necessário
void ajustaFBInsercao(arvAVL *arv, noAVL *novoNo);

// Função que ajusta o fb após a remoção de um nó 
void ajustaFBRemocao(arvAVL *arv, noAVL *pai, int chaveRemovida);

//Função que corrige o balamenceamento da árvore
void balanceamento(arvAVL *arv, noAVL *noDesbalanceado);

//Função que realiza a rotação à direita no noDesbalanceado
void rotacaoDireita(arvAVL *arv, noAVL *noDesbalanceado);

//Função que realiza a rotação à esquerda no noDesbalanceado
void rotacaoEsquerda(arvAVL *arv, noAVL *noDesbalanceado);

//Percorre a árvore em pré-ordem
//printf("%d (%d) \t", &no->codigo, &no->fb);
void percorrePreOrdem(noAVL *aux);

//Retorna raiz da árvore
noAVL *retornaRaiz(arvAVL *arv);

#endif //AVL_AVL_H