//heap_binario.h
#include "grafo_listaadj.h"

#define VERTICE_INEXISTENTE -1

typedef struct aux{
    int * heap;
    int tamanhoAtual;
    int tamanhoHeap;
}HEAP, * PONT_HEAP;

void inicializaHeap(PONT_HEAP heap, TipoGrafo* grafo);

int pai(int i);

int esquerda(int i);

int direita(int i);

void constroiMinHeap(PONT_HEAP heap,double *d);

bool insereVerticeHeap(PONT_HEAP heap, int vertice);

void inverte(PONT_HEAP heap, int vertice, int vertice2);

void minHeapify(PONT_HEAP heap, int pos_heap, double *d);

int extraiMin(PONT_HEAP heap, double *d);