#include <stdio.h>
#include "RB.h"

int main() {
    //DECLARAÇÃO DE VARIÁVEIS
    FILE *arq;
    int valor, opcao;
    char nomeArquivo1[30];
    char nomeArquivo2[30];
    rb *T1 = alocaArvore();
    rb *T2 = alocaArvore();
    rb *T3 = NULL;
    noRB *novoNo;


    scanf("%s", nomeArquivo1);
    scanf("%s", nomeArquivo2);


    //**CARGA DA ÁRVORE 1**//
    arq = fopen(nomeArquivo1, "r");
    if (!arq)
        return 1;

    while(!feof(arq))
    {
        fscanf(arq, "%d", &valor);
        novoNo = alocaNo(T1, valor);
        insereNo(T1, novoNo);
    }
    atualiza_Altura_Preto(T1, retornaRaiz(T1));
    atualiza_Altura_Preto_RB(T1);
    percorrePreOrdem(T1, retornaRaiz(T1));
    printf("\n\n");
    fclose(arq);

    //**CARGA DA ÁRVORE 2**//
    arq = fopen(nomeArquivo2, "r");
    if (!arq)
        return 1;

    while(!feof(arq))
    {
        fscanf(arq, "%d", &valor);
        novoNo = alocaNo(T2, valor);
        insereNo(T2, novoNo);
    }
    atualiza_Altura_Preto(T2, retornaRaiz(T2));
    atualiza_Altura_Preto_RB(T2);
    percorrePreOrdem(T2, retornaRaiz(T2));
    printf("\n\n");
    fclose(arq);

    //**MENU DE OPÇÕES**//

    scanf("%d", &opcao);
    while (opcao >=1 && opcao <=4 )
    {
        switch (opcao) {
            case 1: //insere um novo nó em T1
                scanf("%d", &valor);
                novoNo = alocaNo(T1, valor);
                if(!novoNo)
                    return 1;
                insereNo(T1, novoNo);
                break;
            case 2: //remove um novo nó em T1
                scanf("%d", &valor);
                valor = removeNo(T1, valor);
                break;
            case 3: //impressao
                scanf("%d", &valor); //lê qual árvore vai imprimir
                if (valor == 1)
                    percorrePreOrdem(T1, retornaRaiz(T1));
                else
                {
                    if (valor == 2)
                        percorrePreOrdem(T2, retornaRaiz(T2));
                    else
                    {
                        if (T3 != NULL)
                            percorrePreOrdem(T3, retornaRaiz(T3));
                    }
                }
                printf("\n\n");
                break;
            case 4: //juncao
                scanf("%d", &valor);
                T3 = rb_join(T1, T2, valor);
                break;
        }
        scanf("%d", &opcao);
    }

    return 0;
}
