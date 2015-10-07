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
    leerArchivo("datos.txt");
    mostrarTabla();

    return 1;
}

