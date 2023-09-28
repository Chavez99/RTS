/*
    Programa: stacklifo.c
    Descripcion: Char Stack del tipo LIFO
    Autor: Arturo Alejandro Chavez Murga
    Fecha: 19/09/23

    Comentarios: Ejecutar de la siguiente manera
    en terminal ubuntu: gcc slifo.c -o slifotest.out
    Ejecutar el archivo en ubuntu: ./slifotest.out
*/

#include <stdio.h>
#include <stdlib.h>
#define N 10 // Specifying the maximum N of the stack

/* Global declaration of variables */

char stack[N]; // Array implementation of stack
char sbuf[N];
int top; // To insert and delete the data elements in the stack
int i; // To traverse the loop to while displaying the stack
int choice; // To choose either of the 3 stack operations

void push(); // Function used to insert the element into the stack
void pop(); // Function used to delete the element from the stack
void peek(); // Function used to display all the elements in the stack according to LIFO rule
void is_Empty(); // Function used to display all the elements in the stack according to LIFO rule
void is_Full(); // Function used to display all the elements in the stack according to LIFO rule

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

void push(){
    char element;
    if(top == N- 1){
        printf("Pila llena\n");
    }
    else{
        printf("\nInserte el elemento a incluir en la pila:\n");
        scanf("%s", &element);
        top++;
        stack[top]=element;
    }
}

void pop(){
    char element;
    if(top == -1){
    printf("Pila vacia\n");
    }
    else{
    element=stack[top];
    printf("Elemento eliminado: %c\n",stack[top]);
    top--; // The element below the topmost element is deleted
    }
}

void peek(){
    if(top == -1){
        printf("Pila vacia\n"); // Stack is empty
    }
    else if(top > 0){
        printf("Los elementos en la pila son:\n");
        for(i = top; i >= 0; i--){
            printf("%c\n",stack[i]);
        }
    }
}

void is_Empty(){
    if(top == -1){
        printf("La pila se encuentra vacia\n");
        //return 1;
    }else{
        printf("Hay valores en la pila\n");
        //return 0;
    }   
}

void is_Full(){
    if(top == N-1){
        printf("La pila se encuentra llena\n");
        //return 1;
    }else{
        printf("La pila no se encuentra llena\n");
    }   
}