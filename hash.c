#include <stdio.h>
#include <string.h>

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
}Lista_Ht;

void inicializar_Lista_Ht(Lista_Ht *l){
    l->inicio = NULL;
    l->tam = 0;
}

int Lista_Ht_vazia(Lista_Ht *l){
    if(l->inicio == NULL)
        return 1;
    else
        return 0;
}

int inserir_cabeca_Lista_Ht(Lista_Ht *l, Item_total *valor){
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

int inserir_calda_Lista_Ht(Lista_Ht *l, Item_total *valor){
    No_hash *No_hashvo = malloc(sizeof(No_hash));
    No_hash *aux;
    if(No_hashvo){
        if(Lista_Ht_vazia(l)){
            inserir_cabeca_Lista_Ht(l, valor);
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

void imprimir_Lista_Ht(Lista_Ht *l){
    No_hash *aux = l->inicio;
    printf(" Tam: %d: ", l->tam);
    while(aux){
        printf("%s[%d]", aux->chave->nome, aux->chave->id);
        aux = aux->proximo;
    }
    printf("\n");
}  

Item_total *buscar_Lista_Ht(Lista_Ht *l, Item_hash busca){
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
    Lista_Ht *v;
    int M;
}Ht_t;  

int inicializa_Ht(Ht_t *ht, int M)
{
    ht->M = M;
    ht->v = malloc(sizeof(Lista_Ht)*M);
    for(int i = 0; i< M; i++){
        inicializar_Lista_Ht(&ht->v[i]);
    }
    return 1;
} 

Item_total *busca_Ht(Ht_t *ht, Item_hash busca){
    int hash = HASH(busca, ht->M);
    Item_total * ret = malloc(sizeof(Item_total));
    ret = buscar_Lista_Ht(&ht->v[hash], busca);
    return ret;
}

int insere_Ht(Ht_t *ht, Item_total *No_hashvo)
{
    int hash = HASH(No_hashvo->nome, ht->M);
    // if(busca_Ht(ht, No_hashvo))
	//     return 1;
	int inseriu = inserir_cabeca_Lista_Ht(&ht->v[hash], No_hashvo);
    return inseriu;
}  

void imprime_Ht(Ht_t *ht, int M){
    for(int i = 0; i<M;i++){
        if(ht->v[i].tam > 0){
            printf("%d ", i);
            imprimir_Lista_Ht(&ht->v[i]);
            printf("\n");
        }
    }
}

int main(void){
    Ht_t *table = malloc(sizeof(Ht_t)*1);
    printf("Insira o tamanho da tabela HASH: ");
    int m;
    scanf("%d", &m);

    int inicializa = inicializa_Ht(table, m);
    printf("Tabela hash com - %d Espacos inicializada\n", table->M);
    
    printf("Fase de insercao, insira quantas insercoes deseja fazer: ");
    int n;
    scanf("%d", &n);
    for(int i = 0;i<n;i++){
        Item_hash temp = malloc(sizeof(Item_hash));
        int temp2;
        scanf("%s %d", temp, &temp2);
        Item_total *item = ITEM_TOTAL(temp, temp2);
        int inseriu = insere_Ht(table, item);
        if(inseriu)
            printf("insercao concluida\n");
        else
            printf("inserão falhou");
    }

    printf("Tabela HASH\n");
    imprime_Ht(table, m);

    printf("Fase de busca, insira quantas buscas deseja fazer: ");
    int b;
    scanf("%d", &b);
    for(int i = 0;i<b;i++){
        Item_hash temp = malloc(sizeof(Item_hash));
        scanf("%s", temp);
        Item_total *resposta = busca_Ht(table, temp);
        if(resposta)
            printf("Item_hash encontrado - %d\n", resposta->id);
        else
            printf("Item_hash nao encontrado\n");
    }

    return 0;

}