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

#ifndef CLAVE_H
#include "clave.h"
#define CLAVE_H
#endif

#define m 11

typedef struct registro{
    Codigo clave;
    int enUso;
}Registro;

Registro tabla[m];

int inicializaRegistros(){
    int i;
    for(i=0; i<m; i++){
        tabla[i].enUso = 0;     // 0 = no esta en uso;   1 = si esta en uso
    }
    return 1;
}

int estaEnUso(int j){
    if(tabla[j].enUso == 1){
        return 1;
    }else{
        return 0;
    }
}

Clave convertirClave(Codigo unCodigo){    // Convierte el Codigo a un int segun el valor del código ASCII
    int ASCII;
    Clave clave = 0;
    char caracter;
    char *cadena = unCodigo;

    while(*cadena != '\0'){
        caracter = *cadena;
        ASCII = caracter;
        clave += ASCII;
        cadena++;
    }
    return clave;
}

int hashDoble(int unaClave, int i){
    int h1 = unaClave % m;
    int h2 = 1 + (unaClave % (m-2));
    int j = (h1 + (i * h2)) % m;

    return j;
}

int insertarClave(Codigo unCodigo){           // Hash por Direccionamiento Abierto.
    Clave unaClave = convertirClave(unCodigo);
    int i = 0;
    while(i != m){
        int j = hashDoble(unaClave, i);
        if(!estaEnUso(j)){
            tabla[j].clave = (char*)malloc(strlen(unCodigo)*sizeof(char));
            strcpy(tabla[j].clave, unCodigo);
            tabla[j].enUso = 1;
            return j;
        }else{
            i++;
        }
    }
    return -1;   // Error: tabla hash completa
}

int buscarClave(Codigo unCodigo){
    Clave unaClave = convertirClave(unCodigo);
    int i = 0;
    while(i != m){
        int j = hashDoble(unaClave, i);
        if((estaEnUso(j)) && (strcmp(tabla[j].clave, unCodigo)==0)){
            return j;
        }
        i++;
    }
    return -1;
}

int leerArchivo(char *nombre){    
    FILE *archivo = fopen(nombre, "r");
    char *codigo;
    while(!feof(archivo)){
        char palabra[20];
        fscanf(archivo,"%s", palabra);
        codigo = (char*)malloc(strlen(palabra)*sizeof(char));
        codigo = palabra;
        insertarClave(codigo);
    }
    fclose(archivo);

    return 1;
}


int mostrarTabla(){
    int i;
    for(i=0; i<m; i++){
        printf("Posicion = %d \nClave = %s\n\n", i, tabla[i].clave);
    }
}


