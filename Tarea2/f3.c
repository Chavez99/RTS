#include<stdio.h>
#include<string.h>

// function for creating and writing in file
void create_marks_csv(){
    FILE *fp;
    int i, count, id, micro, dcn, ds, rd;

    //printf("\n Creating %s.csv file",filename);
    //filename=strcat(filename,".csv");

    fp=fopen("Summary.csv","w+");

    fprintf(fp,"Student Id, Microprocessor, RDMBMS, DCN, DS");
    printf("How many student's marks do you want to save?");
    //scanf("%d", &count);

    for(i = 0; i < 200; i++){
        fprintf(fp,"\n%d",i);
    }
    fclose(fp);
    //printf("\n %sfile created",filename);


    printf("\nfile created");
}

//main method
int main(){
    char str[100];
    //clrscr();
    printf("\n Enter the filename :");
    scanf("%s", str);

    //fgets(str);
    create_marks_csv();

    return 0;
}