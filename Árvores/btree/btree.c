#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

struct no
{
    int *chaves;
    no **ponteiros;
    no *pai;
    int folha; //1 é folha. 0 é não folha
    int ocupacao;
};

struct btree{
    no *raiz;
    int ordem;
};

no *alocaNo(int ordem,  int folha)
{
    no *novoNo;
    novoNo = (no*) malloc(sizeof (no));
    if(!novoNo)
    {
        printf("Erro ao alocar um novo nó para a arvore");
        exit(1);
    }
    novoNo->chaves = (int*) malloc(ordem * sizeof(int));
    novoNo->ponteiros = (no**) malloc((ordem+1) * sizeof(no*));
    for (int i=0; i<=ordem; i++)
    {
        novoNo->ponteiros[i] = NULL;
    }
    novoNo->folha = folha;
    novoNo->ocupacao = 0;
    novoNo->pai = NULL;
    return novoNo;
}

btree *criaArvore(int m)
{

    btree *novaArvore = (btree*) malloc(sizeof (btree));
    if (!novaArvore)
    {
        printf("Erro ao alocar arvore");
        exit(1);
    }

    no *raiz = alocaNo(m, 1);
    novaArvore->raiz = raiz;
    novaArvore->ordem = m;

    return novaArvore;
}

no *retornaRaiz(btree *arvore)
{
    return arvore->raiz;
}

no *buscaElemento(no *atual, int valor)
{
    int i = 0;
    int pos  = -1;

    if (atual == NULL)
        return NULL;

    while ((i<atual->ocupacao) && (pos == -1))
    {
        if(valor == atual->chaves[i])
            return atual;
        if(valor < atual->chaves[i])
            pos = i;
        else
            i++;
    }
    return buscaElemento(atual->ponteiros[i], valor);
}

no *buscaNo(no *atual, int valor)
{
    int i = 0;
    int pos  = -1;

    if (atual->folha == 1)
        return atual;

    while ((i<atual->ocupacao) && (pos == -1))
    {
        if(valor < atual->chaves[i])
            pos = i;
        else
            i++;
    }
    return buscaNo(atual->ponteiros[i], valor);
}

int insereElemento(btree *arvore, int valor)
{
    int ocuMax = arvore->ordem;

    no *aux = arvore->raiz;
    if (!aux)
        return -1;

    aux = buscaNo(aux, valor); //encontra a folha correta para inserção

    //ALGORITMO DE INSERÇÃO
    //INSERE NA FOLHA
    if (aux->ocupacao < ocuMax) //existe espaço na folha
    {
        int pos = aux->ocupacao; // começa no final
        while (pos != 0 && aux->chaves[pos-1] > valor)
        {
            aux->chaves[pos] = aux->chaves[pos-1];
            pos--;
        }
        aux->chaves[pos] = valor;
        aux->ocupacao++;
    }

    //VERIFICA SE ULTRAPASSOU O LIMITE MAXIMO
    if (aux->ocupacao > arvore->ordem - 1)
        split(arvore, aux);
    return 1;
}

