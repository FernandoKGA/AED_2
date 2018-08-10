#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define nv 5
#define nvp 6

typedef int tipoPeso;

typedef struct s{
int vertice;
struct s* prox;
} NO;

typedef struct tAresta
{
	int vDest;
	tipoPeso peso;
	struct tAresta* prox;
}tipoAresta;

typedef struct{
    int fila[nvp];
    int proxVazio;
} tipoFila;

typedef tipoAresta* tipoApontador;

typedef struct
{
	tipoApontador* listaAdj;
	int numVertices;
	int numArestas;
}tipoGrafo;

bool inicializaGrafo (tipoGrafo* grafo, int nVer)
{
	grafo->numVertices = nVer;
	grafo->numArestas = 0;
	grafo->listaAdj = (tipoApontador*) calloc (nv+1, sizeof(tipoApontador));
	if (grafo->listaAdj == NULL) return false;

	for (int r = 1; r <= nVer; r++)
	{
		grafo->listaAdj[r] = NULL;
	}
	return true;
}

void inicializaFila (tipoFila* f){
    for (int a = 0; a <= nvp; a++) f->fila[a] = -1;
    f->proxVazio = 1;
}

void addFila (tipoFila* f, int v){
    f->fila[f->proxVazio] = v;
    f->proxVazio++;
}

int delFila (tipoFila* f){
    int resposta = f->fila[1];
    for (int a = 1; a <= f->proxVazio; a++){
        f->fila[a] = f->fila[a+1];
    }
    f->proxVazio--;
    return resposta;
}

void insereAresta (tipoGrafo* grafo, int v1, int v2, int p)
{
	tipoAresta* ta = (tipoAresta*) malloc (sizeof(tipoAresta));
	ta->vDest = v2;
	ta->peso = p;
	grafo->numArestas++;

	tipoApontador ap = grafo->listaAdj[v1];
	grafo->listaAdj[v1] = ta;
	ta->prox = ap;
}

bool existeAresta (tipoGrafo* g, int a, int z)
{
    if ((a <= 0) || (a > nv)) return false;
    tipoApontador ap = g->listaAdj[a];
    while (ap)
    {
        if (ap->vDest == z) return true;
        ap = ap->prox;
    }
    return false;
}

bool removeAresta (tipoGrafo* g, int a, int z)
{
    if ((a <= 0) || (a > nv)) return false;
    tipoApontador ap = g->listaAdj[a];
    tipoApontador ant = g->listaAdj[a];
    while (ap)
    {
        if (ap->vDest == z)
        {
        	if (g->listaAdj[a] == ap) g->listaAdj[a] = ap->prox;
        	else ant->prox = ap->prox;
            free (ap);
            g->numArestas--;
            return true;
        }
        ant = ap;
        ap = ap->prox;
    }
    return false;
}

void imprimeGrafo (tipoGrafo* g)
{
	for (int a=1; a <= nv; a++)
	{
		printf("v[%d]: ",a);
		if (g->listaAdj[a])
        {
            tipoApontador ap = g->listaAdj[a];
            while (ap)
            {
 	       	    printf("{%d (p=%d)} ", ap->vDest, ap->peso);
       			ap = ap->prox;
            }
        }
        printf("\n");
	}
	printf("\n");
}

bool listaAdjVazia (tipoGrafo* g, int x)
{
    if (g->listaAdj[x]) return false;
    return true;
}

tipoApontador proxListaAdj (tipoGrafo* g, tipoAresta* ta)
{
    if (!ta->prox) return NULL;
    tipoApontador ap = ta;
    return ap;
}




void visitaBP (int v, tipoGrafo* g, int* tempo, int cor[], int tdesc[], int tterm[], int antecessor[]){
    printf("\nv=%d ", v);
    cor[v] = 1;
    tdesc[v] = (*tempo)++;
    tipoApontador ap = g->listaAdj[v];
    while (ap){
            printf("(ap->vDest=%d, cor[ap->vDest]=%d) ", ap->vDest, cor[ap->vDest]);
        if (cor[ap->vDest] == 0){
            antecessor[ap->vDest] = v;
            printf("%d->%d ", v, ap->vDest);
            visitaBP(ap->vDest, g, tempo, cor, tdesc, tterm, antecessor);
        }
        ap = ap->prox;
    }
    tterm[v] = (*tempo)++;
    cor[v] = 2;
}

void buscaProfundidade (tipoGrafo* g){
    int cor[nvp];// B = 0; C = 1; P = 2
    int tdesc[nvp];
    int tterm[nvp];
    int antecessor[nvp];
    int tempo = 0;

    for (int a = 0; a <= nvp; a++){
        cor[a] = 0;
        tdesc[a] = 0;
        tterm[a] = 0;
        antecessor[a] = -1;
    }
    for (int b = 1; b <= nv; b++){
        if (cor[b] == 0) visitaBP(b, g, &tempo, cor, tdesc, tterm, antecessor);
    }
}



void printaAnteriores(int v, int ant[]){
    int aux = v;
    int p = 0;
    while (p != v){
        printf("%d <- ", v);
        if (v == ant[v]){
    		printf("%d", v);
    		break;
		}
        v = ant[v];
        p = aux;
    }
	printf("%d", v);
}

void printaAnteriores_safe(int v, int ant[]){
    int aux = v;
    int p = 0;
    int x = 0;
    while ((p != v)&&(x <= 20)){
        printf("%d <- ", v);
        if (v == ant[v]){
    		printf("%d.", v);
    		break;
		}
        v = ant[v];
        p = aux;
        x++;
    }
	printf("%d", v);
}

