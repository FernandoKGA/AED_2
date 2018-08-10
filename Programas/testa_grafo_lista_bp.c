#include "busca_em_profundidade/busca_em_prof_lista.c"

int main()
{
  TipoGrafo g1;
  int numVertices;

  do {
   printf("Digite o número de vértices do grafo\n");
   scanf("%d", &numVertices);
  } while (!inicializaGrafo(&g1, numVertices));

  insereAresta(1,4,4,&g1);
  insereAresta(4,2,4,&g1);
  insereAresta(2,1,4,&g1);
  insereAresta(1,2,4,&g1);
  insereAresta(1,3,4,&g1);
  insereAresta(3,2,4,&g1);
  imprimeGrafo(&g1);
  bool ciclo;
  ciclo = temCicloBP(&g1);
  printf("%s\n", ciclo ? "Tem ciclo." : "Não tem ciclo.");
}
