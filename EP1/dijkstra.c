//dijkstra.c com vetores
#include "heap_binario.h"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

//Inicia os arranjos
void iniciaSingleSource(TipoGrafo* grafo, double *d, int *ant){
    for(int i=0; i <= grafo->numVertices; i++){
        d[i] = DBL_MAX;  //Valor MAX Double
        ant[i] = VERTICE_INEXISTENTE;   //Antecessor invalido
    }
}

//Funcao de relaxamento
void relaxamento(int v, int u, TipoGrafo* grafo, double *d, int *ant){
    double peso;
    printf("vertice: %d\n",v);
    printf("d[%d] do vertice: %f\n",v,d[v]);
    printf("adj de %d: %d\n",v,u);
    printf("d[%d] do adj: %f\n",u,d[u]);
    if(d[u] > (d[v] + (peso = obtemPesoAresta(v,u,grafo)))){  //Se a distancia de ate u eh maior que somando v + aresta
        printf("peso da aresta entre %d e %d: %f\n",v,u,peso);
        d[u] = d[v] + peso;   //Substitui o valor para um novo
        printf("d[%d]: %f\n",u,d[u]);
        ant[u] = v;   //Coloca o antecessor
        printf("ant[%d]: %d\n",u,v);
    }
}

void insereVerticesNoHeap(TipoGrafo * grafo, PONT_HEAP heap, int s){
    //Insere a origem
    insereVerticeHeap(heap,s);
    printf("inseri a origem\n");
    //Insere os outros vertices
    for(int i=1; i <= grafo->numVertices; i++){
        if(i != s)  insereVerticeHeap(heap,i);
    }
}

//Algoritmo
void dijkstra(TipoGrafo* grafo, PONT_HEAP heap, int s, double *d, int *ant){
    
    //Inicializa Distancia e Antecessor
    iniciaSingleSource(grafo,d,ant);
    printf("inicializei os arranjos\n");
    //Inicializa distancia origem
    d[s] = 0;
    printf("vertice ori: %d\n",s);
    printf("valor vori: %f\n",d[s]);
    //Inicializa Heap(Q) com todos os vertices
    insereVerticesNoHeap(grafo,heap,s);
    printf("inseri os vertices\n");
    //Monta o heap
    constroiMinHeap(heap,d);
    printf("Construi o heap\n");
    for(int i=1;i <= heap->tamanhoHeap;i++)  printf("first heap: %d\n",heap->heap[i]);
    //Cria variaveis para os vertices
    int u,v;
    TipoApontador atual = NULL;
    //Loop para executar o algoritmo
    printf("Entrando while do algo\n");
    
    while(heap->heap[1] != VERTICE_INEXISTENTE){ //Enquanto nao retirar todos
        printf("prioritario: %d\n",heap->heap[1]);
        //Remove v de Q tal que d[v] eh minimo (vertice de maior prioridade)
        v = heap->heap[1];
        printf("Vertice extraido: %d\n", v);
        //Coloca o primeiro adjacente
        atual = primeiroListaAdj(v,grafo);
        if(atual){
            printf("adj atual: %d\n",atual->vdest);
        }
        //Para cada vertice adjacente u de v faca   //usar proxListaAdj para att
        while(atual){
            relaxamento(v,atual->vdest,grafo,d,ant);
            printf("terminou relaxar\n");
            atual = proxListaAdj(v,grafo,atual);
        }
        printf("vou extrair\n");
        v = extraiMin(heap,d);
    }

}

int main(int argc, char *argv[]){
    //Cria ponteiro para o arquivo
    FILE *fp;

    //Cria as estruturas
    TipoGrafo grafo;
    HEAP heap;
    //argv[0] eh o argc
    printf("%s\n",argv[1]);
    printf("%s\n",argv[2]);
    //Abre o arquivo que se recebeu como paramentro
    fp = fopen(argv[1],"r");
    
    if(!fp){
        printf("Arquivo nao encontrado...\n");
        printf("Ele se encontra no mesmo diretorio?\n");
        printf("Voce digitou o nome corretamente?");
    }
    else{
        // s é o vertice origem
        int s;
        int result;
        if((result = fscanf(fp,"%i\n",&s)) != EOF){
            printf("Origem: %i\n",s);
        }
        if(result == EOF){
            printf("Erro na leitura do vertice origem.");
            return 1;
        }
        // n e m são o numero de vértice e arestas
        int n,m;
        if((result = fscanf(fp,"%i %i\n",&n,&m)) != EOF){
            printf("N_vertices:%i N_arestas: %i\n",n,m);
        }
        if(result == EOF){
            printf("Erro na leitura de vertices e arestas.");
            return 1;
        }

        //Inicializacao do grafo
        inicializaGrafo(&grafo,n);
        printf("grafo inicializado\n");
        
        //Insere arestas
        // oi di custoi são respec. origem, destino, custo da aresta em double para custo e int para outros.
        int o,dest,custo;
        for(int i=1;i <= m;i++){
            if((result = fscanf(fp,"%i %i %d\n", &o, &dest, &custo)) != EOF){
                if(custo >= 0){
                    printf("%i %i %d\n", o, dest, custo);
                    insereAresta(o,dest,custo,&grafo);
                    printf("inseri a aresta\n");
                }
            }
            if(result == EOF){
                printf("Erro de leitura em linha.");
                return 1;
            }
        }
        printf("terminei o for de inserção\n");
        //Fecha arquivo que estava sendo utilizado.
        fclose(fp);
        
        //Inicializa Heap
        printf("vou iniciar heap\n");
        inicializaHeap(&heap, &grafo);
        printf("inicializouHeap\n");
        //Aloca os arranjos de distancia e antecessor
        double *d = (double*) malloc(sizeof(double)*(grafo.numVertices+1));
        int *ant = (int*) malloc(sizeof(int)*(grafo.numVertices+1));
        printf("Aloquei os arranjos de dist e ant\n");

        //Executa o Dijkstra
        printf("Entrando no dijkstra\n");
        dijkstra(&grafo, &heap, s, d, ant);
        printf("Saindo do dijkstra\n");
        
        //impressao
        //vi di antecessor, qual o vertice, a distancia da origem, e o seu antecessor 
        fp = fopen(argv[2],"w+");
        if(fp == NULL){
            printf("Nao foi possivel criar o arquivo.");
            return 1;
        }
        for(int i=1;i <= n;i++){
            if(d[i] == DBL_MAX){
                result = fprintf(fp,"%d %.2e %d\n",i,d[i],ant[i]);
                printf("%d %.2e %d\n",i,d[i],ant[i]);
                if(result == EOF){
                    printf("Erro na gravação da linha");
                    return 1;
                }
            }
            else{
                result = fprintf(fp,"%d %f %d\n",i,d[i],ant[i]);
                printf("%d %f %d\n",i,d[i],ant[i]);
                if(result == EOF){
                    printf("Erro na gravação da linha");
                    return 1;
                }
            }
        }
    }
}