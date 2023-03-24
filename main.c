#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int id;
    int prioridade;
}TipoAviao;

typedef struct celula *apontador;

typedef struct celula{
    TipoAviao aviao;
    apontador prox;
}celula;

typedef struct{
    apontador primeiro;
}TipoFila;

void criar(TipoFila *fila){
    fila->primeiro = (apontador) malloc(sizeof(celula));
    fila->primeiro->prox = NULL;
}

void enfileirar(TipoFila *fila, TipoAviao aviao){
    if(verificarID(*fila, aviao.id)==1){
        printf("O id do aviao ja esta na fila");
    }else{
        apontador aux = fila->primeiro;
        while((aux->prox!=NULL) && (aux->prox->aviao.prioridade <= aviao.prioridade)) {
            aux = aux->prox;
        }
        if(aux->prox == NULL){//inser��o no final da fila
            aux->prox = (apontador) malloc(sizeof(celula));
            aux = aux->prox;
            aux->prox = NULL;
            aux->aviao = aviao;
        }else{//inser��o no meio da fila
            apontador novo = (apontador) malloc(sizeof(celula));
            novo->prox = aux->prox;
            aux->prox = novo;
            novo->aviao = aviao;
        }

    }
}

apontador* desenfileirar(TipoFila *fila){
    apontador aux = fila->primeiro->prox;
    fila->primeiro->prox = aux->prox;
    return aux;
    }

void imprimir(TipoFila fila){
    apontador aux = fila.primeiro->prox;
    while(aux!=NULL){
        printf("[%d] - Prioridade: %d\n", aux->aviao.id, aux->aviao.prioridade);
        aux = aux->prox;
        }
    }

int buscar(TipoFila fila, int id){
    apontador aux = fila.primeiro->prox;
    while(aux!=NULL){
        if(aux->aviao.id == id){
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
    }

int verificarID(TipoFila fila, int id){
    apontador aux;
    aux = fila.primeiro->prox;
    while(aux!=NULL){
        if(aux->aviao.id == id){
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

void zerar(TipoFila *fila){
    apontador aux;
    aux = fila->primeiro;
    while(aux->prox != NULL){
        apontador excluir = desenfileirar(fila);
        free(excluir);
    }
    criar(fila);
}

void CadastroLote(TipoFila *filaPouso, TipoFila *filaDecolar){
    srand(time(NULL));
    TipoAviao aviao;
    int id;
    int prioridade;
    int emergencia;
    int aux=1;

    do{
        id = rand()%50;
        prioridade = 2;
        emergencia = rand()%12;

        if (emergencia > 9){
            prioridade = 1;
        }

        if(id % 2 == 0 ){
            if(verificarID(*filaDecolar, id) == 0){
                aviao.id = id;
                aviao.prioridade = prioridade;
                enfileirar(filaDecolar, aviao);
                aux++;
            }
        }else{
            if(verificarID(*filaPouso, id) == 0){
            aviao.id = id;
            aviao.prioridade = prioridade;
            enfileirar(filaPouso, aviao);
            aux++;
            }
        }

    }while(aux <= 20);

    }

int main(){
    srand(time(NULL));

    TipoFila filaDecolar;
    TipoFila filaPouso;
    TipoAviao aviao;

    criar(&filaDecolar);
    criar(&filaPouso);

    CadastroLote(&filaPouso, &filaDecolar);
    imprimir(filaPouso);
    printf("\n-----------------------------------------------\n");
    imprimir(filaDecolar);



    return 0;
}






