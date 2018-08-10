//Ep 2 - Arvore B.

/*
    Referencias:
    -
    -
    -
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define t 3   //Tamanho do t como determinado no PDF.

/*
    Limites inferior e superior do numero de chaves de um no
    eh um inteiro fixo t >= 2 chamado de grau minimo.
    -Todo no que nao seja RAIZ deve conter pelo menos t-1 chaves;
    -Todo no interno que nao seja raiz deve conter pelo menos t filhos;
    -Todo no deve conter no maximo 2*t-1 chaves e portanto todo no
    deve ter no maximo 2*t filhos;
    -Um no esta cheio quando ele tiver exatamente 2*t-1 chaves.
*/

//Declaracao de TipoChave.
typedef int TipoChave;

FILE *fp;   //Ponteiro para o arquivo de entrada
FILE *fp_e; //Ponteiro para o arquivo de saida

//Declaracao do NO.
typedef struct aux{
    TipoChave chaves[2*t-1];
    struct aux* filhos[2*t];
    int numChaves;
    bool folha;
}NO, * PNO;

//Declaracao do par ordenado.
typedef struct {
    int indice; //Indíce correspondente a chave em no.
    PNO no_chave; //Ponteiro do no correspondente a chave.
}PAR_ORDENADO, * PPO;

/*
    Funcao auxiliar que cria nos.
*/
PNO create_no(){
    PNO no = (PNO) malloc(sizeof(NO));
    no->folha = true;
    no->numChaves = 0;
    for(int i=0;i<(2*t);i++){
        no->filhos[i] = NULL;
    }
    for(int i=0;i<(2*t-1);i++){
        no->chaves[i] = 0;
    }
    return no;
}

PNO b_tree_ordena_no(PNO raiz){
    //Pode ser executado somente quando for a primeira chave que foi eliminada
    //Arruma as chaves
    for(int g = 0; g < (2*t-1); g++){
        TipoChave chave = raiz->chaves[g+1];
        raiz->chaves[g+1] = raiz->chaves[g];
        raiz->chaves[g] = chave;
    }
    //Arruma os filhos
    for(int g = 0; g < (2*t-1); g++){
        PNO filho = raiz->filhos[g+1];
        raiz->filhos[g+1] = raiz->filhos[g];
        raiz->filhos[g] = filho;
    }
    return raiz;
}

/*
    Funcao de criacao de uma arvore B vazia.
*/
PNO b_tree_create(){
    printf("---------- B-TREE-CREATE ---------\n");
    PNO no = create_no();  //Chama a auxiliar.
    return no;
}

/*
    Funcao de Busca em Arvore B.
    Parametros:
    -Ponteiro para um no;
    -Chave que se quer encontrar;
    Retorno:
    -Estrutura PAR_ORDENADO contendo o ponteiro ao no;
    -NULL caso nao encontre.
*/
PPO b_tree_search(PNO no,TipoChave k){
    printf("---------- B-TREE-SEARCH-PO ---------\n");
    PPO par_ord;
    int i = 0;
    while((i <= no->numChaves) && (k > no->chaves[i])){  //Verificacao da busca.
        i++;  //Soma o indice.
    }   
    if((i <= no->numChaves) && (k == no->chaves[i])){ //Se achar a chave
        par_ord = (PPO) malloc(sizeof(PAR_ORDENADO)); //Aloca o par ordenado.
        par_ord->indice = i;   //Guarda o indice.
        par_ord->no_chave = no;   //Guarda o no.
        printf("achei\n");
        return par_ord;  //Retorna o par ordenado.
    }
    if(!no->folha){
        printf("nao eh folha ainda\n");
        par_ord = b_tree_search(no->filhos[i],k); //Chama o recursivo.
        return par_ord; //Retorna o que encontrou.
    }
    printf("nao achei nada\n");
    return NULL;
}

