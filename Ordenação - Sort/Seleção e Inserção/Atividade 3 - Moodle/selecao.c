#include <stdio.h>
#include <stdlib.h>
#include "selecao.h"


//Esta função gera 'qtd' números aleatórios e os escreve no arquivo 'nomeArquivo'
//Os numeros devem variar entre 0 e 1000 e devem ser inicializados com a semente
//A função retorna 0 se funcionou corretamente. Retorna 1 se houve algum erro no processo.
//Pesquisem pelas funções rand() e srand().
int geraAleatorios(char *nomeArquivo, int qtd, int semente) {
    FILE *arq = fopen(nomeArquivo, "w");
    
    if(!arq) return 1;

    srand(semente);

    for(int i = 0; i < qtd; i++) {
        fprintf(arq, "%d ", rand() % 1000);
    }

    fclose(arq);
    return 0;
}

//Esta função lê 'qtd' dados do arquivo 'nomeArquivo' e os insere em um vetor de inteiros
//A função retorna NULL caso haja algum erro no processo.
int* leArquivo(char *nomeArquivo, int qtd) {
    FILE *arq = fopen(nomeArquivo, "r");
    
    if(!arq){
        fclose(arq);    
        return NULL;
    }

    int *vet = malloc(sizeof(int) * qtd);

    if(!vet) {
        fclose(arq);    
        return NULL;
    }

    while(!feof(arq))
        for(int i = 0; i < qtd; i++) 
            fscanf(arq, "%d", &vet[i]);


    fclose(arq);
    return vet;
}

//Esta função recebe um vetor de inteiros de tamanho 'tam' e o ordena (ordem crescente) utilizando o método seleção
void selecao(int *vet, int tam) {
    for (int i = 0; i < tam - 1; i++) {
        int min = i;
        for (int j = i + 1; j < tam; j++) {
            if (vet[j] < vet[min]) {
                min = j;
            }
        }
        int aux = vet[i];
        vet[i] = vet[min];
        vet[min] = aux;
    }
}
//Esta função recebe um vetor de inteiros de tamanho 'tam' e o ordena utilizando o método insercao
void insercao(int *vet, int tam) {
    int marcador, pos, aux;

    for(marcador = 1; marcador < tam; marcador++) {
        pos = marcador - 1;
        aux = vet[marcador];

        while(pos >= 0 && aux < vet[pos]) {
            vet[pos + 1] = vet[pos];
            pos--;
        }
        vet[pos + 1] = aux;
    }
}


//Esta função implementa a busca binária e sua saída é salva no vetor res
//res[0] recebe 1 se encontrou o elemento buscado e 0 caso contrário
//res[1] informa quantas vezes a função buscaBinaria foi chamada, uma vez que ela é recursiva
//ou seja, sempre que a função é chamada res[1] é incrementado
void buscaBinaria(int *vet, int inicio, int fim, int valor, int *res) {
    res[1]++;

    if(inicio > fim) {
        res[0] = 0;
        return; 
    }

    int meio = (inicio + fim) / 2;

    if(vet[meio] == valor) {
        res[0] = 1;
        return;
    } 

    if(vet[meio] > valor) 
            buscaBinaria(vet, inicio, meio - 1, valor, res);
    else buscaBinaria(vet, meio + 1, fim, valor, res);

}

//Esta função recebe um vetor e o imprime na tela
//A impressão é em linha -> printf("%d ", ...);
//Antes de encerrar, a função imprime uma linha em branco
void imprimeVet(int *vet, int tam) {
for(int i = 0; i < tam; i++)
    printf("%d ", vet[i]);

    printf("\n");
}