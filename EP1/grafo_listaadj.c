#include <stdio.h>
#include <stdlib.h>
#include "grafo_listaadj.h"
enum cores {branco=0, cinza=1, preto=2};

/*
    Grafo direcionado
*/

//COMPLETO
bool inicializaGrafo(TipoGrafo* grafo, int nv){
	if(nv <= 0){
	    imprimeErroIniciar();
	    return false;
	}
	else{
	    grafo->listaAdj = (TipoApontador*) calloc(nv+1,sizeof(TipoApontador));
	    grafo->numVertices = nv;
	    grafo->numArestas = 0;
	    return true;
	}
	return false;
}

//COMPLETO
int obtemNrVertices(TipoGrafo* grafo){
	return grafo->numVertices;
}

//COMPLETO
int obtemNrArestas(TipoGrafo* grafo){
	return grafo->numArestas;
}

//COMPLETO
bool verificarValidadeVertice(int v, TipoGrafo* grafo){
	if(v <= 0) return false;
	if(v > grafo->numVertices) return false;
	return true;
}

//COMPLETO
bool existeAresta(int v1, int v2, TipoGrafo* grafo){
	char funcao[] = "existeAresta";
	if(!verificarValidadeVertice(v1,grafo)){
	    imprimeErro(funcao,v1,grafo);
	    return false;
	}
	if(!verificarValidadeVertice(v2,grafo)){
	    imprimeErro(funcao,v2,grafo);
	    return false;
	}
	TipoApontador p;
	p = grafo->listaAdj[v1];
	while(p){
	    if(p->vdest == v2) return true;
	    p = p->prox;
	}
	return false;
}

//COMPLETO
void insereAresta(int v1, int v2, TipoPeso peso, TipoGrafo* grafo){
	char funcao[] = "insereAresta";
	if(!verificarValidadeVertice(v1,grafo)) imprimeErro(funcao,v1,grafo);
	if(!verificarValidadeVertice(v2,grafo)) imprimeErro(funcao,v2,grafo);
	TipoApontador p;
    printf("chega aqui com peso: %f",peso);
    //p = (TipoApontador) malloc(sizeof(TipoApontador));   Alocando PONTEIRO???
	p = (TipoAresta*) malloc(sizeof(TipoAresta));
    printf("passou do malloc");
	p->prox = NULL;
	p->vdest = v2;
	p->peso = peso;
    printf("iniciou a aresta");
	if(grafo->listaAdj[v1] == NULL) grafo->listaAdj[v1] = p;
	else{
        p->prox = grafo->listaAdj[v1];
        grafo->listaAdj[v1] = p;
	}
	grafo->numArestas++;
}

//COMPLETO
TipoPeso obtemPesoAresta(int v1, int v2, TipoGrafo* grafo){
    char funcao[] = "obtemPesoAresta";
    if(!verificarValidadeVertice(v1,grafo)) imprimeErro(funcao,v1,grafo);
    if(!verificarValidadeVertice(v2,grafo)) imprimeErro(funcao,v2,grafo);
    TipoApontador p;
    p = grafo->listaAdj[v1];
    while(p){
        if(p->vdest == v2) return p->peso;
        p = p->prox;
    }
    return AN;
}

//COMPLETO
bool removeArestaObtendoPeso(int v1, int v2, TipoPeso* peso, TipoGrafo *grafo){
    char funcao[] = "removeArestaObtendoPeso";
    if(!verificarValidadeVertice(v1,grafo)) imprimeErro(funcao,v1,grafo);
    if(!verificarValidadeVertice(v2,grafo)) imprimeErro(funcao,v2,grafo);
    TipoApontador p;
    p = grafo->listaAdj[v1];
    TipoApontador ant = NULL;
    while(p){
        if(p->vdest == v2){
            if(ant != NULL) ant->prox = p->prox;  //Se nao for inicial ele pega o anterior e passa o proximo para frente.
            p->prox = NULL;
            *peso = p->peso;
            p->peso = AN;
            grafo->numArestas--;
            return true;
        }
        ant = p;
        p = p->prox;
    }
    return false;
}