/*
    Implementacao da funcao de Split da arvore b.
    Param:
        -PNO x onde x eh o pai
        -int i onde i eh o indice (p o filho?)
        -PNO y o filho de x
*/
void b_tree_split_child(PNO x, int i, PNO y){
    printf("---------- B-TREE-SPLIT-CHILD ---------\n");
    //Aloca z.
    PNO z = create_no();
    z->folha = y->folha;
    z->numChaves = t-1;
    printf("z->folha: %d\n",z->folha);
    printf("z->numChaves: %d\n",z->numChaves);
    printf("x->numChaves: %d\n",x->numChaves);
    for(int j=0; j < (t-1); j++){   //Passa os valores da metade da direita de Y para Z
        z->chaves[j] = y->chaves[j+t];
        printf("z->chaves[j]: %d\n",z->chaves[j]);
        printf("y->chaves[j+t]: %d\n",y->chaves[j+t]);
    }
    if(!y->folha){  //Caso y nao seja folha, passa os filhos tambem
        printf("y nao eh folha\n");
        for(int j=0; j < t; j++){
            z->filhos[j] = y->filhos[j+t];
        }
    }
    //Ajusta y.
    y->numChaves = t-1;
    printf("Ajustei y\n");
    //Ajusta x.
    printf("Ajustando filhos de x\n");
    printf("i: %d\n",i);
    for(int j = (x->numChaves+1); j >= (i+1); j--){  //Empurra os filhos
        x->filhos[j] = x->filhos[j-1];
        printf("empurrei um filho de %d para %d\n",j-1,j);
    }
    x->filhos[i] = z;  //Coloca a direita do y
    int j = x->numChaves;
    printf("j: %d\n",j);
    while(j > i-1){
        x->chaves[j] = x->chaves[j-1];
        printf("x->chaves[%d] = %d\n",j,x->chaves[j]);
        printf("empurrei uma chave\n");
        j--;
    }
    
    x->chaves[i-1] = y->chaves[t-1];  //copia chave do meio e coloca naquele indice
    
    x->numChaves++;
    printf("x->numChaves: %d\n",x->numChaves);
}

/*
    Algoritmo Insercao na arvore B quando nao esta cheio.
*/
void b_tree_insert_nonfull(PNO x,TipoChave k){
    printf("---------- B-TREE-INSERT-NONFULL ---------\n");
    int i = x->numChaves;
    printf("x->numChaves: %d\n",x->numChaves);
    printf("Printando valores do no\n");
    for(int l = 0; l < (2*t-1); l++){
        printf("x->chaves[%d]: %d\n",l,x->chaves[l]);
    }
    printf("inserindo nonfull: %d\n",k);
    if(x->folha){  //Se for folha
        while((i >= 1) && (k < x->chaves[i-1])){  //i-1 para que ele seja equivalente ah 4 posicao
            x->chaves[i] = x->chaves[i-1]; //Empurra para frente
            i--;
            printf("loop\n");
        }
        printf("PASSEI no if\n");
        x->chaves[i] = k;  //Insere na posicao correta
        x->numChaves++;   //Aumenta numero de chaves

        for(int i=0;i < x->numChaves;i++){
            printf("x->chaves[%d] = %d\n",i,x->chaves[i]);
        }
        printf("x->numChaves: %d\n",x->numChaves);
    }
    else{
        printf("passei no else\n");
        while((i >= 1) && (k < x->chaves[i-1])){
            i--;
            printf("i: %d\n",i);
        }
        
        if(x->filhos[i]->numChaves == (2*t-1)){
            int cms = i;  //i e deve ser diferente para eles
            cms++;
            b_tree_split_child(x,cms,x->filhos[i]);
            if(k > x->chaves[i]) i++;
        }
        b_tree_insert_nonfull(x->filhos[i],k);
    }
}

