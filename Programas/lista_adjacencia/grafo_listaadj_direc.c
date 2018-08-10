#include <stdio.h>
#include <stdlib.h>
#include "grafo_listaadj.h"

/*
    Grafo direcionado
*/

//COMPLETO
bool inicializaGrafo(TipoGrafo* grafo, int nv){
	if(nv <= 0){
	    imprimeErroIniciar();
	    return false;
	}
	else{
	    grafo->listaAdj = (TipoApontador*) calloc(nv+1,sizeof(TipoApontador));
	    grafo->numVertices = nv;
	    grafo->numArestas = 0;
	    return true;
	}
	return false;
}

//COMPLETO
int obtemNrVertices(TipoGrafo* grafo){
	return grafo->numVertices;
}

//COMPLETO
int obtemNrArestas(TipoGrafo* grafo){
	return grafo->numArestas;
}

//COMPLETO
bool verificarValidadeVertice(int v, TipoGrafo* grafo){
	if(v <= 0) return false;
	if(v > grafo->numVertices) return false;
	return true;
}

//COMPLETO
bool existeAresta(int v1, int v2, TipoGrafo* grafo){
	char funcao[] = "existeAresta";
	if(!verificarValidadeVertice(v1,grafo)){
	    imprimeErro(funcao,v1,grafo);
	    return false;
	}
	if(!verificarValidadeVertice(v2,grafo)){
	    imprimeErro(funcao,v2,grafo);
	    return false;
	}
	TipoApontador p;
	p = grafo->listaAdj[v1];
	while(p){
	    if(p->vdest == v2) return true;
	    p = p->prox;
	}
	return false;
}

//COMPLETO
void insereAresta(int v1, int v2, TipoPeso peso, TipoGrafo* grafo){
	char funcao[] = "insereAresta";
	if(!verificarValidadeVertice(v1,grafo)) imprimeErro(funcao,v1,grafo);
	if(!verificarValidadeVertice(v2,grafo)) imprimeErro(funcao,v2,grafo);
	TipoApontador p;
	p = (TipoApontador) malloc(sizeof(TipoApontador));
	p->prox = NULL;
	p->vdest = v2;
	p->peso = peso;
	if(grafo->listaAdj[v1] == NULL) grafo->listaAdj[v1] = p;
	else{
        p->prox = grafo->listaAdj[v1];
        grafo->listaAdj[v1] = p;
	}
	grafo->numArestas++;
}

//COMPLETO
TipoPeso obtemPesoAresta(int v1, int v2, TipoGrafo* grafo){
    char funcao[] = "obtemPesoAresta";
    if(!verificarValidadeVertice(v1,grafo)) imprimeErro(funcao,v1,grafo);
    if(!verificarValidadeVertice(v2,grafo)) imprimeErro(funcao,v2,grafo);
    TipoApontador p;
    p = grafo->listaAdj[v1];
    while(p){
        if(p->vdest == v2) return p->peso;
        p = p->prox;
    }
    return AN;
}

//COMPLETO
bool removeArestaObtendoPeso(int v1, int v2, TipoPeso* peso, TipoGrafo *grafo){
    char funcao[] = "removeArestaObtendoPeso";
    if(!verificarValidadeVertice(v1,grafo)) imprimeErro(funcao,v1,grafo);
    if(!verificarValidadeVertice(v2,grafo)) imprimeErro(funcao,v2,grafo);
    TipoApontador p;
    p = grafo->listaAdj[v1];
    TipoApontador ant = NULL;
    while(p){
        if(p->vdest == v2){
            if(ant != NULL) ant->prox = p->prox;  //Se nao for inicial ele pega o anterior e passa o proximo para frente.
            p->prox = NULL;
            *peso = p->peso;
            p->peso = AN;
            grafo->numArestas--;
            return true;
        }
        ant = p;
        p = p->prox;
    }
    return false;
}

//COMPLETO
bool removeAresta(int v1, int v2, TipoGrafo* grafo){
    char funcao[] = "removeAresta";
    if(!verificarValidadeVertice(v1,grafo)) imprimeErro(funcao,v1,grafo);
    if(!verificarValidadeVertice(v2,grafo)) imprimeErro(funcao,v2,grafo);
    TipoApontador p;
    p = grafo->listaAdj[v1];
    TipoApontador ant = NULL;
    while(p){
        if(p->vdest == v2){
            if(ant != NULL) ant->prox = p->prox;  //Se nao for inicial ele pega o anterior e passa o proximo para frente.
            p->peso = AN;
            p->prox = NULL;
            grafo->numArestas--;
            return true;
        }
        ant = p;
        p = p->prox;
    }
    return false;
}

//COMPLETO
bool listaAdjVazia(int v, TipoGrafo* grafo){
    char funcao[] = "ListaAdjVazia";
    if(!verificarValidadeVertice(v,grafo)) imprimeErro(funcao,v,grafo);
    if(grafo->listaAdj[v] == NULL) return true;
    return false;
}

//COMPLETO
TipoApontador primeiroListaAdj(int v, TipoGrafo *grafo){
    char funcao[] = "primeiroListaAdj";
    if(!verificarValidadeVertice(v,grafo)) imprimeErro(funcao,v,grafo);
    if(grafo->listaAdj[v] != NULL) return grafo->listaAdj[v];
    return NULL;
}

//COMPLETO
TipoApontador proxListaAdj(int v, TipoGrafo* grafo, TipoApontador atual){
    char funcao[] = "proxListaAdj";
    if(!verificarValidadeVertice(v,grafo)) imprimeErro(funcao,v,grafo);
    if(atual->prox != NULL) return atual->prox;
    return NULL;
}

//COMPLETO
void imprimeGrafo(TipoGrafo* grafo){
    int i,j;
    TipoApontador p;
    for(i=1;i<=grafo->numVertices;i++){
        printf("v%2d: ",i);
        p = grafo->listaAdj[i];
        while(p){
            printf("(%2d,%2d);",p->vdest,p->peso);
            p->prox;
        }
        printf("\n");
    }
}

//COMPLETO
void liberaGrafo(TipoGrafo* grafo){
	int i;
	TipoApontador p;
	TipoApontador ant;
	/*
	 * Liberação das arestas do grafo
	 * */
	for(i=1;i <= grafo->numVertices; i++){
	    p = grafo->listaAdj[i]->prox;
	    free(grafo->listaAdj[i]);
	    grafo->listaAdj[i];
	    while(p){
            ant = p;
            p = p->prox;
            free(ant);
	    }
	}
	free(grafo->listaAdj);
	grafo->numVertices=0;
	grafo->numArestas=0;
	/*
	 * Liberação da alocação do vetor de vértices
	 * e zerando o grafo.
	 *
	 * (grafo em si não precisa ser liberado)
	 * */
	free(grafo->listaAdj);
	grafo->listaAdj = NULL;
	grafo->numVertices = 0;
	grafo->numArestas = 0;
}

//COMPLETO
int verticeDestino(TipoApontador p){
    return p->vdest;
}

//COMPLETO
void imprimeErro(char funcao[], int v, TipoGrafo* grafo){
	fprintf(stderr,"ERRO na chamada da função: %s. Vértice %i é inválido! Deve ser maior que 0 OU menor que o número de %d vértices iniciados!",funcao,v,grafo->numVertices);
}

//COMPLETO
void imprimeErroIniciar(){
	fprintf(stderr,"ERRO na chamada da função de inicialização do grafo! Número de vértices deve ser maior que 0!");
}
