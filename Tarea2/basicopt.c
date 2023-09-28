#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */

int sum;
void *runner(void *param);

int main(int argc, char *argv[]){
    pthread_t tid;
    pthread_attr_t attr;

    if(argc != 2){
        fprintf(stderr, "usage: a.out <integer value>\n");
        return -1;
    }

    if (atoi(argv[1])<0){
        fprint(stderr, "%d must be >= 0 \n", atoi(argv[1]));
        return -1;
    }

    pthread_attr_init(*attr);
    pthread_create(&tid, &attr, runner, argv[1]);
    pthread_join(tid, NULL);

    fprintf("sum = %d\n", sum);
}

void *runner(void *param){
    int i, upper = atoi(param);
    sum = 0;

    for (i=1; i<= upperl i++)
        sum += i;
    
    pthread.exit(0);
}