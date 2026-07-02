#include <stdio.h>
#include "AVL.h"

int main() {
    arvAVL *avl;
    int status;
    int opc;
    int pontuacao, id, novaPontuacao;
    char nome[30];
    char nomeArquivo[30];

    avl = alocaArvore();
    if (!avl)
        return 1;

    scanf("%s", &nomeArquivo);
    status = montaRanking(nomeArquivo, avl);
    if (status == 1)
        return 1;

    scanf("%d", &opc);
    while (opc > 0 && opc < 8)
    {
        switch (opc)
        {
            case 1:
                percorrePreOrdem(retornaRaiz(avl));
                break;
            case 2:
                scanf("%d", &pontuacao);
                scanf("%d", &id);
                scanf("%s", &nome);
                jogador *novo = alocaNo(pontuacao, id, nome);
                if (!novo)
                    printf("Erro ao alocar o nó");
                else
                    insereJogador(avl, novo);
                break;
            case 3:
                scanf("%d", &pontuacao);
                removeJogador(avl, pontuacao);
                break;
            case 4:
                estatisticasAVL(avl);
                break;
            case 5:
                scanf("%d", &pontuacao);
                scanf("%d", &novaPontuacao);
                atualizaPontuacao(avl, pontuacao, novaPontuacao);
                break;
            case 6:
                scanf("%d", &pontuacao);
                topX(retornaRaiz(avl), &pontuacao);
                break;
            case 7:
                mostraRanking(retornaRaiz(avl));
                break;
            default:
                break;
        }
        scanf("%d", &opc);
    }


    return 0;
}
