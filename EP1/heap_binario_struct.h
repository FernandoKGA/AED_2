//heap_binario_struct.h
#include "grafo_listaadj.h"

typedef struct{
    int vertice;
    TipoPeso distanciaOrigem;
}NO, * PONT_NO;

typedef struct aux{
    PONT_NO * heap;
    int tamanhoAtual;
    int tamanhoHeap;
}HEAP, * PONT_HEAP;

bool insereVerticeHeap(PONT_HEAP heap, PONT_NO vertice);