void split(btree *arvore, no *noAtual)
{
    //VERIFICA SE O NO ATUAL É RAIZ
    no *novaRaiz = NULL;
    if (noAtual == arvore->raiz)
    {
        novaRaiz = alocaNo(arvore->ordem, 0); //Note o parâmetro 0 no final. Ele indica que essa novaRaiz não é uma folha (já que ela terá filhos abaixo dela)
        if (!novaRaiz)
            return;
        arvore->raiz = novaRaiz;
    }

    //ALOCA O NÓ IRMÃO
    no *irmao = alocaNo(arvore->ordem, noAtual->folha);
    if (!irmao)
        return;

    //ASSOCIA O PAI DO IRMÃO AO PAI DO NÓ ATUAL
    if (noAtual->pai == NULL)
    {
        noAtual->pai = novaRaiz;
        novaRaiz->ponteiros[0] = noAtual;
        novaRaiz->ponteiros[1] = irmao;
    }
    irmao->pai = noAtual->pai;

    //COPIA A METADE PARA O IRMÃO
    int meio = (int)(arvore->ordem-1)/2;
    int ocupacaoOriginal = noAtual->ocupacao; // FIX: guarda o limite ANTES do loop mexer em noAtual->ocupacao
    int i = 0;
    for (int j = meio + 1; j < ocupacaoOriginal; j++) // FIX: usa o limite fixo, não a ocupação sendo decrementada (esse era o bug que só "dava certo" por acaso pra ordens pequenas)
    {
        irmao->chaves[i] = noAtual->chaves[j];
        irmao->ponteiros[i] = noAtual->ponteiros[j];
        irmao->ocupacao++;
        noAtual->ocupacao--;
        i++;
    }
    // copia o último ponteiro filho (o que fica após a última chave migrada)
    irmao->ponteiros[i] = noAtual->ponteiros[ocupacaoOriginal]; // FIX: usa o limite fixo

    // atualiza o ponteiro pai dos filhos que foram migrados para o irmão
    for (int k = 0; k <= irmao->ocupacao; k++)
        if (irmao->ponteiros[k])
            irmao->ponteiros[k]->pai = irmao;

    //INSERE O MEIO NO PAI
    no *pai = noAtual->pai;
    int pos = pai->ocupacao;
    while (pos != 0 && pai->chaves[pos-1] > noAtual->chaves[meio])
    {
        pai->chaves[pos] = pai->chaves[pos-1];
        pai->ponteiros[pos+1] = pai->ponteiros[pos];
        pos--;
    }
    pai->chaves[pos] = noAtual->chaves[meio];
    pai->ponteiros[pos+1] = irmao;
    pai->ocupacao++;

    noAtual->ocupacao = meio; // FIX: sobram só as chaves [0 .. meio-1]; atribuição direta em vez de decremento manual dentro do loop

    //VERIFICA SE O PAI ESTOUROU
    if (pai->ocupacao > arvore->ordem - 1)
        split(arvore, pai);
}

void populaBTree(char *nomeArquivo, btree *arvore)
{
    FILE *arq;
    int elemento, status;

    arq = fopen(nomeArquivo, "r");
    if (!arq)
    {
        printf("Erro ao abrir o arquivo\n");
        exit(-1);
    }

    while (fscanf(arq, "%d", &elemento) == 1) // FIX: testa o retorno do fscanf em vez de feof(), evita reinserir o último valor duplicado
    {
        status = insereElemento(arvore, elemento);
        if (status == -1)
        {
            printf("Erro ao inserir\n");
            exit(-1);
        }
    }
    fclose(arq);
}

void imprimeArvore(no *atual, int filho)
{
    //imprime o nó
    for (int i=0; i<atual->ocupacao; i++)
        printf("%d  ", atual->chaves[i]);
    printf("\n");

    while((atual->folha == 0) && (filho <= atual->ocupacao))
    {
        imprimeArvore(atual->ponteiros[filho], 0);
        filho++;
    }
}

