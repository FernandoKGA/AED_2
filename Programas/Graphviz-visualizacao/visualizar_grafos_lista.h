#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafo_listaadj.h"

bool inicializaGrafo(TipoGrafo *g, int nv){
    if(nv<=0){
        printf("Erro ao inicializar");
    }
    else{
        g->listaAdj = (TipoApontador*) calloc(nv+1,sizeof(TipoApontador));
	    g->numVertices = nv;
	    g->numArestas = 0;
	    return true;
    }
    return false;
}


void insereAresta(int v1,int v2, TipoPeso peso, TipoGrafo * g){
    TipoApontador p= g->listaAdj[v1];
    TipoApontador q = (TipoAresta*) malloc(sizeof(TipoAresta));
    q->prox=NULL;
    q->vdest=v2;
    q->peso=peso;
    if(!p){g->listaAdj[v1]=q;}
    else{
        q->prox=p;
        g->listaAdj[v1]=q;
    }

}


void escreveArquivoGraphviz(TipoGrafo* g){
    FILE* f= fopen("grafo.gv","w+");
    fprintf(f,"digraph G{\n");
    int i,j;
    for(j=1;j<=g->numVertices;j++){
        fprintf(f,"%d;\n",j);
    }
    for(i=1;i<=g->numVertices;i++){
        TipoApontador p= g->listaAdj[i];
        while(p){
            fprintf(f,"%d -> %d [label=%d];\n",i,p->vdest,p->peso);
            p=p->prox;

        }
    }
    fprintf(f,"}");
    fclose(f);

}

