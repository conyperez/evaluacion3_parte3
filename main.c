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

#ifndef HASH_H
#include "hash.h"
#define HASH_H
#endif

typedef Registro Tabla;

int main(){

    Tabla tabla[m];

    inicializaRegistros();

    insertarClave("1234");
    insertarClave("5678");
    insertarClave("6754");
    insertarClave("5534");
    insertarClave("1102");
    insertarClave("1107");

    mostrarTabla();

    if(buscarClave("6754") != -1){
        printf("\n\nClave encontrada");
    }else{
        printf("\n\nClave no encontrada");
    }

    if(buscarClave("6987") != -1){
        printf("\n\nClave encontrada");
    }else{
        printf("\n\nClave no encontrada");
    }

    return 1;
}

