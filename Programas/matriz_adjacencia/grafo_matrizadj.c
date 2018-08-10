#include <stdio.h>
#include "grafo_matrizadj.h"

bool inicializaGrafo(TipoGrafo* grafo, int nv){
	int i, j;
	if(nv > MAXNUMVERTICES){
		imprimeErroIniciar();
		return false;
	}
	if(nv <= 0){
		imprimeErroIniciar();
		return false;
	}
	grafo->numVertices = nv;
	grafo->numArestas = 0;
	for(i=1; i <= grafo->numVertices;i++){
		for(j=1; j <= grafo->numVertices;j++){
			grafo->mat[i][j]= AN;
		}
	}
	return true;
}

int obtemNrVertices(TipoGrafo* grafo){
	return grafo->numVertices;
}

int obtemNrArestas(TipoGrafo* grafo){
	return grafo->numArestas;
}

bool verificaValidadeVertice(int v, TipoGrafo *grafo){
	if(v <= 0) return false;
	if(v >= grafo->numVertices) return false;
	return true;
}

void insereAresta(int v1, int v2, TipoPeso peso, TipoGrafo *grafo){
	char funcao[] = "insereAresta";
	if(!verificaValidadeVertice(v1,grafo)){
		imprimeErro(funcao,v1,grafo);
	}
	else{
	    if(!verificaValidadeVertice(v2,grafo)){
	    	imprimeErro(funcao,v2,grafo);
	    }
	    else{
	    	grafo->mat[v1][v2] = peso;
		grafo->numArestas++;
	    }
	}
}

bool existeAresta(int v1, int v2, TipoGrafo *grafo){
	char funcao[] = "existeAresta";
	if(!verificaValidadeVertice(v1,grafo)){
	    imprimeErro(funcao,v1,grafo);
	    return false;
	}
	else{
	    if(!verificaValidadeVertice(v2,grafo)){
	    	imprimeErro(funcao,v2,grafo);
		return false;
	    }
	    else{
	    	if(grafo->mat[v1][v2]!= AN) return true;
	    }
	}
	return false;
}

TipoPeso obtemPesoAresta(int v1, int v2, TipoGrafo *grafo){
	if(existeAresta(v1,v2,grafo)){
	    return grafo->mat[v1][v2];
	}
	return AN;
}

bool removeArestaObtendoPeso(int v1, int v2, TipoPeso* peso, TipoGrafo *grafo){
	if(existeAresta(v1,v2,grafo)){
	    *peso = grafo->mat[v1][v2];
	    grafo->mat[v1][v2] = AN;
	    grafo->numArestas--;
	    return true;
	}
	return false;
}

bool removeAresta(int v1, int v2, TipoGrafo *grafo){
	if(existeAresta(v1,v2,grafo)){
	    grafo->mat[v1][v2] = AN;
	    grafo->numArestas--;
	    return true;
	}
	return false;
}

bool listaAdjVazia(int v, TipoGrafo* grafo){
	if(!verificaValidadeVertice(v,grafo)){
	    char funcao[] = "listaAdjVazia";
	    imprimeErro(funcao,v,grafo);
	    return false;
	}
	else{
	    int i;
	    for(i=1;i < grafo->numVertices;i++){
	    	if(grafo->mat[v][i] != AN) return false;
	    }
	}
	return false;
}

TipoApontador primeiroListaAdj(int v, TipoGrafo* grafo){
	if(!verificaValidadeVertice(v,grafo)){
	    char funcao[] = "primeiroListaAdj";
	    imprimeErro(funcao,v,grafo);
	    return VERTICE_INVALIDO;
	}
	else{
	    int i;
	    for(i=1;i < grafo->numVertices;i++){
	    	if(grafo->mat[v][i] != AN){
		    TipoApontador var = grafo->mat[v][i];
		    return var;
		}
	    }
	}
	return VERTICE_INVALIDO;
}

TipoApontador proxListaAdj(int v, TipoGrafo* grafo, TipoApontador atual){
	if(!verificaValidadeVertice(v,grafo)){
	    char funcao[] = "proxListaAdj";
	    imprimeErro(funcao,v,grafo);
	}
	else{
	    for(++atual;atual < grafo->numVertices; atual++){
	    	if(grafo->mat[v][atual] != AN){
		    TipoApontador var = grafo->mat[v][atual];
		    return var;
		}
	    }
	}
	return VERTICE_INVALIDO;
}

void imprimeGrafo(TipoGrafo* grafo){
	int i,j;
	printf("   ");
	for(i=1; i <= grafo->numVertices; i++)	printf("%3d",i);
	printf("\n");

	for(i=1;i <= grafo->numVertices; i++){
	    printf("%3d",i);
	    for(j=1;j <= grafo->numVertices; j++){
	    	printf("%3d",grafo->mat[i][j]);
	    }
	    printf("\n");
	}
}

void liberaGrafo(TipoGrafo* grafo){}

void imprimeErro(char funcao[], int v, TipoGrafo* grafo){
	fprintf(stderr,"ERRO na chamada da função: %s. Vértice %i é inválido! Deve ser maior que 0 OU menor que o número de %d vértices iniciados!",funcao,v,grafo->numVertices);
}

void imprimeErroIniciar(){
	fprintf(stderr,"ERRO na chamada da função de inicialização da matriz! Número de vértices deve ser maior que 0 e menor que o número máximo de vértices: %i",MAXNUMVERTICES);
}
