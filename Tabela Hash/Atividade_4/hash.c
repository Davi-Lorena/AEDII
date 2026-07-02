#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "lista.h"

typedef struct hash {
lista **tabela;
int tam;
} hash;

//Aloca e inicializa uma tabela hash de tamanho "tam";
hash *criaHash(int tam) {
hash *table = malloc(sizeof(hash));

if(!table) return NULL;

table->tam = tam;

table->tabela = malloc(sizeof(lista*) * tam);
if(!table->tabela) return NULL;

for(int i = 0; i < tam; i++) { 
    table->tabela[i] = criaLista();
    if(!table->tabela[i]) return NULL;
}

return table;
}

//Retorna a posição da palavra na tabela hash de tamanho "tamHash"
//O cálculo está na descrição da atividade
int funcaoHash(char *palavra, int tamHash) {
    int soma = 0, i;
  
    for(i = 0; palavra[i] != '\0'; i++) 
        soma += palavra[i];
    
    return soma % tamHash;
}

//Insere uma nova palavra na hash utilizando a função insereLista da TAD lista.
void insere(hash *h, char *palavra) {
    int pos = funcaoHash(palavra, h->tam);

    insereLista(h->tabela[pos], palavra);    
}

//Verifica a presença de uma palavra na tabela hash utilizando a função buscaLista da TAD lista
//Se o elemento estiver presente, retorna a posição dele na Hash. Caso contrário, retorna -1.
int encontraElemento(hash *h, char *palavra) {
    int pos = funcaoHash(palavra, h->tam);

    if(buscaLista(h->tabela[pos], palavra)) {
        return pos;
    }

    return -1;
}

//Imprime a lista de uma posição da hash utilizando a função imprimeLista da TAD lista
void percorre(hash *h, int pos) {
    imprimeLista(h->tabela[pos]);
}

//Retorna o tamanho de uma lista da hash utilizando a função getTamLista da TAD lista.
int getTamanhoLista(hash *h, int pos) {
    return getTamLista(h->tabela[pos]);
}

//Remove uma palavra da hash utilizando as funções encontraElemento e removeLista da TAD lista.
//Se o elemento existia na hash e foi removido, retorna 0. Caso contrário, retorna -1.
int removeElemento(hash *h, char *palavra) {
    int posElemento = encontraElemento(h, palavra);

    if(posElemento == -1) return -1;

    removeLista(h->tabela[posElemento], palavra);
}
