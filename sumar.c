#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* convertirBase(char* numero, int baseAntigua, int baseNueva) {
    /* Función que convierte un número de una base a otra */
    int decimal = 0, longitud = strlen(numero), exponente = 1, i, j;
    char* resultado = (char*) malloc(100 * sizeof(char));

    /* Convertir el número a decimal */
    for (i = longitud - 1; i >= 0; i--) {
        int valor;
        if (numero[i] >= '0' && numero[i] <= '9') {
            valor = numero[i] - '0';
        } else if (numero[i] >= 'A' && numero[i] <= 'F') {
            valor = numero[i] - 'A' + 10;
        } else {
            printf("Número no válido.\n");
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
        } else {
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
    int longitud1 = strlen(numero1), longitud2 = strlen(numero2);
    int longitudMaxima = longitud1 > longitud2 ? longitud1 : longitud2;
    char* resultado = (char*) malloc(sizeof(char) * (longitudMaxima + 2));
    memset(resultado, ' ', longitudMaxima+2); // Inicializa los 3 caracteres en cero
    resultado[longitudMaxima+1] = '\0';
    int acarreo = 0, i, j;

    printf("longitud1 = %d\n",longitud1);
    printf("longitud2 = %d\n",longitud2);
    printf("longitudMaxima = %d\n",longitudMaxima);
    

    for (i = longitud1 - 1, j = longitud2 - 1; i >= 0 || j >= 0 || acarreo > 0; i--, j--) {
        int digito1 = i >= 0 ? numero1[i] - '0' : 0;
        int digito2 = j >= 0 ? numero2[j] - '0' : 0;
        int suma = digito1 + digito2 + acarreo;

        char digito = (suma % base) + '0';
        printf("\n%d + %d + %d = %d = %c",digito1,digito2,acarreo,suma,digito);
        
        resultado[longitudMaxima] = digito;
        printf("\nres= %c",resultado[longitudMaxima]);
        longitudMaxima--;
        
        acarreo = suma / base;
    }
    // resultado[strlen(resultado)] = '\0';
    printf("\nresultadoSize= %d",strlen(resultado));
    printf("\nresultado= %c%c",resultado[1],resultado[2]);
    return resultado;
}


int main() {
    char numero1[100], numero2[100];
    int base1, base2, baseNueva;
    char* resultado;

    /* Leer los números y las bases */
    printf("Ingrese el primer numero: ");
    scanf("%s", numero1);
    printf("Ingrese la base del primer numero: ");
    scanf("%d", &base1);
    printf("Ingrese el segundo numero: ");
    scanf("%s", numero2);
    printf("Ingrese la base del segundo numero: ");
    scanf("%d", &base2);
    printf("Ingrese la base del resultado: ");
    scanf("%d", &baseNueva);

    /* Convertir los números a la base nueva */
    char* numero1Nuevo = convertirBase(numero1, base1, baseNueva);
    char* numero2Nuevo = convertirBase(numero2, base2, baseNueva);

    printf("\nnumero1Nuevo = %s",numero1Nuevo);
    printf("\nnumero2Nuevo = %s\n",numero2Nuevo);

    /* Sumar los números en la base nueva */
    char* resultadoNuevo = sumarNumeros(numero1Nuevo, numero2Nuevo, baseNueva);

    /* Mostrar el resultado en la base nueva */
    printf("\n%s + %s = %s en base %d\n", numero1, numero2, resultadoNuevo, baseNueva);

    /* Liberar la memoria */
    free(numero1Nuevo);
    free(numero2Nuevo);
    free(resultadoNuevo);

    return 0;
}
