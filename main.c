#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // se utiliza para las variables booleanas (true | false)

// Definición de la estructura lista doblemente enlazada
// Teoría para entender que es una lista https://youtu.be/15urP2LmfqY
struct nodo {
    int num;
    struct nodo *sig; //apuntador al nodo siguiente
    struct nodo *ant; //apuntador al nodo anterior
};

//Prototipo de la funcion para cambiar de base
void cambioDeBase(long int numero, int numbase,struct nodo **inicio, struct nodo **final);

//Prototipo de la funcion para sumar 2 numeros
void sumarDosNumeros(struct nodo **inicio1, struct nodo **final1,struct nodo **inicio2, struct nodo **final2,int base);

//Prototipo de la función validar cifra
int validarCifra(int cifra);

//Prototipos de las funciones para la lista
bool isVacia(struct nodo **inicio);
void insertar(struct nodo **inicio, struct nodo **final, int num);
void imprimir(struct nodo *inicio);
int extraer(struct nodo **inicio,struct nodo **final);
void liberar(struct nodo **inicio);

    
int main(){
    int num1, num2, base;
    bool repeat = true;

    // Las siguientes 2 lineas serviran para almacenar el primer numero en su nueva base
    struct nodo *inicioN1 = NULL; //Definimos el inicio de la lista 1
    struct nodo *finalN1 = NULL; //Definimos el final de la lista 2

    // Las siguientes 2 lineas serviran para almacenar el segundo numero en su nueva base
    struct nodo *inicioN2 = NULL; //Definimos el inicio de la lista 2
    struct nodo *finalN2 = NULL; //Definimos el final de la lista 2

    do{
        printf("Escribe el primer numero: "); 
        scanf("%d",&num1);
    
        printf("Escribe el segundo numero: "); 
        scanf("%d",&num2);

        printf("Escribe a la base que se desea sumar ambos numeros: "); 
        scanf("%d",&base);

        if(base>=2 && base<=16){
            cambioDeBase(num1,base,&inicioN1,&finalN1); //cambiamos la base del primer numero
            printf("\nNumero %d en base %d = ",num1,base);
            imprimir(inicioN1);//imprimimos el primer numero en su nueva base

            cambioDeBase(num2,base,&inicioN2,&finalN2);//cambiamos la base del segundo numero
            printf("Numero %d en base %d = ",num2,base);
            imprimir(inicioN2);//imprimimos el segundo numero en su nueva base

            printf("\nEl resultado de la suma es = ");
            sumarDosNumeros( &inicioN1, &finalN1, &inicioN2, &finalN2, base); //sumamos los 2 números en la nueva base
            imprimir(inicioN1);//imprimimos la suma en la nueva base

            repeat = false;
        }
        else{
            printf("la base debe de ser un numero de 2 a 16\n");
        }

    }while(repeat);// el while permite repetir el programa si el usuario ingresa una base diferente a 2-16

    system("PAUSE");// se utiliza para pausar el programa hasta presionar una tecla	
    return 0;
}
    
void cambioDeBase(long int numero, int numbase,struct nodo **inicio, struct nodo **final){
    // base_digits es un arreglo que se usa para saber que símbolo corresponde al cambiar de base
    char base_digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7','8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    // converted_number es un arreglo que almacena el valor del dígito en su nueva base
    int converted_number[128];
    // index nos ayuda a saber cuantas cifras tendrá nuestro numero en su nueva base
    int  index=0;
    
    while (numero != 0){
        /* la operación numero % numbase se traduce como "modulo" en la "base" en la variable "numero"
            retorna el residuo de la division entre el numero y su base
            no confundir con la operación numero / numbase, que corresponde a la division de numero entre numbase
        */ 
        converted_number[index] = numero % numbase;
        numero = numero / numbase;
        index++;
    }
    index--;
    /* En el for guardamos cada cifra de nuestro numero en un nodo,
       pero esta ves lo que guarda es su valor ASCII de su carácter
       Ejemplo: si el carácter es A su valor ASCII es 65
    */
    for( ; index>=0; index--)
        insertar(inicio,final,base_digits[converted_number[index]]);
}

