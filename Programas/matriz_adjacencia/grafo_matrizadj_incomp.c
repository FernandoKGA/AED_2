#include <stdio.h>
#include "grafo_matrizadj_incomp.h"

/*
  InicializaGrafo(TipoGrafo* grafo, int nv): Inicializa um grafo com nv vertices
  Vertices vao de 1 a nv.
  Preenche as celulas com AN (representando ausencia de aresta)
  Retorna true se inicializou com sucesso e false caso contrario
*/ 
bool inicializaGrafo(TipoGrafo* grafo, int nv)
{ int i , j ;
  if (nv > MAXNUMVERTICES) {
    fprintf(stderr, "ERRO na chamada de inicializaGrafo: Numero de vertices maior que o maximo permitido DE %d.\n", MAXNUMVERTICES);
    return false;
  }
  if (nv <= 0) {
    fprintf(stderr, "ERRO na chamada de inicializaGrafo: Numero de vertices de ser positivo.\n");
    return false;
  }
  grafo->numVertices = nv;
  grafo->numArestas = 0;
  for ( i = 0; i <= grafo->numVertices; i++)
    { for ( j = 0; j <= grafo->numVertices; j ++)
	grafo->mat[i][j] = AN;
    }
  return true;
}

/*
    void imprimeGrafo(TipoGrafo* grafo):
    Imprime a matriz de adjacencia do grafo.
    Assuma que cada vértice e cada peso de aresta são inteiros de até 2 dígitos.
*/
void imprimeGrafo(TipoGrafo* grafo){
  int i, j;
  printf("   ");
  /* imprime linha de vertices */
  for ( i = 1; i <= grafo->numVertices; i++) printf("%3d", i);
  printf("\n");
    
  for ( i = 1; i <= grafo->numVertices; i++){
    printf("%3d", i); /* imprime coluna de vertices */
    for ( j = 1; j <= grafo->numVertices; j ++)
      printf("%3d", grafo->mat[i][j]);
    printf("\n");
  }
}

void insereAresta(int v1, int v2, TipoPeso peso, TipoGrafo* grafo){
	if(v1 != v2){
	   if(v1 <= 0){
	      fprintf(stderr,"ERRO na chamada de insereAresta: vértice 1 deve ser positivo.\n");
	   } 
	   else{
		if(v1 >= grafo->numVertices){
		   fprintf(stderr,"ERRO na chamada de insereAresta: vértice 1 é um número maior que o número de vértices do grafo: %d\n",grafo->numVertices);
		}
		else{
		    if(v2 <= 0){
		       fprintf(stderr,"ERRO na chamada de insereAresta: vértice 2 deve ser positivo.\n");
		    }
		    else{
		       if(v2 >= grafo->numVertices){
		          fprintf(stderr,"ERRO na chamada de insereAresta: vértice 2 é um número maior que o de vértices do grafo: %d\n",grafo->numVertices);
		       }
		       else{
			 grafo->mat[v1][v2] = peso;
			 grafo->numArestas++;
		       }
		    }
		}
	    }
	} 
	else{
	    fprintf(stderr,"ERRO na chamada de insereAresta: tentando inserir aresta do/para o mesmo vértice, ação não permitida!");
	}	
}

bool existeAresta(int v1, int v2, TipoGrafo *grafo){
	if(v1 != v2){
	   if(v1 <= 0){
	      fprintf(stderr,"ERRO na chamada de existeAresta: vértice 1 deve ser positivo.\n");
	   } 
	   else{
		if(v1 >= grafo->numVertices){
		   fprintf(stderr,"ERRO na chamada de existeAresta: vértice 1 é um número maior que o número de vértices do grafo: %d\n",grafo->numVertices);
		}
		else{
		    if(v2 <= 0){
		       fprintf(stderr,"ERRO na chamada de existeAresta: vértice 2 deve ser positivo.\n");
		    }
		    else{
		       if(v2 >= grafo->numVertices){
		          fprintf(stderr,"ERRO na chamada de existeAresta: vértice 2 é um número maior que o de vértices do grafo: %d\n",grafo->numVertices);
		       }
		       else{
			 if(grafo->mat[v1][v2] != AN) return true;
		       }
		    }
		}
	    }
	}
	else{
	  fprintf(stderr,"ERRO na chamada de existeAresta: tentando verificar se existe aresta para o mesmo vértice.");
	}
	return false;
}