/*
    Algoritmo para insercao em arvore b.
*/
PNO b_tree_insert(PNO raiz,TipoChave k){
    printf("---------- B-TREE-INSERT ---------\n");
    PNO r = raiz;  //R recebe a raiz
    if(r->numChaves == (2*t-1)){
        printf("no cheio\n");
        printf("inserindo %d\n",k);
        PNO s = create_no();
        s->folha = false;
        //Nao precisa setar numChaves, create_no faz isso
        s->filhos[0] = r;  //COLOCA a raiz antiga NA ESQUERDA JA
        printf("raiz->folha: %d\n",raiz->folha);
        b_tree_split_child(s,1,r);
        for(int i=0; i<(2*t-1);i++){
            printf("s->chaves[%d]: %d\n",i,s->chaves[i]);
        }
        b_tree_insert_nonfull(s, k);
        raiz = s;   //raiz recebe o novo no
        printf("raiz->folha: %d\n",raiz->folha);
        for(int i=0; i<(2*t-1);i++){
            printf("raiz->chaves[%d]: %d\n",i,raiz->chaves[i]);
        }
        return raiz;
    }
    else{
        printf("só inserindo: %d\n",k);
        b_tree_insert_nonfull(r, k);
        return r;
    } 
}
/*
    Algoritmo para deletar em uma folha.
*/
PNO b_tree_delete_leaf(PNO raiz, TipoChave k){
    printf("--------B-TREE-DELETE-LEAF--------\n");
    if(raiz->folha){
        PPO aux = b_tree_search(raiz,k);
        if(aux != NULL && (aux->no_chave == raiz)){  //Se o aux eh o mesmo que a raiz (garantido)
            raiz->chaves[aux->indice] = 0; //Coloca 0 no indice
            raiz->numChaves--;  //Diminui a quantidade de chaves
            for(int g = aux->indice; g < (2*t-1); g++){   //Faz o shift do 0
                TipoChave aux = raiz->chaves[g+1];
                raiz->chaves[g+1] = raiz->chaves[g];
                raiz->chaves[g] = aux;
            }
            return raiz; //Retorna a raiz que deletou
        }
        else{
            if(aux == NULL){
                printf("essa chave nao existe na folha\n");
                return raiz;
            }
        }
    }
    else{
        printf("erro? nao eh folha na b_tree_delete_leaf\n");
        return raiz;
    }
}
/*
    Algoritmo que faz a juncao.
*/
PNO b_tree_delete_merge(PNO x, int indice, PNO y, PNO z){
    printf("---------B-TREE-DELETE-MERGE---------\n");
    int aux_y = y->numChaves;  //t-1
    int aux_z = 0; //Inicio de z.

    y->chaves[aux_y] = x->chaves[indice];  //Coloca a chave que se quer no filho.
    
    for(int i = aux_y+1; i < (2*t-1); i++){ //Coloca as chaves de z em y.
        y->chaves[i] = z->chaves[aux_z];
        aux_z++;
    }

    //Ajusta o numero de chaves de y.
    y->numChaves = 2*t-1;

    if(!z->folha){  //Se z nao for folha passa os filhos.
        for(int i = aux_y+1; i < (2*t); i++){
            y->filhos[i] = z->filhos[aux_z];
            aux_z++;
        }
    }

    //Ajustando x.
    //Ajustando as chaves de x.
    for(int i = indice; i < (2*t-1); i++){
        x->chaves[i] = x->chaves[i+1];
    }

    //Ajustando a ultima chave de x.
    x->chaves[x->numChaves-1] = 0;
    
    //Ajustando os filhos de x.
    for(int i = indice+1; i < (2*t); i++){
        x->filhos[i] = x->filhos[i+1];
    }

    //Ajusta o ultimo filho.
    x->filhos[x->numChaves] = NULL;

    //Ajusta o numero de chaves de x.
    x->numChaves--;

    //Libera o z.
    free(z);

    //Retorna o x;
    return x;
}

