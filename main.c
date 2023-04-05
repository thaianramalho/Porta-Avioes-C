#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

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
        apontador aux = fila->primeiro;
        while((aux->prox!=NULL) && (aux->prox->aviao.prioridade <= aviao.prioridade)) {
            aux = aux->prox;
        }
        if(aux->prox == NULL){//inserção no final da fila
            aux->prox = (apontador) malloc(sizeof(celula));
            aux = aux->prox;
            aux->prox = NULL;
            aux->aviao = aviao;
        }else{//inserção no meio da fila
            apontador novo = (apontador) malloc(sizeof(celula));
            novo->prox = aux->prox;
            aux->prox = novo;
            novo->aviao = aviao;
        }

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
    while (aux != NULL) {
        if (aux->aviao.id == id) {
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

int ultimoId = 0;
int contadorEmergencia = 0;

void CadastroLote(TipoFila *filaPouso, TipoFila *filaDecolar){
    TipoAviao aviao;
    int prioridade;
    int emergencia;
    int sorteio = rand() % 3;
    printf("Fila de pouso:\n");
    printf("Emergencias atendidas: [%d]\n", contadorEmergencia);
    printf("Sorteio:%d \n",sorteio);
    for(int i = 0; i < sorteio; i++){
        prioridade = 2;
        emergencia = rand() % 12;

        if (emergencia > 9){
            prioridade = 1;
            contadorEmergencia++;
        }

        ultimoId++;
        while (verificarID(*filaPouso, ultimoId) || verificarID(*filaDecolar, ultimoId)) {
            ultimoId++;
        }
        printf("ID: [%d]\n",ultimoId);

        aviao.id = ultimoId;
        aviao.prioridade = prioridade;
        enfileirar(filaPouso, aviao);
    }

    sorteio = rand() % 3;
    printf("Fila de decolagem:\n");
    printf("Sorteio:%d \n",sorteio);
    for(int i = 0; i < sorteio; i++){
        prioridade = 2;

        ultimoId++;
        while (verificarID(*filaPouso, ultimoId) || verificarID(*filaDecolar, ultimoId)) {
            ultimoId++;
        }

        printf("ID: [%d]\n",ultimoId);

        aviao.id = ultimoId;
        aviao.prioridade = prioridade;
        enfileirar(filaDecolar, aviao);
    }
}
int contadorDesenfileirar = 0;

void desenfileirar(TipoFila *fila1, TipoFila *fila2){
    int count = 0;
    apontador *aux = &(fila1->primeiro->prox);
    apontador *aux2 = &(fila2->primeiro->prox);

    while(count < 3 && *aux != NULL){
        if((*aux)->aviao.prioridade == 1){
            printf("Desenfileirando: [%d] - Prioridade: %d -- Pista: [%d]\n", (*aux)->aviao.id, (*aux)->aviao.prioridade, count+1);
            apontador temp = *aux;
            *aux = temp->prox;
            free(temp);
            contadorDesenfileirar++;
            count++;
        }else{
            aux = &((*aux)->prox);
        }
    }

    while(count < 3 && (fila1->primeiro->prox != NULL || fila2->primeiro->prox != NULL)){
        int aleatorio = rand() % 2;
        if((aleatorio == 0 && fila1->primeiro->prox != NULL) || fila2->primeiro->prox == NULL){
            printf("Desenfileirando avião [%d] - Prioridade: %d -- Pista: [%d]\n", fila1->primeiro->prox->aviao.id, fila1->primeiro->prox->aviao.prioridade, count+1);
            apontador temp = fila1->primeiro->prox;
            fila1->primeiro->prox = temp->prox;
            free(temp);
        }else{
            printf("Desenfileirando avião [%d] - Prioridade: %d -- Pista: [%d]\n", fila2->primeiro->prox->aviao.id, fila2->primeiro->prox->aviao.prioridade, count+1);
            apontador temp = fila2->primeiro->prox;
            fila2->primeiro->prox = temp->prox;
            free(temp);
        }
        contadorDesenfileirar++;
        count++;
    }
}



int main(){
    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");

    TipoFila filaDecolar;
    TipoFila filaPouso;

    criar(&filaDecolar);
    criar(&filaPouso);
    int i = 0;
    char ch;
    do{
        printf("[ENTER]\n");
        ch=fgetc(stdin);
        if(ch==0x0A){
            system("cls");
            CadastroLote(&filaPouso, &filaDecolar);
            printf("\n----- FILA DE ATERRISSAGEM -----\n");
            imprimir(filaPouso);
            printf("\n----- FIM DA FILA DE ATERRISSAGEM -----\n");
            printf("\n----- FILA DE DECOLAGEM -----\n");
            imprimir(filaDecolar);
            printf("\n----- FIM DA FILA DE DECOLAGEM -----\n");

            desenfileirar(&filaPouso, &filaDecolar);
            printf("Aviões atendidos: [%d]\n", contadorDesenfileirar);
            }
    }while(ch == 0x0A);

return 0;

}









