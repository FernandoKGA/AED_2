/*
    Algoritmo de Dijkstra por:
    Fernando K. G. A.
    N_USP: 10387644
*/


//dijkstra.c com vetores
#include "heap_binario.h"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

//Inicia os arranjos.
void iniciaSingleSource(TipoGrafo* grafo, double *d, int *ant){
    for(int i=0; i <= grafo->numVertices; i++){
        d[i] = DBL_MAX;  //Valor MAX Double definido em float.h.
        ant[i] = VERTICE_INEXISTENTE;   //Antecessor invalido.
    }
}

//Funcao de relaxamento.
void relaxamento(int v, int u, TipoGrafo* grafo, double *d, int *ant){
    double peso;
    //Se a distancia de ate u eh maior que somando v + aresta.
    if(d[u] > (d[v] + (peso = obtemPesoAresta(v,u,grafo)))){ 
        //Substitui o valor para um novo.
        d[u] = d[v] + peso;
        //Coloca o antecessor.
        ant[u] = v;
    }
}

void insereVerticesNoHeap(TipoGrafo * grafo, PONT_HEAP heap, int s){
    //Insere a origem.
    insereVerticeHeap(heap,s);
    //Insere os outros vertices em ordem.
    for(int i=1; i <= grafo->numVertices; i++){
        //Faz uma comparacao para nao colocar a origem fora da prioridade.
        if(i != s)  insereVerticeHeap(heap,i);
    }
}

//Algoritmo.
void dijkstra(TipoGrafo* grafo, PONT_HEAP heap, int s, double *d, int *ant){
    
    //Inicializa Distancia e Antecessor.
    iniciaSingleSource(grafo,d,ant);

    //Inicializa distancia origem.
    d[s] = 0;
    
    //Inicializa Heap(Q) com todos os vertices.
    insereVerticesNoHeap(grafo,heap,s);

    //Monta o heap.
    constroiMinHeap(heap,d);

    //Cria variaveis para os vertices.
    int u,v;
    TipoApontador atual = NULL;
    
    //Loop para executar o algoritmo
    while(heap->heap[1] != VERTICE_INEXISTENTE){ //Enquanto nao retirar todos.
        //Coloca numa variavel o prioritario.
        v = heap->heap[1];

        //Coloca o primeiro adjacente.
        atual = primeiroListaAdj(v,grafo);

        //Para cada vertice adjacente u de v faca.
        while(atual){
            //Faz o relaxamento da aresta.
            relaxamento(v,atual->vdest,grafo,d,ant);
            //Atualizacao da atual.
            atual = proxListaAdj(v,grafo,atual);
        }
        //Remove v de Q tal que d[v] eh minimo (vertice de maior prioridade).
        v = extraiMin(heap,d);
    }

}

int main(int argc, char *argv[]){
    //Cria ponteiro para o arquivo.
    FILE *fp;

    //Cria as estruturas.
    TipoGrafo grafo;
    HEAP heap;

    //Abre o arquivo que se recebeu como paramentro, argv[1].
    fp = fopen(argv[1],"r");
    
    if(!fp){
        printf("Arquivo nao encontrado...\n");
        printf("Ele se encontra no mesmo diretorio?\n");
        printf("Voce digitou o nome corretamente?");
    }
    else{
        // s e o vertice origem.
        int s;
        int result;
        result = fscanf(fp,"%i\n",&s);
        if(result == EOF){
            printf("Erro na leitura do vertice origem.");
            return 1;
        }

        // n e m sao o numero de vertice e arestas.
        int n,m;
        result = fscanf(fp,"%i %i\n",&n,&m);
        if(result == EOF){
            printf("Erro na leitura de vertices e arestas.");
            return 1;
        }

        //Inicializacao do grafo.
        inicializaGrafo(&grafo,n);
        
        //Insere arestas.
        /*
            oi di custoi são respec. origem, destino, 
            custo da aresta em double para custo e int para outros.
        */
        int o,dest,custo;
        for(int i=1;i <= m;i++){
            if((result = fscanf(fp,"%i %i %d\n", &o, &dest, &custo)) != EOF){
                if(custo >= 0){
                    insereAresta(o,dest,custo,&grafo);
                }
                else{
                    printf("Aresta de custo negativo. Não inserindo");
                }
            }
            if(result == EOF){
                printf("Erro de leitura em linha.");
                return 1;
            }
        }

        //Fecha arquivo que estava sendo utilizado.
        fclose(fp);
        
        //Inicializa Heap.
        inicializaHeap(&heap, &grafo);

        //Aloca os arranjos de distancia e antecessor.
        double *d = (double*) malloc(sizeof(double)*(grafo.numVertices+1));
        int *ant = (int*) malloc(sizeof(int)*(grafo.numVertices+1));

        //Executa o Dijkstra
        dijkstra(&grafo, &heap, s, d, ant);
        
        //Abertura de arquivo para gravacao.
        //vi di antecessor, qual o vertice, a distancia da origem, e o seu antecessor.
        fp = fopen(argv[2],"w+");
        if(fp == NULL){
            printf("Nao foi possivel criar o arquivo.");
            return 1;
        }

        //Gravacao.
        for(int i=1;i <= n;i++){
            //Se o custo for DBL_MAX, grava como tal.
            if(d[i] == DBL_MAX){
                result = fprintf(fp,"%d %.2e %d\n",i,d[i],ant[i]);
                if(result == EOF){
                    printf("Erro na gravação da linha");
                    return 1;
                }
            }
            //Caso contrario, usa gravacao de float.
            else{
                result = fprintf(fp,"%d %f %d\n",i,d[i],ant[i]);
                if(result == EOF){
                    printf("Erro na gravação da linha");
                    return 1;
                }
            }
        }
    }
}