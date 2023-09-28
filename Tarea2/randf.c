#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int mails = 0;
pthread_mutex_t mutex;


void* randn(){
   int base = -1;
   int top = 1;
   int count = 20;
   float ranvals[20];

   //srand(17);
   
   for(int i=0; i<count; i++){
      pthread_mutex_lock(&mutex);
      ranvals[i] = ((top - base)*((float)rand()/RAND_MAX)) + base;
      printf("Iteration: %d Ranvals: [%d] = %f\n", i+1, i, ranvals[i]);
      mails++;
      pthread_mutex_unlock(&mutex);
    }
    
}

void* lowpassfilter(){
   printf("Low pass\n");    
}


int main(int argc, char* argv[]){
    pthread_t p1, p2, p3, p4;
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);
    if(pthread_create(&p1, NULL, &randn, NULL) !=0){
        return 1;
    }
    if(pthread_create(&p2, NULL, &lowpassfilter, NULL) !=0){
        return 2;
    }
    
    if(pthread_join(p1, NULL) !=0){
        return 5;
    }
    if(pthread_join(p2, NULL) !=0){
        return 6;
    }
    pthread_mutex_destroy(&mutex);

    printf("Number of mails: %d\n", mails);
    return 0;

}
    