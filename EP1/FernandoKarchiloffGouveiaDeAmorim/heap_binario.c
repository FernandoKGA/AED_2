/*
    Heap Binario por:
    Fernando K. G. A.
    N_USP: 10387644
*/

//heap_binario.c com vetores
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "heap_binario.h"

//Inicializa o Heap.
void inicializaHeap(PONT_HEAP heap, TipoGrafo* grafo){
    //Aloca o vetor do Heap.
    heap->heap = (int*) malloc(sizeof(int)*(grafo->numVertices+1));
    //Atribuicao de valores.
    heap->tamanhoAtual = 0;
    heap->tamanhoHeap = grafo->numVertices;
    //Inicializa o vetor do heap.
    for(int i=0; i <= grafo->numVertices; i++) heap->heap[i] = VERTICE_INEXISTENTE;
}

//Pega o valor do pai.
int pai(int i){
    return (i/2);
}

//Pega o valor do filho a esquerda.
int esquerda(int i){
    return (2*i);
}

//Pega o valor do filho a direita.
int direita(int i){
    return (2*i)+1;
}

//Constroi o Heap totalmente.
void constroiMinHeap(PONT_HEAP heap,double *d){
    int i;
    int metadeTamanho = heap->tamanhoAtual/2;
    for (i=metadeTamanho; i > 0 ;i--){
        //Constroi o heap por nível.
        minHeapify(heap,i,d);
    }
}

//Faz a insercao de vertice no Heap.
bool insereVerticeHeap(PONT_HEAP heap, int vertice){
    int i;
    if (heap->tamanhoAtual == heap->tamanhoHeap) return false;
    //Incrementa tamanho.
    (heap->tamanhoAtual)++;
    i = heap->tamanhoAtual;
    //Coloca o vertice na posicao ja incrementada.
    heap->heap[i] = vertice;
    return true;
}

//Faz a troca entre vertices.
void inverte(PONT_HEAP heap, int vertice, int vertice2){
    //Guarda o que sera trocado temporariamente.
    int temp = heap->heap[vertice];
    //Inverte os vertices.
    heap->heap[vertice] = heap->heap[vertice2];
    //Devolve o anterior ao novo local.
    heap->heap[vertice2] = temp;
}

void minHeapify(PONT_HEAP heap, int pos_heap, double *d){
    /*
        d[i] vetor das distancias.
        heap->heap[i] vetor da prioridade de vertices.
        d[heap->heap[pos_heap]] distancia do maior prioridade.
        d[heap->heap[esquerda(pos_heap)]] distancia do filho a esq.
        d[heap->heap[direita(pos_heap)]] distancia do filho a dir.
    */
    //Define variaveis para executar as comparacoes.
    int esq = heap->tamanhoHeap; //Default.
    int dir = heap->tamanhoHeap; //Default.
    int menor = pos_heap; //Maior prioridade.
    
    //esquerda(pos_heap) <= heap->tamanhoAtual verifica se a posicao eh valida.
    if(esquerda(pos_heap) <= heap->tamanhoAtual) {
        esq = heap->heap[esquerda(pos_heap)];
        //Verifica se o filho a esquerda eh menor que o da pos_heap em dist.
        if(d[esq] < d[heap->heap[menor]]){
            menor = esquerda(pos_heap); //Guarda o valor do vertice menor.
        }
    }
    
    //direita(pos_heap) <= heap->tamanhoAtual verifica se a posicao eh valida.
    if(direita(pos_heap) <= heap->tamanhoAtual) {
        dir = heap->heap[direita(pos_heap)];
        //Verifica se o filho a direita eh menor que o da pos_heap em dist.
        if(d[dir] < d[heap->heap[menor]]) {
            menor = direita(pos_heap); //Guarda o valor do vertice menor.
        }
    }
    
    //Se o vertice for diferente que o menor encontrado, inverte.
    if(heap->heap[menor] != heap->heap[pos_heap]){
        //Executa inversao.
        inverte(heap,pos_heap,menor);
        //Chama o minHeapify para verificar a integridade no menor.
        minHeapify(heap,menor,d); 
    }
}

//Extrai o menor valor do Heap
int extraiMin(PONT_HEAP heap, double *d){
    //Se o tamnhoAtual for menor, gera erro.
    if(heap->tamanhoAtual < 1) printf("Heap invalido. Underflow error.");
    /*
    Se o tamanhoAtual for 1, guarda o prioritario, zera o tamanho
    e insere a primeira posicao como VERTICE_INEXISTENTE,
    por final retorna o prioritario.
    */
    if(heap->tamanhoAtual == 1) {
        int temp = heap->heap[1];
        heap->heap[1] = -1;
        heap->tamanhoAtual = 0;
        return temp;
    }
    //Coloca a prioridade na variavel.
    int min = heap->heap[1];
    //Substitui a prioridade pela ultimo valor existente no heap.
    heap->heap[1] = heap->heap[heap->tamanhoAtual];
    //Diminui o tamanho do heap.
    heap->tamanhoAtual--;
    //Chama o minHeapify para verificar integridade do menor.
    minHeapify(heap,1,d);
    //Retorna a prioridade.
    return min;
}

