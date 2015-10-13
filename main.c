#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H
#endif

#ifndef STRING_H
#include <string.h>
#define STRING_H
#endif

#ifndef TIME_H
#include <time.h>
#define TIME_H
#endif

#ifndef HASH_H
#include "hash.h"
#define HASH_H
#endif

typedef Registro Tabla;

int main(){

    Tabla tabla[m];

    inicializaRegistros();
    clock_t start = clock();
    leerArchivo("datos.txt");
    printf("DATOS INGRESADOS\n");
 /* if(buscarClave("I176S8C4J1V1")){
        printf("\nClave encontrada\n");
    }else{
        printf("\nClave no encontrada\n");
    }*/
    printf("Tiempo de ejecucion = %f\n", ((double)clock() - start)/CLOCKS_PER_SEC);
   // mostrarTabla();

    return 1;
}

