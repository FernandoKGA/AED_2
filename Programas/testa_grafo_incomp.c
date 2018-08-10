#include "matriz_adjacencia/grafo_matrizadj_incomp.h"
//#include "lista_adjacencia/grafo_listaadj.h"
#include <stdio.h>

int main()
{
  TipoGrafo g1;
  int numVertices;
  
  do {
   printf("Digite o número de vértices do grafo\n");
   scanf("%d", &numVertices);
  } while (!inicializaGrafo(&g1, numVertices));

  // ou teste diretamente valores como abaixo:
  //inicializaGrafo(&g1, 0);
  //inicializaGrafo(&g1, -2);
  //inicializaGrafo(&g1, 50000);
  //inicializaGrafo(&g1, 5);

  insereAresta(3,4,4,&g1);
  imprimeGrafo(&g1);
  TipoPeso p;
  removeAresta(3,4,&p,&g1);
  printf("%d\n",p);
  imprimeGrafo(&g1);
}
