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
    int matricula;
    char *institucion;
    char *ciudad;
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

Clave convertirCodigo(Codigo unCodigo){      // Convierte el Codigo a un int con los valores del código ASCII
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

int agregarArchivo(Clave unaClave, int j){    // Agrega las claves y el resultado del Hash Doble para crear la Dispersión Empírica
    FILE *archivo = fopen("claves.txt", "a");
    fprintf(archivo, "%d\t%d\n", unaClave, j);
  //  printf("%d\t%d\n", unaClave, j);
    fclose(archivo);
    return 1;
}

// Hash de Direccionamiento Abierto
int insertarClave(Codigo unCodigo, int totalMatricula, char *unaInstitucion, char *unaCiudad, char *unaCarrera){
    Clave unaClave = convertirCodigo(unCodigo);
    int i = 0;
    while(i != m){
        int j = hashDoble(unaClave, i);
        if(!estaEnUso(j)){
            tabla[j].clave = (char*)malloc(strlen(unCodigo)*sizeof(char));
            strcpy(tabla[j].clave, unCodigo);
            tabla[j].matricula = totalMatricula;
            tabla[j].institucion = (char*)malloc(strlen(unaInstitucion)*sizeof(char));
            strcpy(tabla[j].institucion, unaInstitucion);
            tabla[j].ciudad = (char*)malloc(strlen(unaCiudad)*sizeof(char));
            strcpy(tabla[j].ciudad, unaCiudad);
            tabla[j].carrera = (char*)malloc(strlen(unaCarrera)*sizeof(char));
            strcpy(tabla[j].carrera, unaCarrera);
            tabla[j].enUso = 1;
            printf("%d\t%s\t%s\t%s\t%s\n",tabla[j].matricula,tabla[j].institucion,tabla[j].ciudad,tabla[j].carrera,tabla[j].clave);
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

int leerArchivo(char *nombre){
    FILE *archivo = fopen(nombre, "r");
    char *institucion,*ciudad, *carrera,*codigo;
    int cantMatricula;
    while(!feof(archivo)){
        char palabra1[100],palabra2[50],palabra3[115],palabra4[20];
        fscanf(archivo, "%d\t%[^\t]\t%[^\t]\t%[^\t]\t%s\n", &cantMatricula,palabra1,palabra2,palabra3,palabra4);
        institucion = (char*)malloc(strlen(palabra1)*sizeof(char));
        institucion = palabra1;
        ciudad = (char*)malloc(strlen(palabra2)*sizeof(char));
        ciudad = palabra2;
        carrera = (char*)malloc(strlen(palabra3)*sizeof(char));
        carrera = palabra3;
        codigo = (char*)malloc(strlen(palabra4)*sizeof(char));
        codigo = palabra4;
        insertarClave(codigo, cantMatricula, institucion, ciudad, carrera);
    }
    fclose(archivo);
    return 1;
}

int mostrarTabla(){
    int i;
    for(i=0; i<m; i++){
        printf("Posicion = %d\nClave = %s\nMatricula = %d\nInstitucion = %s\nCiudad = %s\nCarrera = %s\n\n", i, tabla[i].clave, tabla[i].matricula, tabla[i].institucion, tabla[i].ciudad, tabla[i].carrera);
    }
}



