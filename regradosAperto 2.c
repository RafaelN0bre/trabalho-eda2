#include <stdio.h>
#include <string.h>

#define MAXV 2000

typedef char * Item;

typedef struct Item_total
{
    Item nome;
    int id;
}Item_total;

Item_total *ITEM_TOTAL(Item nome, int id)
{
    Item_total * item = malloc(sizeof(Item_total));
    item->id = id;
    item->nome = nome;
    return item;
}

typedef struct No_hash{
    Item_total *chave;
    struct No_hash *proximo;
}No_hash;

typedef struct{
    No_hash *inicio;
    int tam;
}Lista_hash;

void inicializar_lista_hash(Lista_hash *l){
    l->inicio = NULL;
    l->tam = 0;
}

int lista_vazia_hash(Lista_hash *l){
    if(l->inicio == NULL)
        return 1;
    else
        return 0;
}

int inserir_cabeca_lista_hash(Lista_hash *l, Item_total *valor){
    No_hash *No_hashvo = malloc(sizeof(No_hash));
    if(No_hashvo){
        No_hashvo->chave = valor;
        No_hashvo->proximo = l->inicio;
        l->inicio = No_hashvo;
        l->tam++;
        return 1;
    }
    else
        return 0;
}  

int inserir_calda_lista_hash(Lista_hash *l, Item_total *valor){
    No_hash *No_hashvo = malloc(sizeof(No_hash));
    No_hash *aux;
    if(No_hashvo){
        if(lista_vazia_hash(l)){
            inserir_cabeca_lista_hash(l, valor);
            return 1;
        }
        else{
            No_hashvo->chave = valor;
            No_hashvo->proximo = NULL;
            aux = l->inicio;
            while(aux->proximo != NULL)
                aux = aux->proximo;        
            aux->proximo = No_hashvo;
            l->tam++;
            return 1;
        }
    }
    else
        return 0;
}    

void imprimir_lista_hash(Lista_hash *l){
    No_hash *aux = l->inicio;
    printf(" Tam: %d: ", l->tam);
    while(aux){
        printf("%s[%d]", aux->chave->nome, aux->chave->id);
        aux = aux->proximo;
    }
    printf("\n");
}  

Item_total *buscar_lista_hash(Lista_hash *l, Item busca){
    No_hash*aux = l->inicio;
    while(aux && strcmp(aux->chave->nome, busca) != 0)
        aux = aux->proximo;
    if(aux)
        return aux->chave;
    return 0;
}

/// Tabela Hash ///
  
int HASH(Item v, int M)
{
	int h, a = 31415, b = 27183;

	for(h = 0; *v != '\0'; v++)
	{
		a = a*b % (M - 1);
		h = (a*h + *v) % M;	
	}

	return h;
}

typedef struct Ht_t
{
    Lista_hash *v;
    int M;
}Ht_t;  

int inicializa_Ht(Ht_t *ht, int M)
{
    ht->M = M;
    ht->v = malloc(sizeof(Lista_hash)*M);
    for(int i = 0; i< M; i++){
        inicializar_lista_hash(&ht->v[i]);
    }
    return 1;
} 

Item_total *busca_Ht(Ht_t *ht, Item busca){
    int hash = HASH(busca, ht->M);
    Item_total * ret = malloc(sizeof(Item_total));
    ret = buscar_lista_hash(&ht->v[hash], busca);
    return ret;
}

int insere_Ht(Ht_t *ht, Item_total *No_hashvo)
{
    int hash = HASH(No_hashvo->nome, ht->M);
    // if(busca_Ht(ht, No_hashvo))
	//     return 1;
	int inseriu = inserir_cabeca_lista_hash(&ht->v[hash], No_hashvo);
    return inseriu;
}  

void imprime_Ht(Ht_t *ht, int M){
    for(int i = 0; i<M;i++){
        if(ht->v[i].tam > 0){
            printf("%d ", i);
            imprimir_lista_hash(&ht->v[i]);
            printf("\n");
        }
    }
}

