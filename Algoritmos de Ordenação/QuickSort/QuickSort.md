# QuickSort 

- Dividir para conquistar: divide o problema em subproblemas menores e os soluciona até chegar na ordenação total 

- Seleciona um PIVÔ (posição inicial do vetor, no nosso caso) e divide o vetor em duas partes: 
    - Os elementos menores que o PIVÔ (desordenados)
    - Os elementos maiores que o PIVÔ (desordenados)
- Ao final de cada passada, o pivô estará ordenado

- Métodos: 
    - QuickSort: Define um Pivô e faz as chamadas recursivas 
    - Particiona: Encontra a posição do pivô e a retorna para o pivô da função quicksort

- Complexidade: O(nlongn) para os demais casos e O(n^2) para o PIOR CASO (Vetor ordenado) 
    - Em seu pior caso, esse quicksort é o PIOR algoritmo de ordenação no quesito tempo

- Alternativas mais eficientes: 
    - Para "melhorar" o pior caso desse algoritmo, algumas estratégias são utilizar pivos em medianas de três ou aleatórios. 

---

## 2. Quick Sort (Ordenação Rápida)

O Quick Sort foca no **Particionamento**. Ele coloca um elemento (Pivô) no lugar certo e garante que menores fiquem à esquerda e maiores à direita.

### 🧠 A Lógica (First Steps)
1. Escolha um **Pivô** (ex: o primeiro elemento).
2. Varra o vetor: sempre que encontrar alguém menor que o pivô, jogue-o para o início.
3. No fim, coloque o pivô logo após o último elemento menor encontrado.

### 💻 Implementação Corrigida

```c
void quickSort(int *vet, int inicio, int fim) {
    if(inicio < fim) {
        // Particiona o vetor e descobre a posição real do pivô
        int pivo_pos = particiona(vet, inicio, fim); 
        
        // Ordena a sub-lista da esquerda
        quickSort(vet, inicio, pivo_pos - 1); 
        
        // Ordena a sub-lista da direita
        quickSort(vet, pivo_pos + 1, fim); 
    }
}

int particiona(int *vet, int inicio, int fim) {
    int i, aux, pivo = vet[inicio], pos = inicio;

    for(i = inicio + 1; i <= fim; i++) {
        if(vet[i] < pivo) {
            pos++;
            if(i != pos) {
                // Troca elementos para organizar os menores à esquerda
                aux = vet[i];
                vet[i] = vet[pos];
                vet[pos] = aux; 
            }
        }
    }
    // Coloca o pivô na sua posição correta (pos)
    aux = vet[inicio];
    vet[inicio] = vet[pos];
    vet[pos] = aux;

    return pos;
}

```