void rotacao(no *noDesbal, no *irmao, int posPai)
{
    no *pai = noDesbal->pai;

    // FIX: descobre se 'irmao' é de fato o ponteiro à esquerda de noDesbal,
    // em vez de assumir isso só pelo sinal de posPai. Antes, quando o irmão
    // era da direita e noDesbal não estava na posição 0 do pai, a chave
    // separadora errada (pai->chaves[0]) era lida/sobrescrita.
    int irmaoEsquerda = (posPai > 0 && pai->ponteiros[posPai - 1] == irmao);
    int posSeparador = irmaoEsquerda ? (posPai - 1) : posPai;

    if (irmaoEsquerda)
    {
        // Abre espaço no início de noDesbal
        for (int i = noDesbal->ocupacao; i > 0; i--)
        {
            noDesbal->chaves[i] = noDesbal->chaves[i-1];
            noDesbal->ponteiros[i+1] = noDesbal->ponteiros[i];
        }
        noDesbal->ponteiros[1] = noDesbal->ponteiros[0];

        // Desce a chave separadora do pai para o início de noDesbal
        noDesbal->chaves[0] = pai->chaves[posSeparador];
        noDesbal->ocupacao++;

        // Adota o filho mais à direita do irmão como filho mais à esquerda de noDesbal
        noDesbal->ponteiros[0] = irmao->ponteiros[irmao->ocupacao];
        if (noDesbal->ponteiros[0])
            noDesbal->ponteiros[0]->pai = noDesbal;

        // Sobe a maior chave do irmão para o pai
        pai->chaves[posSeparador] = irmao->chaves[irmao->ocupacao - 1];
        irmao->ocupacao--;
    }
    else // Rotação com irmão da DIREITA
    {
        // Desce a chave separadora do pai para o fim de noDesbal
        noDesbal->chaves[noDesbal->ocupacao] = pai->chaves[posSeparador];
        noDesbal->ponteiros[noDesbal->ocupacao + 1] = irmao->ponteiros[0];
        if (noDesbal->ponteiros[noDesbal->ocupacao + 1])
            noDesbal->ponteiros[noDesbal->ocupacao + 1]->pai = noDesbal;
        noDesbal->ocupacao++;

        // Sobe a menor chave do irmão para o pai
        pai->chaves[posSeparador] = irmao->chaves[0];

        // Remove a primeira chave do irmão e ajusta seus ponteiros
        for (int i = 0; i < irmao->ocupacao - 1; i++)
        {
            irmao->chaves[i] = irmao->chaves[i+1];
            irmao->ponteiros[i] = irmao->ponteiros[i+1];
        }
        irmao->ponteiros[irmao->ocupacao - 1] = irmao->ponteiros[irmao->ocupacao];
        irmao->ocupacao--;
    }
}

no *merge(no *noDesbal, int posPai)
{
    no *pai = noDesbal->pai;

    no *esq, *dir;
    int posChavePai; // posição da chave separadora no pai

    if (posPai > 0) // merge com irmão da ESQUERDA
    {
        esq = pai->ponteiros[posPai - 1];
        dir = noDesbal;
        posChavePai = posPai - 1;
    }
    else // merge com irmão da DIREITA
    {
        esq = noDesbal;
        dir = pai->ponteiros[posPai + 1];
        posChavePai = posPai;
    }

    // Desce a chave separadora do pai para o nó esquerdo
    esq->chaves[esq->ocupacao] = pai->chaves[posChavePai];
    esq->ponteiros[esq->ocupacao + 1] = dir->ponteiros[0];
    if (esq->ponteiros[esq->ocupacao + 1])
        esq->ponteiros[esq->ocupacao + 1]->pai = esq;
    esq->ocupacao++;

    // Copia todas as chaves e ponteiros do nó direito para o esquerdo
    for (int i = 0; i < dir->ocupacao; i++)
    {
        esq->chaves[esq->ocupacao] = dir->chaves[i];
        esq->ponteiros[esq->ocupacao + 1] = dir->ponteiros[i + 1];
        if (esq->ponteiros[esq->ocupacao + 1])
            esq->ponteiros[esq->ocupacao + 1]->pai = esq;
        esq->ocupacao++;
    }

    // Remove a chave separadora do pai e ajusta seus ponteiros
    for (int i = posChavePai; i < pai->ocupacao - 1; i++)
    {
        pai->chaves[i] = pai->chaves[i+1];
        pai->ponteiros[i+1] = pai->ponteiros[i+2];
    }
    pai->ocupacao--;

    free(dir->chaves);
    free(dir->ponteiros);
    free(dir);

    return esq;
}