// Estrutura da lista
typedef struct no{
    Item chave;
    struct no *proximo;
}No;
  
typedef struct{
    No *inicio;
    int tam;
}Lista;
  
void inicializar_lista(Lista *l){
    l->inicio = NULL;
    l->tam = 0;
}
  
int lista_vazia(Lista *l){
    if(l->inicio == NULL)
        return 1;
    else
        return 0;
}
  
int inserir_cabeca_lista(Lista *l, Item valor){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->chave = valor;
        novo->proximo = l->inicio;
        l->inicio = novo;
        l->tam++;
        return 1;
    }
    else
        return 0;
}

int inserir_calda_lista(Lista *l, Item valor){
    No *novo = malloc(sizeof(No));
    No *aux;
    if(novo){
        if(lista_vazia(l)){
            inserir_cabeca_lista(l, valor);
            return 1;
        }
        else{
            novo->chave = valor;
            novo->proximo = NULL;
            aux = l->inicio;
            while(aux->proximo != NULL)
                aux = aux->proximo;        
            aux->proximo = novo;
            l->tam++;
            return 1;
        }
    }
    else
        return 0;
}  

Item *excluir_cabeca_lista(Lista *l){
    No *aux;
    aux = l->inicio;
    l->inicio = l->inicio->proximo;
    return aux->chave;
}
  
Item *excluir_calda_lista(Lista *l){
    No *aux;
    Item exc;
    aux = l->inicio;
    while(aux->proximo->proximo != NULL)
        aux = aux->proximo;
    exc = aux->proximo->chave;
    free(aux->proximo);
    aux->proximo = NULL;
    return exc;
} 

void imprimir_lista(Lista *l){
    No *aux = l->inicio;
    printf(" Tam: %d: ", l->tam);
    while(aux){
        printf("%d ", aux->chave);
        aux = aux->proximo;
    }
    printf("\n");
}

Item *buscar_lista(Lista *l, Item busca){
    No*aux = l->inicio;
    while(aux && strcmp(aux->chave, busca) != 0)
        aux = aux->proximo;
    if(aux)
        return aux->chave;
    return 0;
}

// Estrutura do Grafo

typedef struct Graph{
    int V;
    int E;
    Lista *adj;
}Graph;

typedef struct Edge
{
    Item v;
    Item w;
}Edge;

// Auxiliares

Edge *EDGE(Item a, Item b)
{
    Edge *aresta = malloc(sizeof(Edge));
    aresta->v = a;
    aresta->w = b;

    return aresta;
}

void imprimeListaArestas(Edge **a, int qtd)
{
    for(int i = 0; i< qtd; i++)
        printf("%d - %d %d\n", i, a[i]->v, a[i]->w);
}

Graph * GraphInit(int v){
    Graph *G = malloc(sizeof(G));
    G->V = v;
    G->E = 0;
    G->adj = malloc(sizeof(Lista)*v);
    for(int i = 0; i< v;i++)
        inicializar_lista(&G->adj[i]);
    return G;
}

void GraphInsertEdge(Graph *G, Edge *e, Ht_t *ht)
{
    Item v = e->v;
    Item w = e->w;
    inserir_cabeca_lista(&G->adj[busca_Ht(ht, v)->id], w);
    inserir_cabeca_lista(&G->adj[busca_Ht(ht, w)->id], v);
    G->E++;
}

int GraphEdges(Edge **a, Graph *G){
    int v, E = 0;
    No *t;
    for(v = 0; v < G->V; v++){
        t = G->adj[v].inicio;
        while(t){
            if(v < t->chave){
                a[E] = EDGE(v, t->chave);
                E++;
            }
            t = t->proximo;
        }
    }
    return E;
}

// Código de Filas

typedef struct no_fila{
    Edge *e;
    struct no_fila *proximo;
}No_fila;
  
typedef struct{
    No_fila *inicio;
    int tam;
}Fila;

void inicializar_fila(Fila *f){
    f->inicio = NULL;
    f->tam = 0;
}

int fila_vazia(Fila *f){
    if(f->inicio == NULL)
        return 1;
    else
        return 0;
}

