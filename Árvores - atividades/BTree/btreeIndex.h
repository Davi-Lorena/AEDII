//
// Created by Vanessa on 25/06/2026.
//

#ifndef BTREE_INDEX_BTREEINDEX_H
#define BTREE_INDEX_BTREEINDEX_H

typedef struct no no;

/*struct no
{
    indiceMatricula *chaves;
    no **ponteiros;
    no *pai;
    int folha; //1 é folha. 0 é não folha
    int ocupacao;
};*/

typedef struct indiceMatricula indiceMatricula;

/*struct indiceMatricula
{
    int matricula;
    long offset;
};*/

typedef struct btree btree;

/*struct btree{
    no *raiz;
    int ordem;
};*/

/****FUNÇÕES DE ALOCAÇÃO******/

//Função que aloca e inicializa um novo nó
//Se o nó for folha, a variável folha é 1. Caso contrário é 0
no *alocaNo(int ordem, int folha);

//Função que aloca e inicializa uma nova árvore com uma raiz alocada, porém vazia.
//Árvore B tradicional. Caso contrário, retorna NULL.
btree *criaArvore(int m);

//Função que retorna a raiz da árvore
no *retornaRaiz(btree *arvore);

/****FUNÇÕES DE INSERÇÃO******/

//Função que insere um novo elemento na árvore usando o algoritmo que insere primeiro, depois splita
//Armazena um espaço extra para inserção
int insereDado(btree *arvore, indiceMatricula *novaMatricula);

//Função que realiza o split no noDesbal.
//Função chamada pela função insereElemento
//Sempre sobe o elemento do meio para o pai (meio = ordem / 2).
//Após o split verifica se encheu o pai. Se sim, a função se chama recursivamente.
void split(btree *arvore, no *noDesbal);

//Função recursiva que retorna a folha correta para inserir produto
no *buscaNo(no *atual, indiceMatricula *mat);

/****FUNÇÕES DE BUSCA E IMPRESSÃO*****/

//Função recursiva que retorna o nó onde o elemento está na árvore
no *buscaElemento(no *atual, int valor);

//Função que busca pelo id do aluno direto no arquivo de dados
void buscaProduto(char *arquivoDados, int id_aluno);

//Função que busca pela matrícula do aluno direto no arquivo de dados
void buscaMatricula(char *arquivoDados, int mat_aluno);

//Função recursiva que imprime a árvore por profundidade
//Raiz, filho da esquerda até chegar na folha. E sobe imprimindo os filhos em sequência
//Imprime matricula
void imprimeArvore(no *atual, int filho);

/****FUNÇÕES DE INDEXAÇÃO*****/

//Função que cria o índice sobre o atributo matricula do aluno
//fscanf(arq, "%d\t%d\t%d\n", &id, &mat, &enade); -- não é obrigado usar fscanf. Apenas para quem quiser usar
//Estudar a função ftell
btree *create_index(char *arquivoDados, int ordem);

//Função que busca pela matrícula do aluno no arquivo de dados utilizando o índice
//Ao encontrar a posição do aluno no arquivo, a função imprime os dados na tela
//Se não encontrar, a função deve imprimir printf("Elemento não encontrado\n");
//Estudar a função fseek
void buscar_Aluno(btree *indice, char *arquivoDados, int mat_aluno);





#endif //BTREE_INDEX_BTREEINDEX_H
