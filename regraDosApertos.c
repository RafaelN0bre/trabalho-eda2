#include <stdio.h>
#include <stdbool.h>

#define MAXV 1001

//////////////// Lógica e estruturas da Pessoa /////////////////////
#include <string.h>

typedef char * Item_hash;

typedef struct Item_total
{
    Item_hash nome;
    int id;
}Item_total;

Item_total *ITEM_TOTAL(Item_hash nome, int id)
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

int inserir_cabeca_lista(Lista *l, Item_total *valor){
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

int inserir_calda_lista(Lista *l, Item_total *valor){
    No_hash *No_hashvo = malloc(sizeof(No_hash));
    No_hash *aux;
    if(No_hashvo){
        if(lista_vazia(l)){
            inserir_cabeca_lista(l, valor);
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

void imprimir_lista(Lista *l){
    No_hash *aux = l->inicio;
    printf(" Tam: %d: ", l->tam);
    while(aux){
        printf("%s[%d]", aux->chave->nome, aux->chave->id);
        aux = aux->proximo;
    }
    printf("\n");
}  

Item_total *buscar_lista(Lista *l, Item_hash busca){
    No_hash*aux = l->inicio;
    while(aux && strcmp(aux->chave->nome, busca) != 0)
        aux = aux->proximo;
    if(aux)
        return aux->chave;
    return 0;
}

/// Tabela Hash ///
  
int HASH(Item_hash v, int M)
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
    Lista *v;
    int M;
}Ht_t;  

int inicializa_Ht(Ht_t *ht, int M)
{
    ht->M = M;
    ht->v = malloc(sizeof(Lista)*M);
    for(int i = 0; i< M; i++){
        inicializar_lista(&ht->v[i]);
    }
    return 1;
} 

Item_total *busca_Ht(Ht_t *ht, Item_hash busca){
    int hash = HASH(busca, ht->M);
    Item_total * ret = malloc(sizeof(Item_total));
    ret = buscar_lista(&ht->v[hash], busca);
    return ret;
}

int insere_Ht(Ht_t *ht, Item_total *No_hashvo)
{
    int hash = HASH(No_hashvo->nome, ht->M);
    // if(busca_Ht(ht, No_hashvo))
	//     return 1;
	int inseriu = inserir_cabeca_lista(&ht->v[hash], No_hashvo);
    return inseriu;
}  

void imprime_Ht(Ht_t *ht, int M){
    for(int i = 0; i<M;i++){
        if(ht->v[i].tam > 0){
            printf("%d ", i);
            imprimir_lista(&ht->v[i]);
            printf("\n");
        }
    }
}

// Definindo os tipos
typedef int Item;

typedef struct Graph
{
	int V;
	int E;
	int **adj;
}Graph;

typedef struct Edge
{
    Item v;
    Item w;
}Edge;

// Auxiliares
Item**MATRIZInit(int linhas, int colunas, int valor_inicial)
{
    int **matriz = malloc(linhas*sizeof(Item*));
    for(int i = 0; i< linhas; i++)
        matriz[i] = malloc(sizeof(Item)*colunas);

    for(int i = 0; i<linhas; i++)
        for(int j = 0; j < colunas; j++)
            matriz[i][j] = valor_inicial;
    return matriz;
}

void imprimeMatriz(Item**matriz, int linhas, int colunas){
    
    printf("    ");
    for(int w = 0; w< colunas;w++)
        printf("%c  ", w+65);
    printf("\n");
    printf("    ");
    for(int w = 0; w< colunas;w++)
        printf("-  ", w);
    printf("\n");
    for(int i = 0; i< linhas; i++)
    {   
        printf("%c - ", i+65);
        for(int j = 0; j<colunas; j++)
            printf("%d  ", matriz[i][j]);
        printf("\n");
    }
    printf("\n");
}

Edge*EDGE(Item a, Item b)
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

// Código de Filas

typedef struct no{
    Edge *e;
    struct no *proximo;
}No;
  
typedef struct{
    No *inicio;
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
    No *novo = malloc(sizeof(No));
    No *aux;
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
    No *aux;
    aux = f->inicio;
    f->inicio = f->inicio->proximo;
    return aux->e;
}

void imprimir_fila(Fila *f){
    No *aux = f->inicio;
    printf(" Tam: %d: ", f->tam);
    while(aux){
        printf("%d ", aux->e);
        aux = aux->proximo;
    }
    printf("\n");
}

// Inicializa Grafo
Graph *GraphInit(int V)
{
	Graph *G = malloc(sizeof(Graph));
	G->V = V;
	G->E = 0;
	G->adj = MATRIZInit(V, V, 0);
	return G;
}

// Inserir aresta em Grafo
void GraphInsertEdge(Graph *G, Edge *e)
{
    Item v = e->v;
    Item w = e->w;
    if(G->adj[v][w] == 0)
        G->E++;
    G->adj[v][w] = 1;
    G->adj[w][v] = 1;
}

int least_distance(int *pre, Graph *G, Edge *src, Edge *destiny)
{
    Fila *fila = malloc(sizeof(Fila)*1);
    inicializar_fila(fila);

    int *dist = malloc(sizeof(int)*G->V);
    for(int i = 0; i< G->V; i++)
        dist[i] = 9999999;
    for(int v = 0;v < G->V; v++)
        pre[v] = -1;

    Fila_put(fila, src);
    pre[src->w] = 0;
    Edge *e = malloc(sizeof(Edge));
    while(!fila_vazia(fila))
    {
        e = Fila_pop(fila);
        if(e == src)
            dist[e->w] = 0;
        for(int i = 0; i< G->V; i++)
            if(G->adj[e->w][i] != 0)    
                if(pre[i] == -1)
                {
                    if(dist[i] > dist[e->w] + 1)
                        dist[i] = dist[e->w]+1;
                    Fila_put(fila, EDGE(e->w, i));
                    pre[i] = 0;
                }
    }

    // for(int i = 0; i< G->V; i++)
    //     printf("%d ", dist[i]);

    free(fila);
    if(dist[destiny->v] == 9999999)
        return -1;

    return dist[destiny->v];
}

int main(void)
{
    int *pre = malloc(sizeof(int)*MAXV);

    Ht_t *table = malloc(sizeof(Ht_t)*1);

    int inicializa = inicializa_Ht(table, 500);

    // Contará as inserções
    int contador = 0;

    // Dois nomes que queremos verificar a conectividade
    Item_hash pessoa1 = malloc(sizeof(char)*26);
    Item_hash pessoa2 = malloc(sizeof(char)*26);
    scanf("%s %s", pessoa1, pessoa2);

    // N e M, número de pessoas, e número de apertos de mão respectivamente
    int N, M;
    scanf(" %d %d", &N, &M);

    Graph *G = GraphInit(N);
    insere_Ht(table, ITEM_TOTAL(pessoa1, contador++));
    insere_Ht(table, ITEM_TOTAL(pessoa2, contador++));

    for(int i = 0; i<N; i++)
    {
        Item_hash pessoa = malloc(sizeof(char)*26);
        scanf("%s", pessoa);
        if(strcmp(pessoa, pessoa1) == 0 || strcmp(pessoa, pessoa2) == 0) continue;
        insere_Ht(table, ITEM_TOTAL(pessoa, contador++));
    }

    // imprime_Ht(table, 1000);

    for(int i = 0; i<M; i++)
    {
        Item_hash temp1 = malloc(sizeof(char)*26);
        Item_hash temp2 = malloc(sizeof(char)*26);
        scanf("%s %s", temp1, temp2);
        Item_total *resposta1 = busca_Ht(table, temp1);
        Item_total *resposta2 = busca_Ht(table, temp2);

        GraphInsertEdge(G, EDGE(resposta1->id, resposta2->id));
    }
    // imprime_Ht(table, 1000);0

 
    int least = least_distance(pre, G, EDGE(0, 0), EDGE(1, 1));
    printf("%d", least);
    return 0;
}