/*
    Algoritmo para procurar o predecessor de uma chave no filho ja
*/
TipoChave b_tree_delete_predec(PNO raiz){
    printf("--------B-TREE-DELETE-PREDEC--------\n");
    if(raiz->folha){  //Se eh folha
        TipoChave chave = raiz->chaves[raiz->numChaves-1];  //Guarda a chave numa variavel
        raiz = b_tree_delete_leaf(raiz,chave); //Passa a chave que vamos retirar como parameteo
        return chave;
    }
    else{  //Caso seja noh interno
        int max = raiz->numChaves;
        if(raiz->filhos[max] != NULL && raiz->filhos[max]->numChaves >= t){
            printf("passei por aqui parça\n");
            TipoChave chave = b_tree_delete_predec(raiz->filhos[max]); //Chama recursivo
            return chave;
        }
        else{  //Caso seja noh interno e nao tenha filho a direita 
            printf("entrou aqui b_tree_delete_predec\n");
            if(raiz->filhos[max] != NULL){
                if(raiz->filhos[max]->numChaves == t-1 && raiz->filhos[max-1] != NULL && raiz->filhos[max-1]->numChaves >= t){
                    TipoChave chave_aux = b_tree_delete_predec(raiz->filhos[max]); //Pega a predecessora.
                    TipoChave mediana = raiz->chaves[max-1];  //Pega a mediana entre esses filhos.
                    if(raiz->filhos[max-1]->numChaves >= t){   //Se o filho a esquerda for pelo menos t
                        PNO aux_filho = raiz->filhos[max-1];
                        TipoChave chave_filho_anterior = aux_filho->chaves[aux_filho->numChaves-1];
                        aux_filho = b_tree_delete_leaf(aux_filho, chave_filho_anterior);
                        raiz->chaves[max-1] = chave_filho_anterior;
                        b_tree_insert_nonfull(raiz->filhos[max],mediana);
                        return chave_aux;
                    }
                }
                else{
                    if((raiz->filhos[max]->numChaves == t-1) && (raiz->filhos[max-1]->numChaves == t-1)){
                        raiz = b_tree_delete_merge(raiz,max-1,raiz->filhos[max-1],raiz->filhos[max]);
                        int tamanho_filho = raiz->filhos[max-1]->numChaves;
                        TipoChave chave = raiz->filhos[max-1]->chaves[tamanho_filho-1];
                        raiz->filhos[max-1] = b_tree_delete_leaf(raiz->filhos[max-1],chave);
                        return chave;
                    }
                }
            }
            else{
                TipoChave chave = raiz->chaves[max-1];  //Guarda a chave numa variavel
                raiz->chaves[max-1] = 0;  //Como eh o ultimo soh colocar 0
                raiz->numChaves--;  //Diminui a quantidade de chaves
                return chave;
            }
            
        }
    }
}
/*
    Algoritmo para procurar o sucessor de uma chave no filho ja
*/
TipoChave b_tree_delete_sucess(PNO raiz){
    printf("--------B-TREE-DELETE-SUCESS-------\n");
    if(raiz->folha){
        TipoChave chave = raiz->chaves[0];  //guarda a chave
        raiz = b_tree_delete_leaf(raiz,chave);  //chama o deleta na folha
        return chave;  //retorna a chave
    }
    else{
        if(raiz->filhos[0] != NULL && raiz->filhos[0]->numChaves >= t){
            printf("passei por aqui lek\n");
            TipoChave chave = b_tree_delete_sucess(raiz->filhos[0]);  //chama recursivo do sucessor
            return chave;  //retorna a chave
        }
        else{
            printf("entrou aqui b_tree_delete_sucess\n");
            if(raiz->filhos[0] != NULL){
                if((raiz->filhos[0]->numChaves == t-1) && raiz->filhos[1] != NULL && (raiz->filhos[1]->numChaves >= t)){
                    TipoChave chave_aux = b_tree_delete_sucess(raiz->filhos[0]);
                    TipoChave mediana = raiz->chaves[0];
                    if(raiz->filhos[1]->numChaves >= t){
                        PNO aux_filho = raiz->filhos[1];
                        TipoChave chave_filho_posterior = aux_filho->chaves[0];
                        aux_filho = b_tree_delete_leaf(aux_filho, chave_filho_posterior);
                        raiz->chaves[0] = chave_filho_posterior;
                        b_tree_insert_nonfull(raiz->filhos[0],mediana);
                        return chave_aux;
                    }
                }
                else{
                    if((raiz->filhos[1]->numChaves == t-1) && (raiz->filhos[1]->numChaves == t-1)){
                        raiz = b_tree_delete_merge(raiz,0,raiz->filhos[1],raiz->filhos[1]); //0 ta certo?
                        int tamanho_filho = raiz->filhos[0]->numChaves;
                        TipoChave chave = raiz->filhos[0]->chaves[0];
                        raiz->filhos[0] = b_tree_delete_leaf(raiz->filhos[0],chave);
                        return chave;
                    }
                }
            }
            else{
                TipoChave chave = raiz->chaves[0];
                raiz->chaves[0] = 0;
                raiz->numChaves--;
                raiz = b_tree_ordena_no(raiz);
                return chave;
            }
        }
    }
}