int Fila_put(Fila *f, Edge *edge){
    No_fila *novo = malloc(sizeof(No));
    No_fila *aux;
    if(novo){
        if(fila_vazia(f)){
            novo->e = edge;
            novo->proximo = f->inicio;
            f->inicio = novo;
            f->tam++;
            return 1;
        }
        else{
            novo->e = edge;
            novo->proximo = NULL;
            aux = f->inicio;
            while(aux->proximo != NULL)
                aux = aux->proximo;        
            aux->proximo = novo;
            f->tam++;
            return 1;
        }
    }
    else
        return 0;
}  

Edge *Fila_pop(Fila *f){
    No_fila *aux;
    aux = f->inicio;
    f->inicio = f->inicio->proximo;
    return aux->e;
}

void imprimir_fila(Fila *f){
    No_fila *aux = f->inicio;
    printf(" Tam: %d: ", f->tam);
    while(aux){
        printf("%d ", aux->e);
        aux = aux->proximo;
    }
    printf("\n");
}


int least_distance(int *pre, Graph *G, Edge *src, Edge *destiny, Ht_t * ht, Item*vet)
{
    Fila *fila = malloc(sizeof(Fila)*1);
    inicializar_fila(fila);

    int *dist = malloc(sizeof(int)*G->V);
    for(int i = 0; i< G->V; i++)
        dist[i] = 9999999;
    for(int v = 0;v < G->V; v++)
        pre[v] = -1;
    Fila_put(fila, src);
    pre[busca_Ht(ht, src->w)->id] = 0;
    Edge *e = malloc(sizeof(Edge));
    while(!fila_vazia(fila))
    {
        e = Fila_pop(fila);
        if(e == src)
            dist[busca_Ht(ht, e->w)->id] = 0;
        for(int i = 0; i< G->V; i++)
            if(buscar_lista(&G->adj[busca_Ht(ht, e->w)->id], vet[i]))
                if(pre[i] == -1)
                {
                    if(dist[i] > dist[busca_Ht(ht, e->w)->id] + 1)
                        dist[i] = dist[busca_Ht(ht, e->w)->id]+1;
                    Fila_put(fila, EDGE(busca_Ht(ht, e->w)->nome, vet[i]));
                    pre[i] = 0;
                }
    }

    // for(int i = 0; i< G->V; i++)
    //     printf("%d ", dist[i]);

    free(fila);
    if(dist[busca_Ht(ht, destiny->v)->id] == 9999999)
        return -1;

    return dist[busca_Ht(ht, destiny->v)->id];
}


int main(void)
{
    int *pre = malloc(sizeof(int)*MAXV);

    // Contará as inserções
    int contador = 0;
    // Dois nomes que queremos verificar a conectividade
    char pessoa1[26];
    char pessoa2[26];

    scanf("%s %s", pessoa1, pessoa2);

    // N e M, número de pessoas, e número de apertos de mão respectivamente
    int N, M;
    scanf(" %d %d", &N, &M);

    Item * vetor_pessoas = malloc(sizeof(Item)*N);

    Graph *G = GraphInit(N);

    Ht_t *table = malloc(sizeof(Ht_t));
    inicializa_Ht(table, 5000);

    for(int i = 0; i<N; i++)
    {
        char *pessoa = malloc(sizeof(char)*26);
        scanf("%s", pessoa);
        vetor_pessoas[contador] = pessoa;
        insere_Ht(table, ITEM_TOTAL(pessoa, contador++));
    }

    for(int i = 0; i<M; i++)
    {
        char *pessoa_1 = malloc(sizeof(char)*26);
        char *pessoa_2 = malloc(sizeof(char)*26);
        scanf("%s %s", pessoa_1, pessoa_2);
        GraphInsertEdge(G, EDGE(pessoa_1, pessoa_2), table);
    }

    int least = least_distance(pre, G, EDGE(pessoa1, pessoa1), EDGE(pessoa2, pessoa2), table, vetor_pessoas);
    printf("%d", least);
    return 0;
}