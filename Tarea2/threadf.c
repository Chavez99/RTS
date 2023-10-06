/*
	Programa:    threadf.c
   
	Introducción:    Las señales obtenidas por los sensores suelen ser afectadas por ruido generado fuentes externas, como luz o electricidad. 
	Para reducir el impacto del ruido en las señales es común el uso de filtros.
   
	Descripción: En esta actividad se elaborará un programa en Lenguaje C que utilice hilos (threads) y semáforos (pthread_mutex). 
	El programa implementará un hilo que se activará 10 veces (puede usarse un ciclo). 
	En cada activación deberá generar 20 números aleatorios en el rango [1, -1]. Cada número deberá contener 6 decimales. 
	Por ejemplo, el número -0.768902. Los 20 números aleatorios deberán ser almacenados en un arreglo compartido. 
	Una vez que los números han sido almacenados en el arreglo compartido, otro hilo los leerá y les aplicará el filtro pasa-bajas (low-pass filter)
	y almacenará los valores originales y los nuevos valores en otro arreglo. Al concluir las 20 activaciones, 
	un tercer hilo almacenará los 200 valores (originales y filtrados) en un archivo. 

	Deberán entregarse el código del programa, el archivo generado en una de las ejecuciones del programa y una gráfica que muestra las dos curvas: valores originales y valores después de aplicarles el filtro.                
    
	Autores:    Arturo Alejandro Chávez Murga
*/ 


#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define LIMIT 200

pthread_mutex_t mutex;
float ranvals[200];
float lpvals[200];
float total[200][2];

float stack[LIMIT]; // Original random floats
float filteredstack[LIMIT]; // Filtered data

int stacktop = -1; // To insert and delete the data elements in the stack
int fstacktop = -1;
int j = 0; // To traverse the loop to while displaying the stack
int n = 0;
float alpha = .5;

void push(); // Function used to insert the element into the stack
void fpush(); // Function used to insert the element into the stack
void display(); // Function used to display all the elements in the stack according to LIFO rule
void mcsv();

void push(float element[]){

    if(stacktop == LIMIT- 1){
        printf("Pila llena\n");
    }
    else{
        stacktop++;
        stack[stacktop]=*element;
    }
}
void fpush(float felement[]){

    if(fstacktop == LIMIT- 1){
        printf("Pila llena\n");
    }
    else{
        fstacktop++;
        filteredstack[fstacktop]=*felement;
    }
}
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

void* randn(){
   int base = -1;
   int top = 1;
   int count = 20;

    printf("Number of j: %d\n", j);
    for(int i = 0; i<count; i++){
        pthread_mutex_lock(&mutex);
        ranvals[j] = ((top - base)*((float)rand()/RAND_MAX)) + base;
        push(&ranvals[j]);
        printf("Iteration: %d Ranvals: [%d] = %f\n", j+1, j, ranvals[j]);
        j++;
        pthread_mutex_unlock(&mutex);
    }  
    printf("Number of j: %d\n", j); 
}

void* lowpassfilter(){
    int ren = 0;
    int col = 0;
    display();
    printf("Low pass Beginning\n");  
    for(int m = 0; m < LIMIT; m++){
        pthread_mutex_lock(&mutex);
        lpvals[n] = alpha*stack[n] + (1-alpha)*lpvals[n];
        fpush(&lpvals[n]);
        printf("Iteration: %d lpnvals: [%d] = %f\n", n+1, n, lpvals[n]);
        n++;
        pthread_mutex_unlock(&mutex);        
    }
    printf("Low pass end\n");    
    printf("Printing in a [200][2] array both matrix\n");
    pthread_mutex_lock(&mutex);
    for(ren = 0; ren<200; ren++){
        total[ren][0] = stack[ren];
    }
    for(ren = 0; ren<200; ren++){
        total[ren][1] = filteredstack[ren];
    }
    pthread_mutex_unlock(&mutex);
    for(ren = 0; ren < 200; ren++){
        for(col = 0; col < 2; col++){
            printf("%f",total[ren][col]);
        }
        printf("\n");
    }
}

void* exportcsv(){
    mcsv();
}

void mcsv(){
    FILE *fp;
    fp = fopen("file.csv", "w");
    if(fp = NULL){
        printf("File error");
        system("pause");
        //return 1;
    }
    fprintf(fp, "1,2,3\n");
    fclose(fp);
    fp = 0;
    system("pause");
    //return 0;
    printf("Hi\n");
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    pthread_t th[12];
    
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
        return 4;
    }
    printf("Thread %d has finished execution\n", 10);
    
    if(pthread_create(th + 11, NULL, &exportcsv, NULL) !=0){
        perror("Failed to create the thread");
        return 5;
    }
    printf("Thread %d has started\n", 2);
    if(pthread_join(th[11], NULL) !=0){
        return 6;
    }
    
    pthread_mutex_destroy(&mutex);

    printf("Number of j: %d\n", j);
    return 0;
}
    