/*
    Algoritmo para delecao de uma chave k.
*/
PNO b_tree_delete(PNO raiz, TipoChave k){

    //Se for folha.
    if(raiz->folha){
        printf("deletando da folha a chave: %d\n",k);
        raiz = b_tree_delete_leaf(raiz,k);
        return raiz;
    }

    //Se for noh interno.
    else{

        //Faz a busca na arvore B.
        PPO ppo_buscado = b_tree_search(raiz,k);
        
        if(ppo_buscado == NULL){
            //mensagem de erro aqui.
            printf("essa chave nao existe, buscada: %d\n",k);
            return raiz;
        }
        else{

            //Faz auxiliares para o par ordenado.
            int indice = ppo_buscado->indice;
            PNO no_chave = ppo_buscado->no_chave;

            //Se estiver no noh interno.
            if(no_chave == raiz){
                printf("deletando com chave no noh interno, chave: %d\n",k);
                /*
                    Se o filho y que precede k no noh x tem pelo menos t chaves, entao
                    encontre o predecessor k' de k na subarvore com raiz y.
                    Delete recursivamente k', e substitua k por k' em x.
                */
                if(raiz->filhos[indice] != NULL && (raiz->filhos[indice]->numChaves >= t)){
                    printf("deletando no caso 2a, chave: %d\n",k);
                    raiz->chaves[indice] = b_tree_delete_predec(raiz->filhos[indice]); //Coloca a chave predecessora em chaves[indice].
                    return raiz;
                }
                else{
                    /*
                        Simetricamente, se o filho z imediatamente apos k no noh x
                        tem pelo menos t chaves, entao encontre o sucessor k' de k na
                        subarvore com raiz z. Delete recursivamente k', e substitua k por k' em x.
                    */
                    if(raiz->filhos[indice+1] != NULL && (raiz->filhos[indice+1]->numChaves >= t)){
                        printf("deletando no caso 2b, chave: %d\n",k);
                        raiz->chaves[indice] = b_tree_delete_sucess(raiz->filhos[indice+1]); //Coloca a chave 
                        return raiz;
                    }
                    /*
                        Caso contrario, se ambos y e z possuem apenas t-1 chaves,
                        faca a juncao de k e todas as chaves de z em y, de forma que
                        x perde tanto a chave k como o ponteiro para z, e y agora contem 2t-1
                        chave. Entao, libere z e delete recursivamente k de y.   
                    */
                    else{
                        if(raiz->filhos[indice] != NULL && raiz->filhos[indice+1] != NULL){
                            printf("deletando no caso 2c, chave: %d\n",k);
                            raiz = b_tree_delete_merge(raiz,indice,raiz->filhos[indice],raiz->filhos[indice+1]);
                            raiz = b_tree_delete(raiz,k);
                            return raiz;
                        }
                        else{
                            printf("um dos filhos eh nulo!\n");
                            return raiz;
                        }
                    }
                }
            }

            //Se nao estiver no noh interno (num filho talvez).
            else{
                printf("deletando chave que nao esta no noh interno, chave: %d\n",k);
                if(no_chave != raiz){
                    //Pega parte do codigo da busca.
                    int i = 0;
                    while((i <= raiz->numChaves) && (k < raiz->chaves[i])){
                        i++;
                    }
                    PNO v = raiz->filhos[i];   //Pega o filho de onde está a subarvore com a chave k.
                    /*
                        Se o filho nao for nulo, tiver chaves igual a t-1 e for folha.  (3a)
                    */
                    if((v != NULL) && (v->folha) && (v->numChaves == t-1) && (no_chave == v)){   //AQUI PODE DAR PROBLEMA
                        if(i == raiz->numChaves){  //Se for o ultimo o irmao imediato eh o penultimo (esquerda).
                            /*
                                Se for o ultimo ela pega a chave predecessor do ultimo, coloca no lugar em x e desce a de x
                                para a que vai ser excluida.
                            */
                            if((raiz->filhos[i-1] != NULL) && (raiz->filhos[i-1]->folha) && (raiz->filhos[i-1]->numChaves >= t)){
                                TipoChave chave_aux = b_tree_delete_predec(raiz->filhos[i-1]); //Pega a predecessora.
                                TipoChave mediana = raiz->chaves[i];  //Pega a mediana entre esses filhos.
                                v = b_tree_delete_leaf(v,k); //Remove a chave que queremos.
                                raiz->chaves[i] = chave_aux;    //Coloca a mediana 
                                b_tree_insert_nonfull(v,mediana); //Insere na que excluiu.
                                return raiz;
                            }
                        }
                        else{
                            /*
                                Se nao for o ultimo, ela pega o da direita para puxar a chave.
                            */ 
                            if((raiz->filhos[i+1] != NULL) && (raiz->filhos[i+1]->folha) && (raiz->filhos[i+1]->numChaves >= t)){
                                TipoChave chave_aux = b_tree_delete_sucess(raiz->filhos[i+1]); //Pega a predecessora.
                                TipoChave mediana = raiz->chaves[i];  //Pega a mediana entre esses filhos.
                                v = b_tree_delete_leaf(v,k); //Remove a chave que queremos.
                                raiz->chaves[i] = chave_aux;    //Coloca a mediana 
                                b_tree_insert_nonfull(v,mediana); //Insere na que excluiu.
                                return raiz;
                            }
                        }
                    }
                    else{
                        if((v != NULL) && (!v->folha) && (v->numChaves == t-1)){  //AQUI TAMBEM
                            int fg = 0;
                            while((fg <= v->numChaves) && (k < v->chaves[fg])){  //Procura dnv
                                fg++;
                            }
                            //Se o filho do filho de x for o no desejado e for folha
                            if((v->filhos[fg] != NULL) && (v->filhos[fg] == no_chave) && (v->filhos[fg]->folha)){
                                if(i == raiz->numChaves){  //Se for o da direita
                                    if((raiz->filhos[i-1] != NULL) && (raiz->filhos[i-1]->numChaves == t-1)){
                                        raiz = b_tree_delete_merge(raiz,i,raiz->filhos[i-1],raiz->filhos[i]); //Problemas?
                                        return b_tree_delete(raiz,k);
                                    }
                                    else{
                                        printf("entrou onde n devia\n");
                                    }
                                }
                                //Se for o da esquerda
                                else{
                                    if((raiz->filhos[i+1] != NULL) && (raiz->filhos[i+1]->numChaves == t-1)){
                                        raiz = b_tree_delete_merge(raiz,i,raiz->filhos[i],raiz->filhos[i+1]);
                                        return b_tree_delete(raiz,k);
                                    }
                                    else{
                                        printf("cagadinha aqui\n");
                                    }
                                }
                            }
                            //Caso nao atinja as exigencias desce uma vez
                            else{
                                printf("pode dar pau aqui\n");
                                raiz = b_tree_delete(v->filhos[fg],k);
                            }
                        }
                    }
                }
            }
        }
    }
}

