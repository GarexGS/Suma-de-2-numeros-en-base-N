#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char result[100];

struct nodo {
    int num;
    struct nodo *sig;
    struct nodo *ant;
};


//Prototipo de la funcion para cambiar de base
void cambioDeBase(long int iDec, int numbase,struct nodo **inicio, struct nodo **final);
//Prototipo de la funcion para sumar 2 numeros
void sumarDosNumeros(struct nodo **inicio1, struct nodo **final1,struct nodo **inicio2, struct nodo **final2,int base);
//Prototipo de la funcion validar cifra
int validarCifra(int cifra);
//Prototipos de las funciones para la Cola
bool isVacia(struct nodo **inicio);
void insertar(struct nodo **inicio, struct nodo **final, int num);
void imprimir(struct nodo *inicio);
int extraer(struct nodo **inicio,struct nodo **final);
void liberar(struct nodo **inicio);

    
int main(){
    int num1, num2, base, index;
    bool repeat = true;

    struct nodo *inicioN1 = NULL;
    struct nodo *finalN1 = NULL;
    struct nodo *inicioN2 = NULL;
    struct nodo *finalN2 = NULL;

    do{
        printf("Escribe el primer numero: "); 
        scanf("%d",&num1);
    
        printf("Escribe el segundo numero: "); 
        scanf("%d",&num2);

        printf("Escribe a la base que se desea sumar ambos numeros: "); 
        scanf("%d",&base);

        if(base>=2 && base<=16){
            cambioDeBase(num1,base,&inicioN1,&finalN1);
            printf("\nNumero %d en base %d = ",num1,base);
            imprimir(inicioN1);

            cambioDeBase(num2,base,&inicioN2,&finalN2);
            printf("Numero %d en base %d = ",num2,base);
            imprimir(inicioN2);

            printf("\nEl resultado de la suma es = ");
            sumarDosNumeros( &inicioN1, &finalN1, &inicioN2, &finalN2, base);
            imprimir(inicioN1);

            repeat = false;
        }
        else{
            printf("la base debe de ser un numero de 2 a 16\n");
        }

    }while(repeat);

    system("PAUSE");	
    return 0;
}
    
void cambioDeBase(long int iDec, int numbase,struct nodo **inicio, struct nodo **final){
    char base_digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7','8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    int converted_number[64];
    int  index=0;
    
    while (iDec != 0){
        converted_number[index] = iDec % numbase;
        iDec /= numbase;
        index++;
    }
    index--;
    for( ; index>=0; index--)
        insertar(inicio,final,base_digits[converted_number[index]]);
}

void sumarDosNumeros(struct nodo **inicio1, struct nodo **final1,struct nodo **inicio2, struct nodo **final2, int base){
    char base_digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7','8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    int converted_number[64];
    int index = 0;
    int acarreo = 0;
    bool repeat = true;

    do{
        int resultado = 0;
        int cifraNum1 = extraer(inicio1,final1);
        int cifraNum2 = extraer(inicio2,final2);

        // printf("\n cifraNum1= %d\ncifraNum2 = %d\n",cifraNum1,cifraNum2);
        // system("pause");

        if(cifraNum1 == -1 && cifraNum2 == -1 && acarreo == 0){
            repeat = false;
            break;
        }
        if(cifraNum1 == -1)
            cifraNum1 = 48; //valor ASCII de cero
        if(cifraNum2 == -1)
            cifraNum2 = 48; //valor ASCII de cero

        cifraNum1 = validarCifra(cifraNum1);
        cifraNum2 = validarCifra(cifraNum2);

        resultado = cifraNum1 + cifraNum2 + acarreo;
        // printf("\n%d + %d + %d = %d \n",cifraNum1,cifraNum2,acarreo,resultado);
        // printf("\n %d / %d = %d\n",resultado,base,resultado % base);
        
        converted_number[index] = (int)(resultado % base);
        acarreo = resultado / base;
        
        // printf(" = %d -> %d ",converted_number[index], acarreo);
        // system("pause");
        
        index++;

    }while(repeat);
      index--;
    for( ; index>=0; index--)
        insertar(inicio1,final1,base_digits[converted_number[index]]);

}

int validarCifra(int cifra){
    char num = (char) cifra;
    int cifraTemp = num - '0';
    
    switch(num){
        case 'A':
         cifraTemp = 10;
        break;
        case 'B':
         cifraTemp = 11;
        break;
        case 'C':
         cifraTemp = 12;
        break;
        case 'D':
         cifraTemp = 13;
        break;
        case 'E':
         cifraTemp = 14;
        break;
        case 'F':
         cifraTemp = 15;
        break;
    }
    return cifraTemp;
}

bool isVacia(struct nodo **inicio){
    bool isVacia = false;
    if (*inicio == NULL)
        isVacia = true;
   return isVacia;
}

void insertar(struct nodo **inicio,struct nodo **final, int num){
    struct nodo *nuevo = malloc(sizeof(struct nodo));
    nuevo -> num = num;
    nuevo -> sig = NULL;
    nuevo -> ant = NULL;

    if (isVacia(inicio)){
        *inicio = nuevo;
        *final = nuevo;
    }
    else{
        (*final) -> sig = nuevo;
        nuevo ->ant = *final;
        *final = nuevo;
        
    }
}

void imprimir(struct nodo *inicio){
    struct nodo *temp = inicio;
    while (temp != NULL) {
        printf("%c ", temp -> num);
        temp = temp -> sig;
    }
    printf("\n");
}

int extraer(struct nodo **inicio,struct nodo **final){
    if (!isVacia(inicio)){
        int numInNodo = (*final) -> num;
        struct nodo *bor = *final;
        if (*inicio == *final){
            *inicio = NULL;
            *final = NULL;
        }
        else{
            *final = (*final) -> ant;
        }
        free(bor);
        return numInNodo;
    }
    else
        return -1;
}
