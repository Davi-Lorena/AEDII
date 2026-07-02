#include <stdio.h>
#include <stdlib.h>
#include "contratos.h"

int main() {
    int n, q;
    sfor *f;
    tlista *l;

    l = cria_lista();
    if(!l) return -1;
    
    scanf("%d", &n);

    f = alocaVetor(n);
    if(!f) return -1;

    preencheFornecedores(f, n);

    scanf("%d", &q);
    preencheOperações(l, f, q);

    return 0;
}