void sumarDosNumeros(struct nodo **inicio1, struct nodo **final1,struct nodo **inicio2, struct nodo **final2, int base){
    // base_digits es un arreglo que se usa para saber que símbolo corresponde al cambiar de base
    char base_digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7','8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    // converted_number es un arreglo que almacena el valor del dígito en su nueva base
    int converted_number[128];
    // index nos ayuda a saber cuantas cifras tendrá nuestro suma en su nueva base
    int index = 0;
    // acarreo almacena el excedente en la suma de 2 cifras
    int acarreo = 0;
    // repeat permanece en true hasta que termine de sumar todas las cifras de los 2 números
    bool repeat = true;

    do{
        /*  resultado almacena la suma de 2 cifras mas el acarreo
            en cada iteración regresa a cero 
        */
        int resultado = 0;
        int cifraNum1 = extraer(inicio1,final1); // extraemos la ultima cifra de la derecha del primer numero 
        int cifraNum2 = extraer(inicio2,final2); // extraemos la ultima cifra de la derecha del segundo numero 

        /* 
            al intentar extraer una cifra si el numero ya no tiene retorna un -1,
            por lo tanto si el primer numero y el segundo ya no cuentan con cifras para ser sumadas
            detenemos el proceso de suma, amenos que acarreo sea != 0
        */
        if(cifraNum1 == -1 && cifraNum2 == -1 && acarreo == 0){
            repeat = false;
            break;
        }
        /*
            si cifraNum1 es  == -1 le asignamos un 0 para que pueda continuar con la suma
            ya que cifraNum2 o el acarreo pueden tener aun valores
        */ 
        if(cifraNum1 == -1)
            cifraNum1 = 48; //valor ASCII del numero cero
         /*
            si cifraNum2 es  == -1 le asignamos un 0 para que pueda continuar con la suma
            ya que el acarreo aun no es igual a cero
        */ 
        if(cifraNum2 == -1)
            cifraNum2 = 48; //valor ASCII del numero cero

        // verificamos que la cifra no se una letra y cambiamos su valor de ASCII a un numero entero
        cifraNum1 = validarCifra(cifraNum1);
        cifraNum2 = validarCifra(cifraNum2);

        // sumamos ambas cifras y el acarreo
        resultado = cifraNum1 + cifraNum2 + acarreo;
        
        /* la operación numero % numbase se traduce como "modulo" en la "base" en la variable "numero"
            retorna el residuo de la division entre el numero y su base
            no confundir con la operación numero / numbase, que corresponde a la division de numero entre numbase
        */ 

        converted_number[index] = resultado % base;
        acarreo = resultado / base;
            
        index++;

    }while(repeat);
      index--;

    /* En el for guardamos cada cifra de nuestro nuevo numero en un nodo,
       pero esta ves lo que guarda es su valor ASCII de su carácter
       
       NOTA: usamos inicio1 y final1 para almacenar la suma esto reemplaza el primer numero
       que digitó el usuario pero como ya se mostró reutilizamos estos apuntadores para no agregar
       2 apuntadores nuevos.
    */

    for( ; index>=0; index--)
        insertar(inicio1,final1,base_digits[converted_number[index]]);

}

int validarCifra(int cifra){
    /*
        Almacenamos en num su carácter que representa en ASCII
        Ejemplo si cifra = 66
        (char )cifra retorna el carácter "B"
        
        si num tiene almacenado el carácter '5' 
        para cambiar el carácter a un numero entero realizamos
        num - '0' esto retorna el numero 5 pero ya se puede almacenar
        en una variable de tipo int

    */ 
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
    //validamos si la lista que mandaron en inicio contiene nodos
    bool isVacia = false;
    if (*inicio == NULL)
        isVacia = true;
   return isVacia;
}

void insertar(struct nodo **inicio,struct nodo **final, int num){
    struct nodo *nuevo = malloc(sizeof(struct nodo)); //reservamos memoria para el nuevo nodo
    nuevo -> num = num; // guardamos en el nodo el numero que recibió la función
    nuevo -> sig = NULL; // iniciamos el apuntador sig del nuevo nodo en NULL
    nuevo -> ant = NULL; // iniciamos el apuntador ant del nuevo nodo en NULL

    // si la lista no contiene nodos inicio y fin apuntan al nodo nuevo
    if (isVacia(inicio)){
        *inicio = nuevo;
        *final = nuevo;
    }
    /*
        si la lista ya contiene almenos un nodo
        el nodo al que apunta final cambia su apuntador sig para apuntar al nuevo nodo
        el nuevo nodo cambia su apuntador ant para apuntar al nodo final que es el anterior a el
        por ultimo final apunta al nuevo nodo quien se convirtió en el nuevo nodo final
    */
    else{
        (*final) -> sig = nuevo;
        nuevo ->ant = *final;
        *final = nuevo;
        
    }
}

void imprimir(struct nodo *inicio){

    /*
        recorremos la lista a la que apunta inicio
        creamos un nodo temporal que el que recorra la lista
        al imprimir el valor que lamacena el nodo lo hacemos con %c
        por que el entero que almacena es el que representa el carácter en la tabla ASCII
        Ejemplo si temp -> num es igual a 69 al poner %c el 69 se muestra como la letra E
    */

    struct nodo *temp = inicio;
    while (temp != NULL) {
        printf("%c ", temp -> num);
        temp = temp -> sig;
    }
    printf("\n");
}

int extraer(struct nodo **inicio,struct nodo **final){
    /*
        -si la lista a la que apunta inicio contiene almenos un nodo
        ingresa al if. Dentro de este guardamos el valor del ultimo nodo en numInNodo
        -Creamos un apuntador (bor) que apunte al nodo final
        -Si el apuntador inicio y final apuntan al mismo nodo, les asignamos NULL para
        que asi el programa sepa que no hay mas nodos en la lista.
        -Si inicio y fin apuntan a nodos diferentes, hacemos que el apuntador final
        apunte al mismo nodo al que apunta el puntero ant dentro del nodo final
        -free(bor) elimina el nodo que anteriormente era el ultimo

        
    */
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
