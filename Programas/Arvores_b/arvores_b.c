#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define t 2

typedef int TipoChave;

typedef struct no{
    TipoChave chaves[2*t-1];
    struct no* filho[2*t];
    int numChaves;
    bool folha;
} NO;

NO* cria_no() {
    NO* x = (NO*) malloc(sizeof(NO));
    x->folha = true;
    x->numChaves = 0;
    return x;
}

void cria_arvore_b(NO* raiz){
    NO* x = cria_no();
    //escreve no disco
    raiz = x;
}

NO busca_arvore_b(NO* y,int k) {
}

int main(){
    NO raiz;
    cria_arvore_b(&raiz);
    //o que eu to fazendo da minha vida
}