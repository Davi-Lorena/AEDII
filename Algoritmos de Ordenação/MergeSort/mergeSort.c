#include <stdio.h>
#include <stdlib.h>

void mergeSort(int *vet, int inicio, int fim) {
    int meio = (inicio + fim) / 2;

    if(inicio < fim) {
        mergeSort(vet, inicio, meio);
        mergeSort(vet, meio+1, fim);
        merge(vet, inicio, meio, fim);
    }
}

void merge(int *V, int inicio, int meio, int fim) {
    int *temp, // Vetor temporário 
    inicioVetor1, // Marca o inicio do subvetor 1  
    inicioVetor2, // Marca o inicio do subvetor 2  
    tamanho, // Tamanho do vetor original 
    // Variáveis de controle 
    i, 
    j, 
    k,
    // Booleanos para o fim do vetor
    fim1 = 0, 
    fim2 = 0;
    // Tamanho dos vetores
    tamanho = fim - inicio + 1;
    inicioVetor1 = inicio;
    inicioVetor2 = meio + 1;
    // Alocação do vetor temporário 
    temp = (int *) malloc(tamanho * sizeof(int));
    
    if(!temp) return;
    
    for (i = 0; i < tamanho; i++) {
        // Se nenhum dos dois vetores tiver chegado ao fim, faça isso 
        if (!fim1 && !fim2) {
             // Combinar ordenando
            if (V[inicioVetor1] < V[inicioVetor2])
                temp[i] = V[inicioVetor1++]; // [x++] -> Adiciona, depois increment, ex: se for 0, coloca o elemento da posição 0 e depois o 0 vira 1;
            else
                temp[i] = V[inicioVetor2++];

                // Vetor acabou?
                if (inicioVetor1 > meio) fim1 = 1;
                if (inicioVetor2 > fim) fim2 = 1;
            } else { // se algum dos vetores chegou ao fim
                // Copia o que sobrar
                if (!fim1)
                    temp[i] = V[inicioVetor1++];
                else
                    temp[i] = V[inicioVetor2++];
            }
    }
        // Copiar do auxiliar para o original
    for (j = 0, k = inicio; j < tamanho; j++, k++) {
        V[k] = temp[j];
    }
    
    free(temp);
}

int main(){
    int v[] = {2,4,5,8,1,5};

    mergeSort(v,0,5);

    printf("VETOR ORDENADO COM O MERGE:\n");

    for(int i = 0 ; i < 6 ; i++){
        printf("%d\n", v[i]);
    }


    return 0;
}