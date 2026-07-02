#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "lista.h"

struct lista {
no *inicio;
int tam;
};

struct no {
char palavra[30];
no *prox;
};

//Aloca e inicializa uma lista
lista *criaLista() {
lista *list = malloc(sizeof(lista));

if(!list) return NULL;

list->inicio = NULL;
list->tam = 0;

return list; 
}

//Insere uma nova palavra na lista. Ou seja, aloca um nó, inicializa e o insere na lista.
//A insersão é sempre no começo da lista.
//Retorna 1 caso ocorra erro na inserção e 0 caso contrário.
int insereLista(lista *l, char *palavra) {
    no *novo = malloc(sizeof(no));

    if(!novo) return 1;
    
    strcpy(novo->palavra, palavra);

    novo->prox = l->inicio;
    l->inicio = novo; 
    l->tam++;
    
}

//Retorna a lista de uma determinada posição da tabela hash
lista *getLista(lista **vet, int pos) {
    return vet[pos];
}

//Retorna o tamanho de uma determinada lista
int getTamLista(lista *l) {
    return l->tam;
}

//Verifica se uma palavra está presente ou não em uma lista
//Se a palavra estiver presente, retorna 1. Caso contrário, retorna 0;
int buscaLista(lista *l, char *palavra) {
no *aux = l->inicio;

while(aux) {
    if(!strcmp(aux->palavra, palavra)) 
        return 1;
    aux = aux->prox;
}

return 0;
}

//Remove uma palavra da lista
void removeLista(lista *l, char *palavra) {
no *aux = l->inicio, *ant = l->inicio;

while(aux) {
    if(!strcmp(aux->palavra, palavra)) { 
        ant->prox = aux->prox;
        free(aux);
        l->tam--;
        return;
    }
    ant = aux;
    aux = aux->prox;
}
}
//Imprime as palavras de uma lista => printf("%s\n", noAux->palavra);
//Se a lista estiver vazia => printf("Lista Vazia\n");
void imprimeLista(lista *l) {
    no *noAux;
    if(!l->tam) {
        printf("Lista Vazia\n");
        return;
    }

    noAux = l->inicio;

    printf("\n");
    while(noAux) { 
        printf("%s", noAux->palavra);
        if(noAux->prox) printf("\n");
        noAux = noAux->prox; 
       }
}
