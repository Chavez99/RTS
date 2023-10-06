//#include <pthread.h>
//#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <time.h>

int main(void){
    FILE *fp;
    fp = fopen("newf.csv", "w");

    if(fp = NULL){
        printf("File err");
        //system("pause");
        return 1;
    }
    fprintf(fp, "1,2,3");

    fclose(fp);
    fp = 0;
    //system("pause");
    return 0;
}

