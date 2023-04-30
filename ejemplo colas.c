#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct nodo {
    int num;
    struct nodo *sig;
};

struct nodo *inicio = NULL;
struct nodo *final = NULL;

bool isVacia();
void insertar(int x);
int extraer();
void imprimir();
void liberar();

int main(){
    insertar(5);
    insertar(10);
    insertar(50);
    imprimir();
    printf("Extraemos uno de la cola: %i\n", extraer());
    imprimir();
    liberar();
    system("pause");
    return 0;
}


bool isVacia(){
    bool isVacia = false;
    if (inicio == NULL)
        isVacia = true;
   return isVacia;
}

void insertar(int num){
    struct nodo *nuevo;
    nuevo = malloc(sizeof(struct nodo));
    nuevo -> num = num;
    nuevo -> sig = NULL;

    if (isVacia()){
        inicio = nuevo;
        final = nuevo;
    }
    else{
        final->sig = nuevo;
        final = nuevo;
    }
}

void imprimir(){
    struct nodo *temp = inicio;
    printf("Listado de todos los elementos de la cola.\n");
    while (temp != NULL) {
        printf("%i - ", temp -> num);
        temp = temp -> sig;
    }
    printf("\n");
}

int extraer(){
    if (!isVacia()){
        int numInNodo = inicio -> num;
        struct nodo *bor = inicio;
        if (inicio == final){
            inicio = NULL;
            final = NULL;
        }
        else{
            inicio = inicio->sig;
        }
        free(bor);
        return numInNodo;
    }
    else
        return -1;
}

void liberar(){
    struct nodo *temp = inicio;
    struct nodo *bor;
    while (temp != NULL){
        bor = temp;
        temp = temp->sig;
        free(bor);
    }
}


// insertar(&inicio,&final,15);
// insertar(&inicio,&final,5);
// insertar(&inicio,&final,10);
// extraer(&inicio,&final);
// imprimir(inicio);