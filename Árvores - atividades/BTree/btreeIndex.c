#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btreeIndex.h"

struct indiceMatricula {
    int matricula;
    long offset;
};

struct no {
    indiceMatricula *chaves;
    struct no **ponteiros;
    struct no *pai;
    int folha;
    int ocupacao;
};

struct btree {
    struct no *raiz;
    int ordem;
};

no *alocaNo(int ordem, int folha) {
    no *novo = (no *)malloc(sizeof(no));
    novo->chaves = (indiceMatricula *)malloc((ordem) * sizeof(indiceMatricula));
    novo->ponteiros = (no **)malloc((ordem + 1) * sizeof(no *));
    novo->pai = NULL;
    novo->folha = folha;
    novo->ocupacao = 0;
    
    for (int i = 0; i <= ordem; i++) {
        novo->ponteiros[i] = NULL;
    }
    return novo;
}

btree *criaArvore(int m) {
    btree *arvore = (btree *)malloc(sizeof(btree));
    arvore->ordem = m;
    arvore->raiz = alocaNo(m, 1);
    return arvore;
}

no *retornaRaiz(btree *arvore) {
    if (arvore) return arvore->raiz;
    return NULL;
}

no *buscaNo(no *atual, indiceMatricula *mat) {
    if (atual->folha) return atual;
    int i = 0;
    while (i < atual->ocupacao && mat->matricula > atual->chaves[i].matricula) {
        i++;
    }
    return buscaNo(atual->ponteiros[i], mat);
}

void insereNo(no *atual, indiceMatricula *mat) {
    int i = atual->ocupacao - 1;
    while (i >= 0 && mat->matricula < atual->chaves[i].matricula) {
        atual->chaves[i + 1] = atual->chaves[i];
        i--;
    }
    atual->chaves[i + 1] = *mat;
    atual->ocupacao++;
}

void split(btree *arvore, no *noDesbal) {
    int ordem = arvore->ordem;
    int meio = (ordem - 1) / 2;
    
    no *novo = alocaNo(ordem, noDesbal->folha);
    novo->pai = noDesbal->pai;
    
    int j = 0;
    for (int i = meio + 1; i < ordem; i++) {
        novo->chaves[j] = noDesbal->chaves[i];
        novo->ocupacao++;
        j++;
    }
    
    if (!noDesbal->folha) {
        j = 0;
        for (int i = meio + 1; i <= ordem; i++) {
            novo->ponteiros[j] = noDesbal->ponteiros[i];
            if (novo->ponteiros[j] != NULL) {
                novo->ponteiros[j]->pai = novo;
            }
            noDesbal->ponteiros[i] = NULL;
            j++;
        }
    }
    
    indiceMatricula promovida = noDesbal->chaves[meio];
    noDesbal->ocupacao = meio;
    
    if (noDesbal->pai == NULL) {
        no *novaRaiz = alocaNo(ordem, 0);
        novaRaiz->chaves[0] = promovida;
        novaRaiz->ponteiros[0] = noDesbal;
        novaRaiz->ponteiros[1] = novo;
        novaRaiz->ocupacao = 1;
        
        noDesbal->pai = novaRaiz;
        novo->pai = novaRaiz;
        arvore->raiz = novaRaiz;
    } else {
        no *pai = noDesbal->pai;
        int pos = pai->ocupacao - 1;
        
        while (pos >= 0 && promovida.matricula < pai->chaves[pos].matricula) {
            pai->chaves[pos + 1] = pai->chaves[pos];
            pai->ponteiros[pos + 2] = pai->ponteiros[pos + 1];
            pos--;
        }
        
        pai->chaves[pos + 1] = promovida;
        pai->ponteiros[pos + 2] = novo;
        pai->ocupacao++;
        
        if (pai->ocupacao == ordem) {
            split(arvore, pai);
        }
    }
}

void insere(btree *arvore, indiceMatricula *mat) {
    if (!arvore || !arvore->raiz) return;
    no *folha = buscaNo(arvore->raiz, mat);
    insereNo(folha, mat);
    if (folha->ocupacao == arvore->ordem) {
        split(arvore, folha);
    }
}

no *buscaElemento(no *atual, int valor) {
    if (!atual) return NULL;
    int i = 0;
    while (i < atual->ocupacao && valor > atual->chaves[i].matricula) {
        i++;
    }
    if (i < atual->ocupacao && valor == atual->chaves[i].matricula) {
        return atual;
    }
    if (atual->folha) {
        return NULL;
    } else {
        return buscaElemento(atual->ponteiros[i], valor);
    }
}

void buscaProduto(char *arquivoDados, int id_aluno) {
    FILE *arq = fopen(arquivoDados, "rb");
    if (!arq) return;
    char linha[512];
    int id, mat, enade;
    int encontrado = 0;
    while (!encontrado && fgets(linha, sizeof(linha), arq)) {
        if (sscanf(linha, "%d %d %d", &id, &mat, &enade) == 3) {
            if (id == id_aluno) {
                printf("%s", linha);
                encontrado = 1;
            }
        }
    }
    if (!encontrado) printf("Elemento não encontrado\n");
    fclose(arq);
}

void buscaMatricula(char *arquivoDados, int mat_aluno) {
    FILE *arq = fopen(arquivoDados, "rb");
    if (!arq) return;
    char linha[512];
    int id, mat, enade;
    int encontrado = 0;
    while (!encontrado && fgets(linha, sizeof(linha), arq)) {
        if (sscanf(linha, "%d %d %d", &id, &mat, &enade) == 3) {
            if (mat == mat_aluno) {
                printf("%s", linha);
                encontrado = 1;
            }
        }
    }
    if (!encontrado) printf("Elemento não encontrado\n");
    fclose(arq);
}

void imprimeArvore(no *atual, int filho) {
    if (!atual) return;
    for (int i = 0; i < atual->ocupacao; i++) printf("%d  ", atual->chaves[i].matricula);
    printf("\n");
    if (!atual->folha) {
        for (int i = 0; i <= atual->ocupacao; i++) imprimeArvore(atual->ponteiros[i], i);
    }
}

btree *create_index(char *arquivoDados, int ordem) {
    FILE *arq = fopen(arquivoDados, "rb");
    if (!arq) return NULL;
    btree *arvore = criaArvore(ordem);
    char linha[512];
    long offset = ftell(arq);
    while (fgets(linha, sizeof(linha), arq) != NULL) {
        int id, mat, enade;
        if (sscanf(linha, "%d %d %d", &id, &mat, &enade) == 3) {
            indiceMatricula im;
            im.matricula = mat;
            im.offset = offset;
            insere(arvore, &im);
        }
        offset = ftell(arq);
    }
    fclose(arq);
    return arvore;
}

void buscar_Aluno(btree *indice, char *arquivoDados, int matricula) {
    no *n = buscaElemento(retornaRaiz(indice), matricula);
    long offset = -1;
    if (n) {
        for (int i = 0; i < n->ocupacao; i++) {
            if (n->chaves[i].matricula == matricula) offset = n->chaves[i].offset;
        }
    }
    if (offset != -1) {
        FILE *arq = fopen(arquivoDados, "rb");
        if (arq) {
            fseek(arq, offset, SEEK_SET);
            char linha[512];
            if (fgets(linha, sizeof(linha), arq)) printf("%s", linha);
            fclose(arq);
        }
    } else {
        printf("Elemento não encontrado\n");
    }
}

void buscar_por_matricula(btree *indice, char *arquivoDados, int matricula) {
    buscar_Aluno(indice, arquivoDados, matricula);
}