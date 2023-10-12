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

float stack[LIMIT]; // Arreglo sin modificar
float filteredstack[LIMIT]; // Arreglo filtrado

int stacktop = -1; 
int fstacktop = -1;
int j = 0; 
int n = 0;
float alpha = .5;
float filt = 0;

void push(); 
void fpush(); 
void display(); 
int mcsv();

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
        printf("Pilla vacía\n");
    }
    else if(stacktop > 0){
        printf("Elementos de la pila:\n");
        for(int k = stacktop; k >= 0; k--){
            printf("%d. %f\n",k, stack[k]);
        }
    }
}

void* randn(){
   int base = -1;
   int top = 1;
   int count = 20;

    printf("Contador de j: %d\n", j);
    for(int i = 0; i<count; i++){
        pthread_mutex_lock(&mutex);
        ranvals[j] = ((top - base)*((float)rand()/RAND_MAX)) + base;
        push(&ranvals[j]);
        printf("Iteración: %d Números aleatorios: [%d] = %f\n", j+1, j, ranvals[j]);
        j++;
        pthread_mutex_unlock(&mutex);
    }  
    printf("Número de j: %d\n", j); 
}

float lowpass(float num){
    filt = (alpha*num) + ((1-alpha)*filt);
    return filt;
}

void* lowpassfilter(){
    int ren = 0;
    int col = 0;
    display();
    printf("Filtro pasa-bajas\n");  
    for(int m = 0; m < LIMIT; m++){
        pthread_mutex_lock(&mutex);
        lpvals[n] = lowpass(stack[n]);
        fpush(&lpvals[n]);
        printf("Iteración: %d datos filtrados: [%d] = %f\n", n+1, n, lpvals[n]);
        n++;
        pthread_mutex_unlock(&mutex);        
    }
    printf("Fin del filtro pasa bajas\n");    
    printf("Vaciando en arreglo [200][2] ambas pila\n");
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
void create_csv(){
    FILE *fp;
    int x;

    fp=fopen("Summary.csv","w+");

    fprintf(fp,"Raw,Filtered\n");

    for(x = 0; x < 200; x++){
        fprintf(fp,"%f,%f\n",total[x][0],total[x][1]);
    }
    fclose(fp);
    printf("\nArchivo creado");
}

void* exportcsv(){
    create_csv();
}




int main(int argc, char* argv[]){
    srand(time(NULL));
    pthread_t th[12];
    
    pthread_mutex_init(&mutex, NULL);

    for(int l = 0; l<10; l++){
        if(pthread_create(th + l, NULL, &randn, NULL) !=0){
            perror("Error al crear el hilo");
            return 1;
        }   
        printf("Comenzando hilo %d\n", l);
        if(pthread_join(th[l], NULL) !=0){
            return 2;
        }
        printf("Finalizando hilo %d\n", l);
    }
    if(pthread_create(th + 10, NULL, &lowpassfilter, NULL) !=0){
            perror("Error al crear el hilo");
            return 3;
    }
    printf("Comenzando hilo %d\n", 2);
    if(pthread_join(th[10], NULL) !=0){
        return 4;
    }
    printf("Finalizando hilo %d\n", 10);
    
    if(pthread_create(th + 11, NULL, &exportcsv, NULL) !=0){
        perror("Error al crear el hilo");
        return 5;
    }
    printf("Comenzando hilo %d\n", 2);
    if(pthread_join(th[11], NULL) !=0){
        return 6;
    }
    
    pthread_mutex_destroy(&mutex);

    printf("Contador de j: %d\n", j);
    return 0;
}
    