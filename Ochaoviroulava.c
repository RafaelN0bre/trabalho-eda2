#include <stdio.h>
#include <stdbool.h>

#define MAXV 2000

//////////////// Lógica e estruturas do Ponto /////////////////////

typedef struct Ponto{
    int x;
    int y;
}Ponto;

Ponto PONTO(int x, int y)
{
    Ponto ponto;
    ponto.x = x;
    ponto.y = y;
    
    return ponto;
}

void imprime_vetor_pontos(Ponto *vetor_pontos, int cont)
{
    printf("Vetor de pontos\n");
    printf("Ponto\tX\tY\n");
    for(int i = 0; i<cont; i++)
        printf("%c\t%d\t%d\n", i+65, vetor_pontos[i].x, vetor_pontos[i].y);
    printf("\n");
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

// Remover aresta de um Grafo
void GraphRemoveEdge(Graph *G, Edge *e)
{
    Item v = e->v;
    Item w = e->w;

    if(G->adj[v][w] == 1)
        G->E--;
    G->adj[v][w] = 0;
    G->adj[w][v] = 0;
}

// Encontrar todas as arestas de um grafo
int GraphEdges(Edge **e, Graph *G)
{
    int v, w, E = 0;
    for(v = 0; v<G->V; v++)
        for(w = v+1; w< G->V; w++)
            if(G->adj[v][w] == 1)
                e[E++] = EDGE(v, w);

    return E;
}

// Buscas

// Aqui temos o vetor pre e nosso count, serão declarados como variáveis estáticas

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

// Calcula a distância euclidiana e verificar se o tamanho é menor do que o passo de Gabriel
int is_conectado(int passo, Ponto a, Ponto b)
{
    float dist = sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
    // printf("%f\n", dist);
    return dist<=passo;
}


int main(void)
{
    int *pre = malloc(sizeof(int)*MAXV);

    // Contará as inserções
    int contador = 0;

    // Tamanho do passo de Gabriel 1 <= d <= 10^3
    int d;
    scanf(" %d", &d);

    // Número total de pontos. Inclui o ponto O, e o ponto S. 2 <= n <= 10^3
    int n;
    scanf(" %d", &n);

    Ponto *vetor_pontos = malloc(sizeof(Ponto)*n);


    // Coordenadas do ponto inicial de Gabriel O. -10^5 <= o_x, o_y <= 10^5
    int o_x, o_y;
    scanf(" %d %d", &o_x, &o_y);
    vetor_pontos[contador++] = PONTO(o_x, o_y);
    // Coordenadas do sofá S. -10^5 <= o_x, o_y <= 10^5
    int s_x, s_y;
    scanf(" %d %d", &s_x, &s_y); 
    vetor_pontos[contador++] = PONTO(s_x, s_y);
    
    Graph *G = GraphInit(n);
    
    for(int i = 0; i<n-2; i++)
    {
        int i_x, i_y;
        scanf(" %d %d", &i_x, &i_y);
        vetor_pontos[contador++] = PONTO(i_x, i_y);

    }

    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            if(is_conectado(d, vetor_pontos[i], vetor_pontos[j]))
                GraphInsertEdge(G, EDGE(i, j));

        
    // imprime_vetor_pontos(vetor_pontos, n);
    // imprimeMatriz(G->adj, n, n);
    printf("%d", least_distance(pre, G, EDGE(0, 0), EDGE(1, 1)));

    return 0;
}