void visitaAC (int v, tipoGrafo* g, int cor[], int antecessor[]){
    cor[v] = 1;
    tipoApontador ap = g->listaAdj[v];
    while (ap){
        if (cor[ap->vDest] == 0){
            antecessor[ap->vDest] = v;
            visitaAC(ap->vDest, g, cor, antecessor);
        }else if ((cor[antecessor[v]]==1)&&(cor[ap->vDest]==1)&&(v != ap->vDest)){
            antecessor[ap->vDest] = v;
            printf("\nCiclo encontrado (%d,%d):\n",ap->vDest, v);
            printf("ant[%d]=%d\n", v, antecessor[v]);
            printaAnteriores_safe(ap->vDest, antecessor);
            }
        ap = ap->prox;
    }
    cor[v] = 1;
}

void achaCiclo (tipoGrafo* g){
    int cor[nvp];// B = 0; C = 1; P = 2
    int antecessor[nvp];

    for (int a = 0; a <= nvp; a++){
        cor[a] = 0;
        antecessor[a] = -1;
    }
    for (int b = 1; b <= nv; b++){
        tipoApontador ap = g->listaAdj[b];
        while(ap){
        	if (ap->vDest == b){
            printf("\nCiclo encontrado (SL):\n%d <- %d", b, b);
			}
			ap = ap->prox;
		}
    }
    for (int c = 1; c <= nv; c++){
        if (cor[c]==0)visitaAC(c, g, cor, antecessor);
    }
}

void visitaT (int v, tipoGrafo* g, int* tempo, int cor[], int tdesc[], int tterm[], int antecessor[], NO* i){
    cor[v] = 1;
    tdesc[v] = (*tempo)++;
    tipoApontador ap = g->listaAdj[v];
    while (ap){
        if (cor[ap->vDest] == 0){
            antecessor[ap->vDest] = v;
            visitaT(ap->vDest, g, tempo, cor, tdesc, tterm, antecessor, i);
        }
        ap = ap->prox;
    }
    tterm[v] = (*tempo)++;
    cor[v] = 2;
    NO* p = (NO*) malloc (sizeof(NO));
    p->vertice = v;
    p->prox = i->prox;
    i->prox = p;
}

void topologia (tipoGrafo* g, NO* i){

    int cor[nvp];// B = 0; C = 1; P = 2
    int tdesc[nvp];
    int tterm[nvp];
    int antecessor[nvp];
    int tempo = 0;

    for (int a = 0; a <= nvp; a++){
        cor[a] = 0;
        tdesc[a] = 0;
        tterm[a] = 0;
        antecessor[a] = -1;
    }
    for (int b = 1; b <= nv; b++){
        if (cor[b] == 0) visitaT(b, g, &tempo, cor, tdesc, tterm, antecessor, i);
    }
}

void printaLista (NO* n){
    NO* p = n;
    printf(" Lista: -");
    while (p){
        printf ("%d-", p->vertice);
        p = p->prox;
    }
}

void printaCor (int cor[])
{
    printf("\n");
    for (int i = 1; i <= nv; i++){
        printf("[%d] = %d\n", i, cor[i]);
    }
    printf("---------------");
}

void anulaVetor (int v[]){
	for (int a = 0; a<=nv; a++) v[a] = -1;
}

void visitaLargura (tipoGrafo* g, int v, int cor[], int ant[], int d[]){
    printf("\nv=%d\nD:", v);
    cor[v] = 1;
    anulaVetor(d);
    d[v] = 0;
    tipoFila f;
    inicializaFila(&f);
    addFila(&f, v);
    int u = 0;
    while (f.proxVazio!=1){
        int u = delFila(&f);
        tipoApontador ap = g->listaAdj[u];
        while (ap){
            if (cor[ap->vDest] == 0){
                cor[ap->vDest] = 1;
                d[ap->vDest] = d[u] + 1;
                ant[ap->vDest] = u;
                addFila(&f, ap->vDest);
            }
            ap = ap->prox;
        }
    }
    cor[u] = 2;
    printaCor(d);
}

void buscaLargura (tipoGrafo* g){
    int cor[nv];
    int ant[nv];
    int d[nv];

    for (int a = 0; a <= nv; a++){
        cor[a] = 0;
        ant[a] = -1;
        d[a] = 99;
    }

    for (int b = 1; b <= nv; b++){
        visitaLargura(g, b, cor, ant, d);
        for (int a = 1; a <= 5; a++){
            if (a == 5){
                cor[a] = 0;
                break;
            }
            cor[a] = 0;
        }
    }
}

int main ()
{
	tipoGrafo g;
	inicializaGrafo (&g, nv);

	insereAresta(&g, 4, 3, 1);
 	insereAresta(&g, 3, 1, 1);
	insereAresta(&g, 2, 5, 1);
   	insereAresta(&g, 1, 3, 1);
	insereAresta(&g, 3, 4, 1);
	insereAresta(&g, 4, 1, 1);
	insereAresta(&g, 4, 3, 1);
	insereAresta(&g, 5, 5, 1);
	insereAresta(&g, 5, 1, 1);

	imprimeGrafo (&g);

	buscaLargura(&g);

	NO* i = (NO*) malloc (sizeof(NO));
    i->vertice = 0;
    i->prox = NULL;

	return 0;
}
