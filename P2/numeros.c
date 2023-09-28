/*

   Programa:  numeros.c
   
   Objetivo:  Mostrar el uso de operadores aritmeticos, operaciones de control (for) y funciones (metodos).
   
   Autor:     Arnoldo Diaz Ramirez
   
*/


#include <stdio.h>

/*
   Prototipos de las funciones
*/

int suma(int, int);
int resta(int, int);
int es_par(int);
int sumatoria(int);
double factorial(int);

int main()
{
   int x,y,s;
   double result;
   
   printf("Escribe un numero: ");
   scanf("%d", &x);
   
   printf("Escribe otro numero: ");
   scanf("%d", &y);
   
   s = suma(x,y);
   printf("La suma de %d y %d es %d\n", x, y, s);
   
   s = resta(x,y);
   printf("La resta de %d y %d es %d\n", x, y, s);
   
   s=es_par(x);
   if (s==1) {
      printf("El numero %d es par\n", x);
   } else {
      printf("El numero %d es impar\n", x);
   }
   
   s=sumatoria(x);
   printf("La sumatoria desde 1 hasta %d es %d\n", x, s);
   
   result = factorial(x);
   printf("El factorial de %d es %.0f\n", x, result);
   
   return 0;
}

/*
   Codigo de las funciones
*/

int suma(int a, int b)
{
   int aux;
   aux = a + b;
   return aux;
}

int resta(int a, int b)
{
   return a - b;
}

int es_par(int a)
{
   int aux;
   
   aux = a % 2;
   
   if (aux != 0) {
      return 0;
   } else {
      return 1;
   }   
}

int sumatoria (int a)
{
   int i, aux;
   
   aux=0;
   for (i=1; i<=a; i++) {
      aux += i;     // aux = aux + i;
   }
   
   return aux;
   
}

double factorial(int a)
{
   if (a <= 1) {
      return 1;
   } else {
      return a * factorial(a-1);
   }
}
