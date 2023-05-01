/* 
    sumar 2 números de diferente base
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Prototipo de la función convertirCifra(cambia las cifras dependiendo de su valor ASCII)
int convertirCifra(int cifra);
//Prototipo de la función convertirBase
char* convertirBase(char* numero, int baseAntigua, int baseNueva);
//Prototipo de la función sumarNumeros
char* sumarNumeros(char* numero1, char* numero2, int base);

int main() {
    char numero1[100], numero2[100];// estos arreglos almacenaran números con maximo 100 dígitos
    int base1, base2, baseNueva; // variables para almacenar las bases
    char* resultado; // apuntador que almacenara la suma de los 2 números

    printf("\t***** Suma de Dos numeros en diferente base *****\n");
    printf("Porfavor usar los caracteres del 0-9 y de A-F para funcionar correctamente.\n");

    /* Leer los números y las bases */
    printf("\nIngrese el primer numero: ");
    scanf("%s", numero1);
    printf("Ingrese la base del primer numero: ");
    scanf("%d", &base1);
    printf("\nIngrese el segundo numero: ");
    scanf("%s", numero2);
    printf("Ingrese la base del segundo numero: ");
    scanf("%d", &base2);
    printf("\nIngrese la base del resultado: ");
    scanf("%d", &baseNueva);

    /* Convertir los números a la base nueva */
    char* numero1Nuevo = convertirBase(numero1, base1, baseNueva);
    char* numero2Nuevo = convertirBase(numero2, base2, baseNueva);

    printf("\nNumero 1 en base %d = %s",baseNueva,numero1Nuevo);
    printf("\nNumero 2 en base %d = %s",baseNueva,numero2Nuevo);

    /* Sumar los números en la base nueva */
    char* resultadoNuevo = sumarNumeros(numero1Nuevo, numero2Nuevo, baseNueva);

    /* Mostrar el resultado en la base nueva */
    printf("\n\n%s + %s = %s en base %d\n", numero1Nuevo, numero2Nuevo, resultadoNuevo, baseNueva);

    /* Liberar la memoria */
    free(numero1Nuevo);
    free(numero2Nuevo);
    free(resultadoNuevo);

    return 0;
}

int convertirCifra(int cifra){
    /*
        Tabla ASCII: https://elcodigoascii.com.ar/codigos-ascii/letra-a-mayuscula-codigo-ascii-65.html
        Almacenamos en num su carácter que representa en ASCII
        Ejemplo si cifra = 57
        (char )cifra retorna el carácter "9"
        
        si num tiene almacenado el carácter '9' 
        para cambiar el carácter a un numero entero realizamos
        num - '0' esto retorna el numero 9 ya que el caracter '9'= 57 en ASCII
        entonces si el caracter '0' = 48 en ASCII
        cifraTemp = 57 - 48 = 9

        Pero si cifra>= 65 cambia el proceso Ejemplo:
        cifra = 66
        num = 'B' ya que B tiene como valor ASCII 66
        si queremos que cifraTemp = 11 ahora debemos restar el caracter '7'
        por que '7' = 55 en ASCII

        Entonces tenemos:
        cifraTemp = 66 - 55 = 11
    */ 
    char num = (char) cifra; 
    int cifraTemp = num - ((cifra>=65)? '7':'0');
    /*Nota: para entender la linea anterior ver el siguiente video 
        Operador ternario o operador interrogación '?'
        https://youtu.be/eo971_99br8?t=6  
    */

    return cifraTemp;
}
char* convertirBase(char* numero, int baseAntigua, int baseNueva) {
    /* Función que convierte un número de una base a otra */
    int decimal = 0, longitud = strlen(numero), exponente = 1, i, j;
    char* resultado = (char*) malloc(100 * sizeof(char));

    /* Convertir el número a decimal */
    for (i = longitud - 1; i >= 0; i--) {
        int valor;
        if (numero[i] >= '0' && numero[i] <= '9') {
            valor = numero[i] - '0';
        } 
        else if (numero[i] >= 'A' && numero[i] <= 'F') {
            valor = numero[i] - 'A' + 10;
        } 
        else {
            //si se usan caracteres diferentes a 0-9 o A-F se detiene el programa
            // por ejemplo 01ab3
            printf("Numero no valido.\n");
            exit(1);
        }
        decimal += valor * exponente;
        exponente *= baseAntigua;
    }

    /* Convertir el número decimal a la base nueva */
    i = 0;
    while (decimal > 0) {
        
        int resto = decimal % baseNueva;
        char digito;
        
        if (resto >= 0 && resto <= 9) {
            digito = resto + '0';
        } 
        else {
            digito = resto - 10 + 'A';
        }
        resultado[i++] = digito;
        decimal /= baseNueva;
    }
    resultado[i] = '\0';

    /* Invertir el resultado */
    longitud = strlen(resultado);
    
    for (i = 0, j = longitud - 1; i < j; i++, j--) {
        char temp = resultado[i];
        resultado[i] = resultado[j];
        resultado[j] = temp;
    }

    return resultado;
}
char* sumarNumeros(char* numero1, char* numero2, int base) {
    /* Función que suma dos números en la misma base */
    int longitud1 = strlen(numero1), //almacenamos la cantidad de dígitos que tiene el numero 1
    int longitud2 = strlen(numero2);//almacenamos la cantidad de dígitos que tiene el numero 2
    int longitudMaxima = longitud1 > longitud2 ? longitud1 : longitud2;// guardamos la cantidad de dígitos mas grande
    char* resultado = (char*) malloc(sizeof(char) * (longitudMaxima + 2)); //reservamos memoria para el apuntador
    int acarreo = 0, i, j;
    
    memset(resultado, ' ', longitudMaxima+2); // Inicializa el apuntador con carateres vacíos, para evitar tener basura
    resultado[longitudMaxima+1] = '\0';// agregamos el caracter nulo para que el programa lo identifique como una cadena de caracteres
    
    //recorremos cifra por cifra de ambos números para sumarlas
    for (i = longitud1 - 1, j = longitud2 - 1; i >= 0 || j >= 0 || acarreo > 0; i--, j--) {
        
        int digito1 =  0;
        int digito2 =  0;

        /*
            si los números no han llegado a su final, cambiamos el valor se su cifra para poder hacer la suma
            ya que en este punto los apuntadores numero1 y numero2 almacenan caracteres que no se pueden sumar,
            cambiando su cifra de caracter a entero con ayuda de la tabla de valores ASCII
        */ 

        if(i >= 0)
            digito1 = convertirCifra(numero1[i]);
        if(j >= 0)
            digito2 = convertirCifra(numero2[j]);

        // Sumamos las cifras y su acarreo
        int suma = digito1 + digito2 + acarreo;
        // Pasamos la nueva cifra de entero a caracter y la almacenamos
        char digito = (suma % base) + (((suma % base) > 9 )? '7':'0');
        resultado[longitudMaxima] = digito;
        // restamos en 1 la longitud maxima para trabajar con la siguiente cifra
        longitudMaxima--;
        /*
            almacenamos el acarreo para sumarlo con la siguiente cifra
            acarreo = suma / base; usualmente toma valores de 1 o cero
        */
        acarreo = suma / base;
    }
    return resultado;
}