#define MAXNUMVERTICES 100
#define AN -1                /* aresta nula, ou seja, valor que representa ausencia de aresta */
#define VERTICE_INVALIDO -1  /* numero de vertice invalido ou ausente */

#include <stdbool.h>   /* variaveis bool assumem valores "true" ou "false" */

typedef int TipoPeso;
typedef struct  {
  TipoPeso mat[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
  int numVertices;
  int numArestas;
} TipoGrafo;
typedef int TipoApontador;

/*
  bool inicializaGrafo(TipoGrafo* grafo, int nv): Inicializa um grafo com nv vertices.
  Vertices vao de 0 a nv-1.
  Preenche as celulas com AN (representando ausencia de aresta).
  Retorna true se inicializou com sucesso e false caso contrario
*/ 
bool inicializaGrafo(TipoGrafo* grafo, int nv);

/*
  void insereAresta(int v1, int v2, TipoPeso peso, TipoGrafo *grafo):
  Insere a aresta (v1, v2) com peso "peso" no grafo.
  Nao verifica se a aresta ja existia.   	
*/ 
void insereAresta(int v1, int v2, TipoPeso peso, TipoGrafo *grafo);

/*
  bool existeAresta(int v1, int v2, TipoGrafo *grafo):
  Retorna true se existe a aresta (v1, v2) no grafo e false caso contrário  
*/
bool existeAresta(int v1, int v2, TipoGrafo *grafo);


/*
  bool removeAresta(int v1, int v2, TipoPeso* peso, TipoGrafo *grafo);
  Remove a aresta (v1, v2) do grafo colocando AN em sua celula (representando ausencia de aresta).
  Se a aresta existia, coloca o peso dessa aresta em "peso" e retorna true,
  caso contrario retorna false (e "peso" é inalterado).  
*/ 
bool removeAresta(int v1, int v2, TipoPeso* peso, TipoGrafo *grafo);

/* 
   bool listaAdjVazia(int v, TipoGrafo* grafo):
   Retorna true se a lista de adjacencia (de vertices adjacentes) do vertice v é vazia, e false caso contrário. 
*/
bool listaAdjVazia(int v, TipoGrafo* grafo);

/*
   TipoApontador primeiroListaAdj(int v, TipoGrafo* grafo):
   Retorna o primeiro vertice da lista de adjacencia de v
   ou VERTICE_INVALIDO se a lista de adjacencia estiver vazia.    
*/
TipoApontador primeiroListaAdj(int v, TipoGrafo* grafo);

/*
   TipoApontador proxListaAdj(int v, TipoGrafo* grafo, TipoApontador atual):
   Trata-se de um iterador sobre a lista de adjacência do vertice v.
   Retorna o proximo vertice adjacente a v, partindo do vertice "atual" adjacente a v
   ou VERTICE_INVALIDO se a lista de adjacencia tiver terminado sem um novo proximo.        
*/
TipoApontador proxListaAdj(int v, TipoGrafo* grafo, TipoApontador atual);

/*
    void imprimeGrafo(TipoGrafo* grafo):
    Imprime a matriz de adjacencia do grafo.
    Assuma que cada vértice e cada peso de aresta são inteiros de até 2 dígitos.
*/
void imprimeGrafo(TipoGrafo* grafo);

/* Nao precisa fazer nada para matrizes de adjacencia */
void liberaGrafo(TipoGrafo* grafo); 




