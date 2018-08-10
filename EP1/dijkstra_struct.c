#include "heap_binario.c"
#include <float.h>
#include <stdio.h>

//dijkstra.c

//Inicia os arranjos
void iniciaSingleSource(TipoGrafo* grafo, double *d, int *ant){
    for(int i=1; i < grafo->numVertices; i++){
        d[i] = DBL_MAX;
        ant[i] = -1;
    }
}

//Funcao de relaxamento
void relaxamento(int u, int v, TipoGrafo* grafo, double *d, int *ant){
    if(d[u] > (d[v] + obtemPesoAresta(v,u,grafo))){  //Se a distancia de ate u eh maior que somando v + aresta
        d[u] = d[v] + obtemPesoAresta(v,u,grafo);   //Substitui o valor para um novo
        ant[u] = v;   //Coloca o antecessor
    }
}

insereVerticesNoHeap(TipoGrafo * grafo, PONT_HEAP HEAP){

}

//Algoritmo
void dijkstra(TipoGrafo* grafo, PONT_HEAP heap, int s){
    //Aloca os arranjos de distancia e antecessor
    double *d = (double*) malloc(sizeof(double)*(grafo->numVertices+1));
    int *ant = (int*) malloc(sizeof(int)*(grafo->numVertices+1));
    //Inicializa Distancia e Antecessor
    int u,v;
    iniciaSingleSource(grafo,d,ant);
    d[s] = 0;
    //Inicializa Heap(Q) com todos os vertices

    /*while(){ //Enquanto Q não estiver vazio  //usar proxListaAdj
        //remove v de Q tal que d[v] eh mínimo (vertice de maior prioridade)
        //Para cada vertice adjacente u de v faca
        relaxamento(u,v,grafo,d,ant);
    }*/

}

int main(){
    //Cria as estruturas
    TipoGrafo grafo;
    HEAP heap;
    // s é o vertice origem
    // n e m são o numero de vértice e arestas
    // oi di custoi são respec. origem, destino, custo da aresta em double para custo e int para outros.
    int s=0;

    dijkstra(&grafo, &heap, s);
    
    //impressao
    //vi di antecessor, qual o vertice, a distancia da origem, e o seu antecessor 

}