/*
    Algoritmo para delecao pela raiz.
*/
PNO b_tree_delete_from_root(PNO raiz,TipoChave k){
    PNO r = raiz;
    if(r != NULL){
        if((r->numChaves == 0) && r->folha){ //Se for raiz, nao tem nada e nao tiver filhos
            //retorna
            printf("raiz vazia\n");
            return NULL;
        }
        else{
            if((r->numChaves == 0) && !r->folha){  //Se for raiz, nao tem nada mas tem filhos
                raiz = r->filhos[0]; //Coloca a raiz como sendo seu unico filho
                free(r); //Livra a raiz vazia
                return raiz;
            }
            else{
                printf("delete normal\n");
                raiz = b_tree_delete(raiz,k); //Procura na raiz a chave
                return raiz;
            }
        }
    }
    else{
        //colocar no arquivo
        printf("arvore vazia\n");
    }
}

void b_tree_print(PNO raiz, FILE *fp_e){
    if(raiz->folha){
        printf("(");
        for(int i=0; i < raiz->numChaves;i++){
            if(i == raiz->numChaves-1){
                printf("%d",raiz->chaves[i]);  //Quando eh o ultimo numero
            }
            else{
                printf("%d ",raiz->chaves[i]);  //Com espaco para separar os numeros
            }
        }
        printf(")");
    }
    else{
        printf("(");
        for(int i=0; i < raiz->numChaves+1;i++){
            if(raiz->filhos[i] != NULL){
                b_tree_print(raiz->filhos[i],fp_e);
            }
            if(i < raiz->numChaves){
                printf(" %d ",raiz->chaves[i]);
            }
        }
        printf(")");
    }
}

