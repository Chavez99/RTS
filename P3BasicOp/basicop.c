/*
    Programa: num.c
    Descripcion: Manejo de numeros por arg
    Autor: Arturo Alejandro Chavez Murga
    Fecha: 19/09/23
*/

#include <stdio.h>
#include <stdlib.h>

#define N 20
#define MAX 3

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Error\n");
        return 1;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int result = 0;
    printf("argv[1] = %s\n", argv[1]);
    printf("argv[2] = %s\n", argv[2]);
    result = a+b;
    printf("sum: %d\n", result);
    return 0; 
}