//COMPLETO
bool removeAresta(int v1, int v2, TipoGrafo* grafo){
    char funcao[] = "removeAresta";
    if(!verificarValidadeVertice(v1,grafo)) imprimeErro(funcao,v1,grafo);
    if(!verificarValidadeVertice(v2,grafo)) imprimeErro(funcao,v2,grafo);
    TipoApontador p;
    p = grafo->listaAdj[v1];
    TipoApontador ant = NULL;
    while(p){
        if(p->vdest == v2){
            if(ant != NULL) ant->prox = p->prox;  //Se nao for inicial ele pega o anterior e passa o proximo para frente.
            p->peso = AN;
            p->prox = NULL;
            grafo->numArestas--;
            return true;
        }
        ant = p;
        p = p->prox;
    }
    return false;
}

//COMPLETO
bool listaAdjVazia(int v, TipoGrafo* grafo){
    char funcao[] = "ListaAdjVazia";
    if(!verificarValidadeVertice(v,grafo)) imprimeErro(funcao,v,grafo);
    if(grafo->listaAdj[v] == NULL) return true;
    return false;
}

//COMPLETO
TipoApontador primeiroListaAdj(int v, TipoGrafo *grafo){
    char funcao[] = "primeiroListaAdj";
    if(!verificarValidadeVertice(v,grafo)) imprimeErro(funcao,v,grafo);
    if(grafo->listaAdj[v] != NULL) return grafo->listaAdj[v];
    return NULL;
}

//COMPLETO
TipoApontador proxListaAdj(int v, TipoGrafo* grafo, TipoApontador atual){
    char funcao[] = "proxListaAdj";
    if(!verificarValidadeVertice(v,grafo)) imprimeErro(funcao,v,grafo);
    if(atual->prox != NULL) return atual->prox;
    return NULL;
}

//COMPLETO
void imprimeGrafo(TipoGrafo* grafo){
    int i,j;
    TipoApontador p;
    for(i=1;i<=grafo->numVertices;i++){
        printf("v%2d: ",i);
        p = grafo->listaAdj[i];
        while(p){
            printf("(%2d,%2f);",p->vdest,p->peso);
            p = p->prox;
        }
        printf("\n");
    }
}

//COMPLETO
void liberaGrafo(TipoGrafo* grafo){
	int i;
	TipoApontador p;
	TipoApontador ant;
	/*
	 * Liberação das arestas do grafo
	 * */
	for(i=1;i <= grafo->numVertices; i++){
	    p = grafo->listaAdj[i]->prox;
	    free(grafo->listaAdj[i]);
	    grafo->listaAdj[i] = NULL;
	    while(p){
            ant = p;
            p = p->prox;
            free(ant);
	    }
	}
	free(grafo->listaAdj);
	grafo->numVertices=0;
	grafo->numArestas=0;
	/*
	 * Liberação da alocação do vetor de vértices
	 * e zerando o grafo.
	 *
	 * (grafo em si não precisa ser liberado)
	 * */
	free(grafo->listaAdj);
	grafo->listaAdj = NULL;
	grafo->numVertices = 0;
	grafo->numArestas = 0;
}

//COMPLETO
int verticeDestino(TipoApontador p, TipoGrafo * grafo){
    return p->vdest;
}

//COMPLETO
void buscaProfundidade(TipoGrafo *grafo){
/*
    Alocação dos arranjos.
*/
    int stp = grafo->numVertices+1;
    int *cor = (int*) malloc(sizeof(int)*stp);
    int *tdesc = (int*) malloc(sizeof(int)*stp);
    int *tterm = (int*) malloc(sizeof(int)*stp);
    int *antecessor = (int*) malloc(sizeof(int)*stp);
    int tempo = 0;
/*
    Inicializa os arranjos.
*/
    int i;
    for(i=1;i<=grafo->numVertices;i++){
        cor[i] = branco;
        tdesc[i] = 0;
        tterm[i] = 0;
        antecessor[i] = -1;
    }
/*
    Faz a busca em profundidade para cada vértice caso ele não tenha sido visitado.
*/
    for(i=1;i<=grafo->numVertices;i++){
        if(cor[i] == branco)    visitaBP(i,grafo,&tempo,cor,tdesc,tterm,antecessor);
    }
}

