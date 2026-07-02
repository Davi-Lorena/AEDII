#include <stdio.h>
#include <stdlib.h>
#include "contratos.h"

struct fornecedor{
    int num;
    int dia_ini_fornecimento;
    int preco;
};
struct cliente {
    int dia_fim_tiberium;
    int receita;
    scli *prox;
};

struct lista {
    scli *com;
};

tlista *cria_lista () {
    tlista *l = malloc(sizeof(tlista));
    
    if (l) 
        l->com = NULL; 

    return l; 
}

int insere_cliente (tlista *l, int dia_fim, int rec) {
    scli *novo, *aux, *ant = NULL;

    novo = malloc(sizeof(scli));

    if (!novo) return 0;

    novo->dia_fim_tiberium = dia_fim;
    novo->receita = rec;
    novo->prox = NULL;

    if (l->com == NULL) {
        l->com = novo;
        return 1;
    }

    aux = l->com;
    while (aux && aux->dia_fim_tiberium < dia_fim) {
        ant = aux;
        aux = aux->prox;
    }
        novo->prox = aux; 
        if (!ant) 
        l->com = novo;
    else
        ant->prox = novo; 

    return 1;
}

sfor *alocaVetor(int tam) {
    sfor *f = malloc(sizeof(sfor) * tam);
    return f;
}

void preencheFornecedores(sfor *f, int tam) {
    for(int i = 0; i < tam; i++) {
        scanf("%d %d", &f[i].dia_ini_fornecimento, &f[i].preco );
        f[i].num = i;
    }
}

void calcula_s (sfor *fornecedor, int id, tlista *l) {
    int end = id-1;
    int calculo, lucro_maximo = 0;

    scli *aux = l->com;

    while(aux) {
        if (fornecedor[end].dia_ini_fornecimento < aux->receita) {
            calculo = (aux->receita - fornecedor[end].preco) * (aux->dia_fim_tiberium - fornecedor[end].dia_ini_fornecimento + 1);
            if (calculo > lucro_maximo)
                lucro_maximo = calculo;
        }
        aux = aux->prox;
    }
    printf("%d\n", lucro_maximo);
}

void preencheOperações (tlista *l, sfor *fornecedor, int tam) {
    char operacao;
    int e, r, id;

    for(int i = 0; i < tam; i++) {
        scanf(" %c", &operacao);
        if (operacao == 'c') {
            scanf("%d %d", &e, &r);
            insere_cliente(l,e,r); 
        }
        else if (operacao == 's') {
            scanf("%d", &id);
            calcula_s(fornecedor, id, l);
        }
        else printf("Operação inexistente.\n");
    }
}

