#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Controllers.h"

int main(){
    int patients, cures;
    scanf("%d %d", &patients, &cures);

    for(int i=0;i<patients;i++){
        char name[255], month[255];
        int day, year;
        scanf("%d %s %d - %[^\n]", &day, &month, &year, &name);
        getchar();
        pushPQ(day, month, year, name);
    }
    patientCount=patients;
    cureCount=cures;
    popPQ();

    if(patientCount){
        printf("Need %d more cure\n", patientCount);
        printPQ();
    }
    else{
        printf("All patients are cured\n", cureCount);
    }

    return 0;
}