//COMPLETO
void visitaBP(int v,TipoGrafo *grafo,int *tempo,int *cor,int *tdesc, int *tterm, int *antecessor){
    cor[v] = cinza;  //Passou pelo vértice
    tdesc[v] = ++(*tempo);  //Tempo de descoberta
    TipoApontador p = grafo->listaAdj[v];
    while(p){
        if(cor[p->vdest] == branco){  //Procura vértices em branco para explorar
            antecessor[p->vdest] = v;    //Guarda quem foi seu antecessor
            visitaBP(v,grafo,tempo,cor,tdesc,tterm,antecessor); //Chama o recursivo para a função
        }
        p = p->prox;
    }
    tterm[v] = ++(*tempo); //Depois de ter passado pelos outros, esse termina
    cor[v] = preto; //Recebe preto por ter terminado
}

/*
    Função de busca em profundidade que returna Verdadeiro se encontra um ciclo
    e Falso caso contrário.
*/

//COMPLETO
bool temCicloBP(TipoGrafo *grafo){
/*
    Alocação dos arranjos.
*/
    
    int stp = grafo->numVertices+1;
    /*
    int cor[stp];
    int antecessor[stp];
    int tterm[stp];
    int tdesc[stp];
    */
    
    int *cor = (int*) malloc(sizeof(int)*stp);
    int *tdesc = (int*) malloc(sizeof(int)*stp);
    int *tterm = (int*) malloc(sizeof(int)*stp);
    int *antecessor = (int*) malloc(sizeof(int)*stp);
    int tempo = 0;
/*
    Inicializa os arranjos.
*/
    //printf("vou iniciar os arranjos\n");
    int i;
    for(i=1;i<=grafo->numVertices;i++){
    	cor[i] = branco;
	    tterm[i] = 0;
	    tdesc[i] = 0;
	    antecessor[i] = -1;
	    //printf("Vértice: %2i; Cor: %i; Tdesc: %2i; Tterm: %2i; Antecessor: %2i\n",i,cor[i],tdesc[i],tterm[i],antecessor[i]);
    }
/*
    Faz a busca em profundidade para cada vértice caso ele não tenha sido visitado.
*/
    bool temCiclo;
    for(i=1;i<=grafo->numVertices;i++){
        if(cor[i] == branco)    temCiclo = visitaBPC(i,grafo,&tempo,cor,tdesc,tterm,antecessor);
        if(temCiclo == true){
            /*int v;
            for(v=1;v<=grafo->numVertices;v++){
                printf("Vértice: %2i; Cor: %i; Tdesc: %2i; Tterm: %2i; Antecessor: %2i\n",v,cor[v],tdesc[v],tterm[v],antecessor[v]);
            }
	    */
	        printf("%2i\n",i);
            return true;
        }
    }
    return false;
}

/*
    Função que faz a visita aos vértices em busca de um ciclo.
*/

//COMPLETO
bool visitaBPC(int v, TipoGrafo *grafo, int *tempo, int *cor, int *tdesc, int *tterm, int *antecessor){
    //printf("estou visitando\n");
    cor[v] = cinza;  //Passou pelo vértice
    tdesc[v] = ++(*tempo);  //Tempo de descoberta
    TipoApontador p = grafo->listaAdj[v];
    bool temCiclo;
    while(p){
        if(cor[p->vdest] == cinza){  //Procura vértices cinzas para definir um ciclo
            antecessor[p->vdest] = v;    //Guarda quem foi seu antecessor
	        tterm[v] = ++(*tempo);
	        printf("%2i\n",p->vdest);
            return true;
        }
        if(cor[p->vdest] == branco){
            antecessor[p->vdest] = v;
            temCiclo = visitaBPC(p->vdest,grafo,tempo,cor,tdesc,tterm,antecessor);
        }
        if(temCiclo == true){
	    tterm[v] = ++(*tempo);
	    printf("%2i\n",p->vdest);
	    return true;
	}
        p = p->prox;
    }
    tterm[v] = ++(*tempo); //Depois de ter passado pelos outros, esse termina
    return false;
}
/*
    Método de ordenação topológica que ordena o grafo,
    e imprime em ordem.
*/

//COMPLETO
void imprimeErro(char funcao[], int v, TipoGrafo* grafo){
	fprintf(stderr,"ERRO na chamada da função: %s. Vértice %i é inválido! Deve ser maior que 0 OU menor que o número de %d vértices iniciados!",funcao,v,grafo->numVertices);
}

//COMPLETO
void imprimeErroIniciar(){
	fprintf(stderr,"ERRO na chamada da função de inicialização do grafo! Número de vértices deve ser maior que 0!");
}
