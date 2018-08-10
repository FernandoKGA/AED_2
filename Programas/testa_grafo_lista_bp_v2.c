#include "busca_em_profundidade/busca_em_prof_lista_v2.c"

int main()
{
  TipoGrafo g1;
  int numVertices;

  do {
   printf("Digite o número de vértices do grafo\n");
   scanf("%d", &numVertices);
  } while (!inicializaGrafo(&g1, numVertices));
  insereAresta(1,6,4,&g1);
  insereAresta(1,4,4,&g1);
  insereAresta(1,3,4,&g1);
  insereAresta(1,2,4,&g1); 
  insereAresta(3,5,4,&g1);
  insereAresta(3,4,4,&g1);
  insereAresta(2,3,4,&g1);
  insereAresta(6,7,4,&g1);
  insereAresta(6,5,4,&g1);
  insereAresta(5,7,4,&g1);
  insereAresta(7,9,4,&g1);
  insereAresta(7,8,4,&g1);
  insereAresta(8,9,4,&g1);
  insereAresta(10,7,4,&g1);
  imprimeGrafo(&g1);
  ordenacaoTopologica(&g1);
}
