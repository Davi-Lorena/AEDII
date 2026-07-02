# 1
com a utilização do preemtive Split/Merge (que só estava habilitado para ordens pares) os nós sofreram o split antes da inserção do elemento que excederia o tamanho. Em termos de implementação, primeiro teríamos que verificar se a ocupação é máxima, se sim, fazer o split e depois realizar a inserção do novo elemento. Se assemelha ao que acontece com Ms ímpares

# 2  Explique a seguinte sentença: “B-Trees são construídas de baixo para cima, enquanto árvores binárias são construídas de cima para baixo”.
Nas árvores binárias, como os nós armazema apenas uma chave, ela cresce à partir da raiz e vai se ramificando de acordo com suas regras de inserção, sendo que cada nó inserido será folha. Já as B-Trees contém mais de uma chave por nó e quando a ocupação máxima do respectivo nó é alcançada, ela "cresce pra cima", com o split gerando uma nova raiz e um irmão, preservando a integridade. 

# 3 Por que B-Trees são consideradas geralmente superiores que as árvores binárias de busca para pesquisa externa, e árvores binárias são comumente usadas para pesquisa interna?
Pela organização dos dados nos blocos de memória, que garantem uma ocupação estável das posições de memória e otimiza a busca ao manter a estrutura de árvore. Como elas armazenam mais de 1 dado por nó, elas se tornam mais eficientes pois é possível armazenar mais em uma árvore menor. Além disso, são projetadas para terem o tamanho exato de um bloco de disco, o que reduz o número de acessos ao disco por concentrar mais informações 
Já as ABP são utilizadas para pesquisa interna por serem mais rápidas e fáceis de serem implementadas para o uso na memória RAM. 

# 4 Dada uma Árvore-B de ordem 256
## a - Qual o número máximo de descendentes de uma página?
256 descendentes

## b - Qual o número mínimo de descendentes de uma página (excluindo a raiz e as folhas)?
256 / 2 = 128

## c - Qual o número mínimo de descendentes da raiz?
2 (mínimo de 1 chave)

## d - Qual o número mínimo de descendentes de uma folha?
0, folhas não tem descendentes.

## e - Quantas chaves há numa página não folha com 200 descendentes?
199 chaves 

## f - Qual a profundidade máxima de uma árvore que contém 100.000 chaves?

# 5 Montar a árvore: 
C G J X N S U O A E B H I F K L Q R T V U W Z

# 6 Remover de uma árvore: 
A B Q R 

# 7 Implementação da função busca No

# 8  Considere as estruturas de índices em memória secundária: B-Tree, B+Tree e B*Tree.
## a - explique uma diferença estrutural entre a B-Tree e a B+Tree.
A B-tree armazena chaves em todos os nós da árvore, enquanto a B+ armazena apenas nós nos folhas (nós intermediários e raiz armazenam índices)

## b - Em qual dessas estruturas a busca por um intervalo de chaves (por exemplo, todas as chaves entre 100 e 200) tende a ser mais eficiente? Justifique
A B+Tree, porque como todos os nós estão armazenados nas folhas, o percorrimento entre eles é mais eficiente, tendo em vista que todos estão conectados como uma lista

## c - Qual é a principal estratégia utilizada pela B*Tree para reduzir a quantidade de divisões (splits) em comparação com a B-Tree tradicional?
Utilizar a ocupação mínima do nó como 2/3 ao inés de 1/2. Além disso, a B*Tree faz rotações "empurrando" nós de irmãos mais cheios para irmãos vazios. Essa redistribuição faz com que o split só ocorra quando o nó e o irmão estiverem cheios.

# 9  Considere os seguintes registros de alunos, na ordem em que foram recebidos pelo sistema:
RA Nome
25 Ana
12 Bruno
38 Carla
17 Daniel
29 Elisa

Considere que cada bloco comporta exatamente 2 registros

## a Mostre como os registros ficariam armazenados em um arquivo heap após todas as inserções.
0 - 25 12 
1 - 38 17
2 - 29

## b Mostre como os registros ficariam armazenados em um arquivo sequencial ordenado pelo RA
0 - 12 17
1 - 25 29 
2 - 38

## c nsidere uma organização por hash estático com 3 buckets e função: ℎ(𝑅𝐴) = 𝑅𝐴𝑚𝑜𝑑3 e mostre o conteúdo final de cada bucket após a inserção dos registros.
0 - 12
1 - 25
2 - 38 17 OVERFLOW 29