bool removeAresta(int v1, int v2, TipoPeso* peso, TipoGrafo *grafo){
	if(v1 != v2){
	   if(v1 <= 0){
	      fprintf(stderr,"ERRO na chamada de removeAresta: vértice 1 deve ser positivo.\n");
	   } 
	   else{
		if(v1 >= grafo->numVertices){
		   fprintf(stderr,"ERRO na chamada de removeAresta: vértice 1 é um número maior que o número de vértices do grafo: %d\n",grafo->numVertices);
		}
		else{
		    if(v2 <= 0){
		       fprintf(stderr,"ERRO na chamada de removeAresta: vértice 2 deve ser positivo.\n");
		    }
		    else{
		       if(v2 >= grafo->numVertices){
		          fprintf(stderr,"ERRO na chamada de removeAresta: vértice 2 é um número maior que o de vértices do grafo: %d\n",grafo->numVertices);
		       }
		       else{
			 *peso = grafo->mat[v1][v2];
			 grafo->mat[v1][v2] = AN;
			 grafo->numArestas--;
			 return true;
		       }
		    }
		}
	    }
	} 
	else{
	    fprintf(stderr,"ERRO na chamada de removeAresta: tentando inserir aresta do/para o mesmo vértice, ação não permitida!");
	}
	return false;
}

bool listaAdjVazia(int v, TipoGrafo* grafo){
	if(v <= 0){
	      fprintf(stderr,"ERRO na chamada de listaAdjVazia: vértice 1 deve ser positivo.\n");
        } 
	else{
	  if(v >= grafo->numVertices){
	   fprintf(stderr,"ERRO na chamada de listaAdjVazia: vértice 1 é um número maior que o número de vértices do grafo: %d\n",grafo->numVertices);
	  }
	  else{
	    int i;
	    for(i=1; i < grafo->numVertices; i++){
	      if(grafo->mat[v][i] != AN) return false;
	    }
	  }
	}
	return true;
}

TipoApontador primeiroListaAdj(int v, TipoGrafo* grafo){
	if(v <= 0){
	      fprintf(stderr,"ERRO na chamada de primeiroListaAdj: vértice 1 deve ser positivo.\n");
        } 
	else{
	  if(v >= grafo->numVertices){
	   fprintf(stderr,"ERRO na chamada de primeiroListaAdj: vértice 1 é um número maior que o número de vértices do grafo: %d\n",grafo->numVertices);
	  }
	  else{
	    TipoApontador i;
	    for(i=1;i < grafo->numVertices;i++){
	      if(grafo->mat[v][i] != AN) return i;
	    }
	    return VERTICE_INVALIDO;
	  }
	}
	return VERTICE_INVALIDO;
}

TipoApontador proxListaAdj(int v, TipoGrafo* grafo, TipoApontador atual){
    if(v <= 0){
      fprintf(stderr,"ERRO na chamada de proxListaAdj: vértice 1 deve ser positivo.\n");
    } 
    else{
      if(v >= grafo->numVertices){
	fprintf(stderr,"ERRO na chamada de proxListaAdj: vértice 1 é um número maior que o número de vértices do grafo: %d\n",grafo->numVertices);
      }
      else{
	for(++atual; atual < grafo->numVertices; atual++){
	  if(grafo->mat[v][atual] != AN) return atual;
	}
      }
    }
    return VERTICE_INVALIDO;
}
void liberaGrafo(TipoGrafo* grafo){}  //Por ser estático não faz nada.

/*    IMPLEMENTAR AS DEMAIS ROTINAS DEFINIDAS NO .h   !!!!!!!!!!!!!!!!!!!!!!  */
