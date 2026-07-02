#include <stdio.h>
#include <stdlib.h>
#include "bolha.h"
#include <stdbool.h>

struct tReturn {
    int *vet, tam, erro;
};

tReturn* alocatReturn() {
    tReturn *r = malloc(sizeof(tReturn));
    return r;
}

int *getVet(tReturn *rep) {
    return rep->vet;
}

int getTam(tReturn *rep) {
    return rep->tam;
}

int getErro(tReturn *rep) {
    return rep->erro;
}

void trataErro(int erro) {
    if (erro == 1)
        printf("Erro ao abrir o arquivo\n");  
    else if (erro == 2)
        printf("Erro ao ler do arquivo\n");
    else if (erro == 3)
        printf("Erro ao alocar memória\n");
}

tReturn* leArquivo(char nomeArquivo[]) {
    tReturn *r = alocatReturn();
    int tam, *vetor;
    FILE *arq;

    arq = fopen(nomeArquivo, "r");
    if (!arq) {
        r->erro = 1;
        return r;
    }

    fscanf(arq, "%d", &tam);
    vetor = malloc(sizeof(int) * tam);
    if (!vetor) {
        r->erro = 3;
        fclose(arq);
        return r;
    }

    for (int i = 0; i < tam; i++) {
        if (fscanf(arq, "%d", &vetor[i]) != 1) {
            r->erro = 2;
            free(vetor);
            fclose(arq);
            return r;
        }
    }
 
    r->tam = tam;
    r->vet = vetor;
    r->erro = 0;
    fclose(arq);
    return r;
}

int bolha (int *vet, int tam) {
    int comp = 0, aux;
    
    for (int i = 0; i < tam; i++) {
        for (int j = 1; j < tam; j++) {
            comp++;
            if (vet[j] < vet[j-1]) {
                aux = vet[j-1];
                vet[j-1] = vet[j];
                vet[j] = aux;
            }
        }
    }
    return comp;
}

int bolhaInteligente (int *vet, int tam) {
    int cont = 0, aux;
    bool houve_troca;

    for (int i = 0; i < tam; i++) {
        houve_troca = false;
        for (int j = 1; j < tam-i; j++) {
            cont++;
            if (vet[j] < vet[j-1]) {
                aux = vet[j-1];
                vet[j-1] = vet[j];
                vet[j] = aux;
                houve_troca = true;
            }
        }
        if (!houve_troca)
            break;
    }
    return cont;
}

void imprimeVet(int *vet, int tam) {
    for (int i = 0; i < tam; i++) 
        printf("%d\n", vet[i]);
}

