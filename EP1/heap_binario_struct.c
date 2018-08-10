//heap_binario.c
#include <stdbool.h>
#include <malloc.h>
#include "heap_binario.h"
#include "grafo_listaadj.c"

void inicializaHeap(PONT_HEAP heap, TipoGrafo* grafo){
    heap->heap = (PONT_NO*) malloc(sizeof(PONT_NO)*(grafo->numVertices+1));
    int tamanhoAtual = 0;
    int tamanhoHeap = grafo->numVertices+1;
    for(int i=0; i < tamanhoHeap; i++) heap->heap[i] = NULL;
}

int pai(int i){
    return i/2;
}

int esquerdo(int i){
    return (2*i);
}

int direito(int i){
    return (2*i)+1;
}

bool insereVerticeHeap(PONT_HEAP heap, PONT_NO vertice){
  int i;
  PONT_NO temp;
  if (heap->tamanhoAtual == heap->tamanhoHeap) return false;
  (heap->tamanhoAtual)++;
  i = heap->tamanhoAtual;
  printf("%i",i);
  heap->heap[i] = vertice; //Coloca os vertices em ordem do menor(vertice) ao maior
  /*while ((i>1) && (heap->heap[pai(i)]->vertice > heap->heap[i]->vertice)){
    temp = heap->heap[pai(i)];
    heap->heap[pai(i)] = heap->heap[i];
    heap->heap[i] = temp;       
    i = pai(i);
  }*/
  return true;
}

