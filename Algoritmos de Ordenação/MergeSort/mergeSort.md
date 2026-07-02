# Merge Sort 

- Dividir para conquistar: Divide o problema em soluções menores 
    - Divide o vetor ao meio até que se tenha um vetor com um elemento (garantido que está ordenado) e à partir daí começa a ordenar os sub-vetores da esquerda para a direita até atingir a ordenação do vetor original 

- Complexidade: O(nlogn) para TODOS os casos

- Por ser recursivo e fazer alocações consome mais recursos de memória e pilha, mas é válido pelo ganho de eficiência 

- Estabilidade: Estável 
    - Não troca um elemento de posição se esta for a posição correta dele

- Métodos: 
 1. MergeSort: Responsável pela chamadas das recursivas e por dividir os vetores ao meio
 2. Merge: Responsável por agrupar os sub-vetores
 
---

## 1. Merge Sort (Ordenação por Interpolação)

O Merge Sort utiliza a estratégia de **Dividir para Conquistar**. A alma do algoritmo é a função `merge`.

### 🧠 A Lógica (First Steps)
Imagine duas pilhas de cartas já ordenadas sobre a mesa. Para criar uma única pilha ordenada:
1. Você olha para as duas cartas do topo.
2. Move a **menor** para a nova pilha.
3. Repete até que uma das pilhas acabe.
4. Copia o restante da pilha que sobrou.


---