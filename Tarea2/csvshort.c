#include<stdio.h>
#include<string.h>

// function for creating and writing in file
void create_csv(){
    FILE *fp;
    int i;

    fp=fopen("Summary.csv","w+");

    fprintf(fp,"Raw,Filtered");

    for(i = 0; i < 200; i++){
        fprintf(fp,"\n%d",i);
    }
    fclose(fp);
    printf("\nfile created");
}

//main method
int main(){
    create_csv();
    return 0;
}