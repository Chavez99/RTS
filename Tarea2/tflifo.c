#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define LIMIT 200


int mails = 0;
pthread_mutex_t mutex;
float ranvals[200];

float stack[LIMIT]; // Array implementation of stack
int stacktop = -1; // To insert and delete the data elements in the stack
int j = 0; // To traverse the loop to while displaying the stack
int choice; // To choose either of the 3 stack operations
//stacktop = -1; // Initializing top to -1 indicates that it is empty

void push(); // Function used to insert the element into the stack
void pop(); // Function used to delete the element from the stack
void display(); // Function used to display all the elements in the stack according to LIFO rule


void* randn(){
   int base = -1;
   int top = 1;
   int count = 20;

   void push(float element[]){

    if(stacktop == LIMIT- 1){
        printf("Pila llena\n");
    }
    else{
        stacktop++;
        stack[stacktop]=*element;
    }
    }
    printf("Number of j: %d\n", j);


    for(int i = 0; i<count; i++){
        pthread_mutex_lock(&mutex);
        ranvals[j] = ((top - base)*((float)rand()/RAND_MAX)) + base;
        push(&ranvals[j]);
        printf("Iteration: %d Ranvals: [%d] = %f\n", j+1, j, ranvals[j]);
        mails++;
        j++;
        pthread_mutex_unlock(&mutex);
    }  
    printf("Number of j: %d\n", j); 
        
}

void* lowpassfilter(){
    void display(){
        if(stacktop == -1){
            printf("Stack underflow\n"); // Stack is empty
        }
        else if(stacktop > 0){
            printf("The elements of the stack are:\n");
        for(int k = stacktop; k >= 0; k--){
            printf("%d. %f\n",k, stack[k]);
        }
        }
    }
    display();
    printf("Low pass\n");    
}


int main(int argc, char* argv[]){
    srand(time(NULL));
    pthread_t th[11];
    
    pthread_mutex_init(&mutex, NULL);

    for(int l = 0; l<10; l++){
        if(pthread_create(th + l, NULL, &randn, NULL) !=0){
            perror("Failed to create the thread");
            return 1;
        }   
        printf("Thread %d has started\n", l);
        if(pthread_join(th[l], NULL) !=0){
            return 2;
        }
        printf("Thread %d has finished execution\n", l);
    }
    if(pthread_create(th + 10, NULL, &lowpassfilter, NULL) !=0){
            perror("Failed to create the thread");
            return 3;
    }
    printf("Thread %d has started\n", 2);
    if(pthread_join(th[10], NULL) !=0){
        return 2;
    }
    printf("Thread %d has finished execution\n", 10);
    
    pthread_mutex_destroy(&mutex);

    printf("Number of mails: %d\n", mails);
    printf("Number of j: %d\n", j);
    return 0;

}
    