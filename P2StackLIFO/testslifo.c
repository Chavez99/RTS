/*
    Programa: stringlifo.c
    Descripcion: Pila de datos string ordenada con el método LIFO.
    Autor: Arturo Alejandro Chavez Murga
    Fecha: 21/09/23

    Comentarios: Ejecutar de la siguiente manera
    en terminal ubuntu: gcc string.c -o slifotest.out
    Ejecutar el archivo en ubuntu: ./slifotest.out
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Stacksize = 3;
char stack[4][20]; // Arreglo de la pila
int top = -1; 
int i; 
int choice; 
char element[20];

int is_empty(){
    if(top == -1){
        printf("La pila se encuentra vacia\n");
        return 1;
    }else{
        printf("Hay valores en la pila\n");
        return 0;
    }   
}

int is_full(){
    if(top == Stacksize){
        printf("La pila se encuentra llena\n");
        return 1;
    }else{
        printf("La pila no se encuentra llena\n");
        return 0;
    }   
}

void push(){
    char element[20];
    if(is_full()){
        printf("Pila llena\n");
    }
    else{
        printf("\nInserte el elemento a incluir en la pila:\n");
        scanf("%s", element);
        top = top + 1;
        strcpy(stack[top], element);
    }
}

char* pop(){
    char* element;
    if(is_empty()){
    printf("Pila vacia\n");
    }
    else{
    element=stack[top];
    printf("Elemento eliminado: %s\n",stack[top]);
    top--;
    return element;
    }
}

char* peek(){
    if(top == -1){
        printf("Pila vacia\n");
        return 0; 
    }
    else{
        printf("Elemento en la cima de la pila:\n %s\n", stack[top]);
        return 0; 
    }
}

/*
char* listpeek(){
    if(top == -1){
        printf("Pila vacia\n"); 
        return 0; 
    }
    else{
        printf("Los elementos en la pila son:\n");
        for(i = top; i >= -1; i--){
            printf("%s\n",stack[i]);
        }
        return 0; 
    }
}
*/


int main(){
    printf ("\nPila del tipo LIFO (Last In First Out)\n");
    printf ("Tamaño de la pila (4)\n\n");
    top = -1; 
    do{
        printf("1. push\n2. pop\n3. peek\n4. is_empty\n5. is_full\n6. list_peek\n7. Exit\n\n");
        printf("Seleccione una opción:");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                push();
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                is_empty();
                break;
            case 5:
                is_full();
                break;
            /*case 6:
                listpeek();
                break;
            */
            case 7:
                printf("See ya!\n");
                exit(0);
                break;
            default:
                printf("Seleccione una de las 7\n");
                break;
        }
    } while(choice!=6);
    return 0;
}
