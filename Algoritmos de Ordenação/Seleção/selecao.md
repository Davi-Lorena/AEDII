# Selection Sort 
Divide o vetor em duas partes: 
- Ordenada: se inicia na posição 0 e aumenta a cada iteração (++) 
- Desordenada: É todo o restante do vetor e diminui a cada iteração, com o crescimento da parte ordenada. 
Funciona buscando sempre o menor elemento da parte desordenada do vetor e o colocando na "ponta" da parte ordenada. Dessa forma, garantimos que o vetor até aquele ponto esteja ordenado. 

## Complexidade
A complexidade assintótica do Selection sort é O(n^2).

## Estabilidade 
O selection sort não é estável, um elemento que está em sua respectiva posição correta final no vetor pode ser trocado de lugar até que o vetor se ordene por completo. 