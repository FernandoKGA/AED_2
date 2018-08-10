#include <stdio.h>
#include <stdlib.h>
#include "visualizar_grafos_matriz.h"



int main(){

	TipoGrafo g;
	inicializaGrafo(&g,5);
	insereAresta(1,2,3,&g);
	escreveArquivoGraphviz(&g);
	return 0;

}