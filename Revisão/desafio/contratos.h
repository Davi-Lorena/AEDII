
typedef struct fornecedor sfor;
typedef struct cliente scli;
typedef struct lista tlista;

tlista *cria_lista ();
int insere_cliente (tlista *l, int dia_fim, int rec);
sfor *alocaVetor(int tam);
void preencheFornecedores(sfor *f, int tam);
void preencheOperações (tlista *l, sfor *fornecedor, int tam);
void calcula_s (sfor *fornecedor, int id, tlista *l);
