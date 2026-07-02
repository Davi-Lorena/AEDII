//
// Created by Vanessa on 07/05/2025.
//

#ifndef AVL_AVL_H
#define AVL_AVL_H

typedef struct Jogador jogador;
typedef struct AVL arvAVL;

//Função que aloca uma árvore AVL
arvAVL *alocaArvore();

//Função que aloca um jogador novo
jogador *alocaNo(int pontuacao, int id, char nome[]);

//Função que lê os dados do arquivo, aloca um novo nó e chama a inserção
//Retorna 1 se a função não conseguir inserir todos os elementos na árvore
//Retorna 0 se terminou bem
int montaRanking(char *nomeArquivo, arvAVL *arv);

//Função iterativa que insere um novo jogador na árvore e chama a função que ajusta o fb
void insereJogador(arvAVL *arv, jogador *novoJogador);

//Função que remove um nó da árvore AVL
//retorna 1 se o nó foi removido
//retorna 0 se o elemento não foi encontrado na árvore
int removeJogador(arvAVL *arv, int codigo);

//Função que atualiza a pontuação de um jogador
//Para tanto, o jogador deverá ser removido da AVL e, posteriormente, inserido novamente com a nova pontuação
//Retorna 1 se a atualização ocorreu
//Retorna 0 caso contrário
int atualizaPontuacao(arvAVL *arv, int pontuacaoAtual, int novaPontuacao);

//Função que imprime as informações da árvore
//Total jogadores, total rotações simples, total rotações duplas, nessa ordem, uma informação por linha
void estatisticasAVL(arvAVL *arv);

//Percorre a árvore em pré-ordem
//printf("%d %d %s -- %d\n", pontuação, id, nome, fb)
void percorrePreOrdem(jogador *aux);

//Função que imprime na tela os top X jogadores do ranking
//Impressão em ordem decrescente
//o valor de X é informado pelo usuário
//printf("%d\n", pontuação)
void topX(jogador *aux, int *X);

//Função que mostra o ranking todo (ordem decrescente)
//printf("%d %d %s\n", pontuação, id, nome);
void mostraRanking(jogador *aux);

//Retorna raiz da árvore
jogador *retornaRaiz(arvAVL *arv);


//*****FUNÇÕES AVL******///

//Função que ajusta o fb após a inserção e chama o balanceamento, caso necessário
void ajustaFB_insercao(arvAVL *arv, jogador *novoJogador);

//Função que ajusta o fb após a remoção e chama o balanceamento, caso necessário
void ajustaFB_remocao(arvAVL *arv, jogador *pai, int valorRemovido);

//Função que corrige o balamenceamento da árvore
//Cada rotação executada deve atualizar o totalRotações da árvore
void balanceamento(arvAVL *arv, jogador *noDesbalanceado);

void rotacaoDireita(arvAVL *arv, jogador *noDesbalanceado);

void rotacaoEsquerda(arvAVL *arv, jogador *noDesbalanceado);

#endif //AVL_AVL_H
