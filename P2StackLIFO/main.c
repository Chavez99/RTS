#include <stdio.h>
#include <string.h>

int MAXSIZE = 8;       
char stack[8][5];     
int top = -1;            

int isempty() {

   if(top == -1)
      return 1;
   else
      return 0;
}
   
int isfull() {

   if(top == MAXSIZE)
      return 1;
   else
      return 0;
}

char* peek() {
   return stack[top];
}

char* pop() {
   char* data;
	
   if(!isempty()) {
      data = stack[top];
      top = top - 1;   
      return data;
   } else {
      printf("Could not retrieve data, Stack is empty.\n");
   }
}

char push(char *data) {

   if(!isfull()) {
      top = top + 1;
      strcpy(stack[top], data);
    //   stack[top] = data;
   } else {
      printf("Could not insert data, Stack is full.\n");
   }
}

int main() {
   // push items on to the stack 
   push("hello\n");
   push("world\n");
   push("world\n");
   push("world\n");
   push("world\n");
   push("world\n");
   push("world\n");
   push("world\n");
   push("adsfgasdfgsd\n");

   printf("Element at top of the stack: %s\n" ,peek());
   printf("Elements: \n");

   // print stack data 
   while(!isempty()) {
      char *data = pop();
      printf("%s\n", data);
      memset(data, 0, strlen(data));
   }

   printf("Stack full: %s\n" , isfull()?"true":"false");
   printf("Stack empty: %s\n" , isempty()?"true":"false");
   
   return 0;
}
