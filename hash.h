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

#define m 12799

typedef struct registro{
    char *carrera;
    Codigo clave;
    int enUso;
} Registro;

Registro tabla[m];

int inicializaRegistros(){
    int i;
    for(i=0; i<m; i++){
        tabla[i].enUso = 0;
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

// Convierte el Codigo ingresado a un int segun los valores del codigo ASCII
Clave convertirCodigo(Codigo unCodigo){
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

// Se agregan las claves y el valor de Hash Doble a un archivo para crear el histograma de Dispersión Empírica
int agregarArchivo(Clave unaClave, int j){
    FILE *archivo = fopen("claves.txt", "a");
    fprintf(archivo, "%d\t%d\n", unaClave, j);
  //  printf("%d\t%d\n", unaClave, j);
    fclose(archivo);
    return 1;
}

int insertarClave(Codigo unCodigo, char *unaCarrera){   // Hash de Direccionamiento Abierto
    Clave unaClave = convertirCodigo(unCodigo);
    int i = 0;
    while(i != m){
        int j = hashDoble(unaClave, i);
        if(!estaEnUso(j)){
            tabla[j].clave = (char*)malloc(strlen(unCodigo)*sizeof(char));
            strcpy(tabla[j].clave, unCodigo);
            tabla[j].carrera = (char*)malloc(strlen(unaCarrera)*sizeof(char));
            strcpy(tabla[j].carrera, unaCarrera);
            tabla[j].enUso = 1;
            printf("%s\t%s\n",tabla[j].clave, tabla[j].carrera);
            return j;
        }else{
            i++;
        }
    }
    return -1;
}

int buscarClave(Codigo unCodigo){
    Clave unaClave = convertirCodigo(unCodigo);
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

int leerArchivo(char *nombre){     // Lee el archivo para agregar los datos a la tabla hash
    FILE *archivo = fopen(nombre, "r");
    char *codigo, *nomCarrera;
    while(!feof(archivo)){
        char palabra1[111],palabra2[20];
        fscanf(archivo, "%[^\t]\t%s\n",palabra1, palabra2);
        codigo = (char*)malloc(strlen(palabra2)*sizeof(char));
        codigo = palabra2;
        nomCarrera = (char*)malloc(strlen(palabra1)*sizeof(char));
        nomCarrera = palabra1;
        insertarClave(codigo, nomCarrera);
    }
    fclose(archivo);
    return 1;
}

int mostrarTabla(){
    int i;
    for(i=0; i<m; i++){
        printf("Posicion = %d\nClave = %s\nCarrera = %s\n\n", i, tabla[i].clave, tabla[i].carrera);
    }
}

