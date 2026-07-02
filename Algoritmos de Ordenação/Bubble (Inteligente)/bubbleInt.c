#include <stdio.h>
#include <stdlib.h>

/* 

As melhorias e principais diferenças do bolha inteligente para o bolha commum são: 

1 - O Bolha inteligente tem uma flag para identificar se o vetor já está ordenado. 
Se nenhuma troca for feita, ele para de executar e economiza quantidades absurdas de execução.

2 - O Bolha garante que as últimas posições do vetor estejam alinhadas e o bolha inteligente as ignora nas demais passagens. 

*/

int *bubbleInteligente(int *vet, int tam) {
int i, j, aux, flag;

for(i = 0; i < tam; i++){
    flag = 0;
    for(j = 1; j < tam-i; j++){
        if(vet[j] < vet[j - 1]) {
            aux = vet[j];
            vet[j] = vet[j - 1];
            vet[j - 1] = aux;
             flag = 1;
        }
    }

    if(!flag) 
        break;
}

    return vet;
}