/************************************
	ACH2024 - Algoritmos e Estruturas de Dados II

	Implementacao de Grafos utilizando Listas de Adjacencia
	(vetor de ponteiros no qual cada posicao indexa um vertice e
	 contem o ponteiro para a sua lista de adjacencia)

*************************************/

#include <stdbool.h>   /* variaveis bool assumem valores "true" ou "false" */

#define VERTICE_INVALIDO -1  /* numero de vertice invalido ou ausente */
#define AN -1                /* aresta nula */ 

typedef int TipoPeso;

/*
  tipo estruturado taresta:
      vertice destino, peso, ponteiro p/ prox. aresta
*/
typedef struct taresta {
  int vdest;
  TipoPeso peso;
  struct taresta * prox;
} TipoAresta;

typedef TipoAresta* TipoApontador;

/*
  tipo estruturado grafo:
      vetor de listas de adjacencia (cada posicao contem o ponteiro
                    para o inicio da lista de adjacencia do vertice)
      numero de vertices
*/
typedef struct {
  TipoApontador *listaAdj;
  int numVertices;
  int numArestas;
} TipoGrafo;

/********************

  Prototipos dos metodos sobre grafos

*********************/

bool inicializaGrafo(TipoGrafo* grafo, int nv);

int obtemNrVertices(TipoGrafo* grafo);

int obtemNrArestas(TipoGrafo* grafo);

bool verificarValidadeVertice(int v, TipoGrafo* grafo);

bool existeAresta(int v1, int v2, TipoGrafo* grafo);

void insereAresta(int v1, int v2, TipoPeso peso, TipoGrafo* grafo);

TipoApontador proxListaAdj(int v, TipoGrafo* grafo, TipoApontador atual);

TipoPeso obtemPesoAresta(int v1, int v2, TipoGrafo* grafo);

bool removeArestaObtendoPeso(int v1, int v2, TipoPeso* peso, TipoGrafo *grafo);

bool removeAresta(int v1, int v2, TipoGrafo* grafo);

bool listaAdjVazia(int v, TipoGrafo* grafo);

TipoApontador primeiroListaAdj(int v, TipoGrafo *grafo);

void imprimeGrafo(TipoGrafo* grafo);

void liberaGrafo(TipoGrafo* grafo);

TipoApontador verticeDestino();

void imprimeErroIniciar();

void imprimeErro(char funcao[], int v, TipoGrafo* grafo);
