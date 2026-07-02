# Insertion Sort 
O Insertion Sort atua dividindo o vetor em duas partes: 
- Ordenada: se inicia na posição 0 e aumenta a cada iteração (++) 
- Desordenada: É todo o restante do vetor e diminui a cada iteração, com o crescimento da parte ordenada. 
Ele pega o primeiro elemento na posição desordenada do vetor e "volta ele pra trás", para a parte ordenada, até chegar na sua posição dentro do vetor ordenado. Após encontrar um elemento menor que o último elemento da parte ordenada do vetor, ele realiza o "shift", movendo os elementos uma casa à frente até que o respectivo menor elemento esteja na posição correta dele. 

# Complexidade 
A complexidade assintótica é O(n^2)

# Estabilidade 
O Insertion Sort é estável, um elemento que está na sua posição relativa correta permanecerá nela até o final da ordenação. 