//Declaracao do main.
int main(int argc, char *argv[]){
    
    //Declaracao do arquivo.
    /*
        "i <chave>" - declaracao para insercao, caracter 'i' e uma chave.
        "r <chave>" - declaracao para remocao, caracter 'r' e uma chave.
        "p" - declarao para impressao da arvore, caracter 'p'.
        Exemplo: (((1 2) 3 (4 5) 6 (7 8)) 9 ((10 11) 12 (13 14) 15 (16 17)))
        "f" - declaracao para finalizar o programa, caracter 'f'.

        A principio o arquivo de entrada tera uma sequencia de comandos dizendo o que fazer
        e o programa devera executar isso em loop, QUALQUER TIPO de erro deve ser jogado para um arquivo de erro.
        fprintf(stderr,[text]).

    */

    //Abertura do arquivo.
    fp = fopen(argv[1],"r");
    if(!fp){
        printf("Arquivo nao encontrado...\n");
        printf("Ele se encontra no mesmo diretorio?\n");
        printf("Voce digitou o nome corretamente?");
    }
    else{
        int result; //Resultado da chamada para o arquivo.
        char tipoOperacao;
        TipoChave chave;
        PNO raiz;
        raiz = b_tree_create();
    
        //Ler arquivo de entrada.
        while((result = fscanf(fp,"%c %d\n",&tipoOperacao, &chave)) != EOF){

            //Faz insercao caso seja 'i'.
            if(tipoOperacao == 'i'){
                raiz = b_tree_insert(raiz,chave);
            }

            //Faz remocao caso seja 'r'.
            if(tipoOperacao == 'r'){
                printf("---------- B-TREE-DELETE ---------\n");
                b_tree_delete_from_root(raiz,chave);
            }

            //Faz impressao no arquivo caso seja 'p'.
            if(tipoOperacao == 'p'){
                fp_e = fopen(argv[2],"w");
                printf("---------- B-TREE-PRINT ---------\n");
                b_tree_print(raiz,fp_e);
                printf("\n");
            }

            //Sai do programa caso seja 'f'.
            if(tipoOperacao == 'f'){
                exit(0);  //Programa terminou com sucesso.
            }
        }
        if(result == EOF){
            printf("Faltou a finalização do programa com a letra 'f'.\n");
            exit(1); //Programa terminou com erro.
        }
    }
}