#ifndef STDIO_H
#include <stdio.h>
#define STDIO_H
#endif

#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H
#endif

#ifndef CLAVE_H
#include "clave.h"
#define CLAVE_H
#endif

#define m 11

typedef struct registro{
    Clave clave;
    int enUso;
}Registro;

Registro tabla[m];