int removeElemento(btree *arvore, int valor)
{
    int minOcupacao = (arvore->ordem + 1) / 2 - 1; // FIX: ceil(m/2) - 1, fórmula correta pra m par e ímpar (antes era ordem/2, que só batia certo pra m ímpar)

    // Busca o nó que contém o valor
    no *noAtual = buscaElemento(arvore->raiz, valor);
    if (!noAtual)
        return -1;

    // Encontra a posição da chave no nó
    int posChave = 0;
    while (posChave < noAtual->ocupacao && noAtual->chaves[posChave] != valor)
        posChave++;

    // REMOÇÃO POR CÓPIA: se não for folha, substitui pelo predecessor
    if (noAtual->folha == 0)
    {
        // Desce pelo filho à esquerda da chave e vai sempre para o filho mais à direita
        no *pred = noAtual->ponteiros[posChave];
        while (pred->folha == 0)
            pred = pred->ponteiros[pred->ocupacao];

        int chavePredecessora = pred->chaves[pred->ocupacao - 1];

        // Substitui a chave pelo predecessor e remove o predecessor da folha
        noAtual->chaves[posChave] = chavePredecessora;
        noAtual = pred;
        posChave = noAtual->ocupacao - 1;
    }

    // Remove a chave da folha
    for (int i = posChave; i < noAtual->ocupacao - 1; i++)
        noAtual->chaves[i] = noAtual->chaves[i+1];
    noAtual->ocupacao--;

    // REBALANCEAMENTO: sobe pela árvore enquanto necessário
    no *noRebalanceado = noAtual;
    int rebalanceamentoConcluido = 0;

    while (noRebalanceado != arvore->raiz && noRebalanceado->ocupacao < minOcupacao && !rebalanceamentoConcluido)
    {
        no *pai = noRebalanceado->pai;

        // Descobre a posição do ponteiro do pai que aponta para o noRebalanceado
        int posicaoNoPai = 0;
        while (posicaoNoPai <= pai->ocupacao && pai->ponteiros[posicaoNoPai] != noRebalanceado)
            posicaoNoPai++;

        // Tenta irmão da esquerda primeiro
        if (posicaoNoPai > 0 && pai->ponteiros[posicaoNoPai-1]->ocupacao > minOcupacao)
        {
            rotacao(noRebalanceado, pai->ponteiros[posicaoNoPai-1], posicaoNoPai);
            rebalanceamentoConcluido = 1;
        }
        // Depois tenta irmão da direita
        else if (posicaoNoPai < pai->ocupacao && pai->ponteiros[posicaoNoPai+1]->ocupacao > minOcupacao)
        {
            // FIX: antes passava 0 fixo aqui; agora passa a posição real de noRebalanceado no pai,
            // que é o que rotacao() precisa pra calcular o separador certo quando posicaoNoPai > 0
            rotacao(noRebalanceado, pai->ponteiros[posicaoNoPai+1], posicaoNoPai);
            rebalanceamentoConcluido = 1;
        }
        else // Merge: tenta esquerda primeiro, senão direita
        {
            int indiceMerge;
            if (posicaoNoPai > 0) {
                indiceMerge = posicaoNoPai;
            } else {
                indiceMerge = 0;
            }

            noRebalanceado = merge(noRebalanceado, indiceMerge);
            noRebalanceado = noRebalanceado->pai;
        }
    }

    // Se a raiz ficou vazia após um merge, a árvore fica um nível menor
    if (arvore->raiz->ocupacao == 0 && arvore->raiz->ponteiros[0] != NULL)
    {
        no *velhaRaiz = arvore->raiz;
        arvore->raiz = velhaRaiz->ponteiros[0];
        arvore->raiz->pai = NULL;
        free(velhaRaiz->chaves);
        free(velhaRaiz->ponteiros);
        free(velhaRaiz);
    }

    return 1;
}

void manipulaBTree(btree *arvore, char *nomeArquivo, char status)
{
    FILE *arq;
    int elemento, resultado;

    arq = fopen(nomeArquivo, "r");
    if (!arq)
    {
        printf("Erro ao abrir o arquivo\n");
        exit(-1);
    }

    while (!feof(arq))
    {
        if (fscanf(arq, "%d", &elemento) != 1)
            break;

        if (status == 'i')
        {
            resultado = insereElemento(arvore, elemento);
            if (resultado == -1)
            {
                printf("Erro ao inserir %d\n", elemento);
                exit(-1);
            }
        }
        else if (status == 'r')
        {
            resultado = removeElemento(arvore, elemento);
            if (resultado == -1)
                printf("Elemento %d não encontrado para remoção\n", elemento);
        }
    }

    fclose(arq);
}