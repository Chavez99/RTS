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
//#define N 10 // Declarando la capacidad de la pila


char stack[2][20]; // Arreglo de la pila
int Stacksize = 1;
int top = -1; // To insert and delete the data elements in the stack
int i; // To traverse the loop to while displaying the stack
int choice; // To choose either of the 3 stack operations

//void push(); // Function used to insert the element into the stack
//void pop(); // Function used to delete the element from the stack
//void peek(); // Function used to display all the elements in the stack according to LIFO rule
//void is_Empty(); // Function used to display all the elements in the stack according to LIFO rule
//void is_Full(); // Function used to display all the elements in the stack according to LIFO rule
char element[20];

int is_Empty(){
    if(top == -1){
        printf("La pila se encuentra vacia\n");
        return 1;
    }else{
        printf("Hay valores en la pila\n");
        return 0;
    }   
}

int is_Full(){
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
    if(is_Full()){
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
    if(is_Empty()){
    printf("Pila vacia\n");
    }
    else{
    element=stack[top];
    printf("Elemento eliminado: %s\n",stack[top]);
    top--; // The element below the topmost element is deleted
    return element;
    }
}

char* peek(){
    if(top == -1){
        printf("Pila vacia\n"); // Stack is empty
    }
    else if(top > 0){
        printf("Los elementos en la pila son:\n");
        for(i = top; i >= 0; i--){
            printf("%s\n",stack[i]);
        }
    }
}



int main(){
    printf ("\nPila del tipo LIFO (Last In First Out)\n\n");
    top = -1; // Initializing top to -1 indicates that it is empty
    do{
        printf("1. Insert\n2. Delete\n3. Peek\n4. is_Empty\n5. is_Full\n6. Exit\n\n");
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
                is_Empty();
                break;
            case 5:
                is_Full();
                break;
            case 6:
                exit(0);
                break;
            default:
                printf("Seleccione una de las 6!\n");
                break;
        }
    } while(choice!=6);
    return 0;
}
