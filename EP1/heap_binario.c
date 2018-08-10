//heap_binario.c com vetores
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "heap_binario.h"

void inicializaHeap(PONT_HEAP heap, TipoGrafo* grafo){
    heap->heap = (int*) malloc(sizeof(int)*(grafo->numVertices+1));
    heap->tamanhoAtual = 0;
    heap->tamanhoHeap = grafo->numVertices;
    for(int i=0; i <= grafo->numVertices; i++) heap->heap[i] = VERTICE_INEXISTENTE;
}

int pai(int i){
    return (i/2);
}

int esquerda(int i){
    return (2*i);
}

int direita(int i){
    return (2*i)+1;
}

//Constroi o Heap totalmente
void constroiMinHeap(PONT_HEAP heap,double *d){
    int i;
    int metadeTamanho = heap->tamanhoAtual/2;
    for (i=metadeTamanho; i > 0 ;i--){
        printf("pos_heap no for: %d\n",i);
        minHeapify(heap,i,d);
    }
}

bool insereVerticeHeap(PONT_HEAP heap, int vertice){
    int i;
    if (heap->tamanhoAtual == heap->tamanhoHeap) return false;
    (heap->tamanhoAtual)++;
    i = heap->tamanhoAtual;
    printf("vertice: %i\n",i);
    heap->heap[i] = vertice;
    return true;
}

//Faz a troca entre vertices
void inverte(PONT_HEAP heap, int vertice, int vertice2){
    int temp = heap->heap[vertice];
    printf("heap->heap[vertice]: %d\n",temp);
    printf("heap->heap[vertice2]: %d\n",heap->heap[vertice2]);
    heap->heap[vertice] = heap->heap[vertice2];
    printf("heap->heap[vertice1]: %d\n",heap->heap[vertice]);
    heap->heap[vertice2] = temp;
    printf("heap->heap[vertice2]: %d\n",heap->heap[vertice2]);
    printf("inverteu\n");
}

void minHeapify(PONT_HEAP heap, int pos_heap, double *d){
    printf("minHeapify\n");
    /*
        d[i] vetor das distancias
        heap->heap[i] vetor da prioridade de vertices
        d[heap->heap[pos_heap]] distancia do maior priori
        d[heap->heap[esquerda(pos_heap)]] distancia do filho a esq
        d[heap->heap[direita(pos_heap)]] distancia do filho a dir
    */
    printf("pos_heap: %d\n",pos_heap);
    int esq = heap->tamanhoHeap;
    int dir = heap->tamanhoHeap;
    int menor = pos_heap; //Maior priori
    
    //esquerda(pos_heap) <= heap->tamanhoAtual verifica se a posicao eh valida
    printf("esquerda da pos: %d\n",heap->heap[esquerda(pos_heap)]);
    if(esquerda(pos_heap) <= heap->tamanhoAtual) {
        esq = heap->heap[esquerda(pos_heap)];
        printf("dist da pos: %f\n",d[heap->heap[pos_heap]]);
        printf("dist esquerda da pos: %f\n",d[esq]);
        printf("dist esquerda da pos(heap): %f\n",d[heap->heap[esquerda(pos_heap)]]);
        //Verifica se o filho a esquerda eh menor que o da pos_heap
        if((d[esq] < d[heap->heap[menor]])){
            menor = esquerda(pos_heap);
            printf("esquerda eh menor\n");
        }
    }
    
    //direita(pos_heap) <= heap->tamanhoAtual verifica se a posicao eh valida
    printf("direita da pos: %d\n",heap->heap[direita(pos_heap)]);
    if(direita(pos_heap) <= heap->tamanhoAtual) {
        dir = heap->heap[direita(pos_heap)];
        printf("dist direita da pos(heap): %f\n",d[heap->heap[direita(pos_heap)]]);
        printf("dist direita da pos(heap(heap)): %f\n",d[heap->heap[dir]]);
        printf("dist direita da pos: %f\n",d[dir]);
        //Verifica se o filho a direita eh menor que o da pos_heap
        if((d[dir] < d[heap->heap[menor]])) {
            menor = direita(pos_heap);
            printf("direita eh menor\n");
        }
    }
    /*
    printf("vertice priori: %d\n",heap->heap[pos_heap]);
    printf("esquerda: %d\n",heap->heap[esq]);
    printf("direita: %d\n",heap->heap[dir]);

    printf("vertice: %d d[%d]: %f\n",heap->heap[pos_heap],
                                    heap->heap[pos_heap],d[heap->heap[pos_heap]]);
    printf("vertice: %d d[%d]: %f\n",heap->heap[esq],
                                    heap->heap[esq],d[heap->heap[esq]]);
    printf("vertice: %d d[%d]: %f\n",heap->heap[dir],
                                heap->heap[dir],d[heap->heap[dir]]);
    */    
    
    
    //Se o vertice for diferente que o menor encontrado, inverte
    if(heap->heap[menor] != heap->heap[pos_heap]){
        printf("vai inverter\n");
        printf("menor: %d",menor);
        printf("pos_heap: %d",pos_heap);
        inverte(heap,pos_heap,menor); //Inverte
        printf("ouve inversao\n");
        minHeapify(heap,menor,d);  //Chama o minHeapify para verificar 
                                   //a integridade no menor
        printf("chamou heapify\n");
    }
}

//Extrai o menor valor do Heap
int extraiMin(PONT_HEAP heap, double *d){
    if(heap->tamanhoAtual < 1) fprintf(stderr,"Heap invalido. Underflow error.");
    if(heap->tamanhoAtual == 1) {
        int temp = heap->heap[1];
        heap->heap[1] = -1;
        heap->tamanhoAtual = 0;
        return temp;
    }
    int min = heap->heap[1]; //Coloca o menor em min
    printf("min: %d\n",min);
    heap->heap[1] = heap->heap[heap->tamanhoAtual]; /* A primeira posicao
    recebe do ultimo vertice do heap */
    printf("novo min: %d\n",heap->heap[1]);
    heap->tamanhoAtual--;
    minHeapify(heap,1,d);
    /*if(d[direita(1)] < d[esquerda(1)]) heap->heap[1] = heap->heap[direita(1)];
    else heap->heap[1] = heap->heap[esquerda(1)];*/
    return min;
}

