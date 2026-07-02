#include "stdio.h"
#include "ES.h"

int main()
{
    //DECLARAÇÃO DE VARIÁVEIS
    int *vet;
    int tam;
    int min;
    int max;
    int semente;

    scanf("%d",&tam);
    scanf("%d",&min);
    scanf("%d",&max);
    scanf("%d",&semente);

    //GERA O VETOR DE NÚMEROS ALEATÓRIOS
    vet = geraVetorAleatorio(tam, min, max, semente);

    //IMPRIME O VETOR
    imprimeVetor(vet, tam);

    return 0;
}







