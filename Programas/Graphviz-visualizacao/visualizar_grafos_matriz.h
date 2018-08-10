#include <stdio.h>
#include <stdlib.h>
#include "grafo_matrizadj.h"

void insereAresta(int v1,int v2, TipoPeso peso, TipoGrafo * g){
    g->mat[v1][v2]=peso;
}

void escreveArquivoGraphviz(TipoGrafo* g){

    FILE *f;
    f=fopen("graph.gv","w+");
    int i,j;
    fprintf(f,"digraph g{");

    for(i=1;i<=g->numVertices;i++){

        fprintf(f,"%d;\n",i);
    }

    for(i=1;i<=g->numVertices;i++){
        for(j=1;j<=g->numVertices;j++){
            if(g->mat[i][j]!=AN){
            fprintf(f,"%d ->%d [label=%d];\n",i,j,g->mat[i][j]);}
        }
    }
    fprintf(f,"}");
    fclose(f);

}

