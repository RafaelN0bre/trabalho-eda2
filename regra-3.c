#include <stdio.h>
#include <stdbool.h>

#define MAXV 1001

//////////////// Lógica e estruturas da Pessoa /////////////////////

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
        printf("%d  ", w);
    printf("\n");
    printf("    ");
    for(int w = 0; w< colunas;w++)
        printf("-  ", w);
    printf("\n");
    for(int i = 0; i< linhas; i++)
    {   
        printf("%d - ", i);
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
    char s[1000][26];
    // Contará as inserções
    int contador = 0;

    // Dois nomes que queremos verificar a conectividade
    char pessoa1[26];
    char pessoa2[26];

    scanf("%s %s", pessoa1, pessoa2);

    // N e M, número de pessoas, e número de apertos de mão respectivamente
    int N, M;
    scanf(" %d %d", &N, &M);

    Graph *G = GraphInit(N);

    for(int i = 0; i<N; i++)
        scanf("%s", s[contador++]);

    int c[2];
    
    for(int i = 0; i<M; i++)
    {
        char temp1[26];
        char temp2[26];
        scanf("%s %s", temp1, temp2);
        int cont = 0;
        int b[2];
        for(int i = 0; i < N && cont != 2; i++)
        {
            if(strcmp(temp1, s[i]) == 0 || strcmp(temp2, s[i]) == 0)
                b[cont++] = i;
            if(strcmp(pessoa1, s[i]) == 0)
                c[0] = i;
            if(strcmp(pessoa2, s[i]) == 0)
                c[1] = i;
        }

        GraphInsertEdge(G, EDGE(b[0], b[1]));
    }

 
    int least = least_distance(pre, G, EDGE(c[0], c[0]), EDGE(c[1], c[1]));
    printf("%d", least);

    return 0;
}