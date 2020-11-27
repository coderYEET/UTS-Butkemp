#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Model.h"

int patientCount, cureCount;
char months[12][255]={"january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"};

Patient* createNode(int day, char month[], int year, char name[]){
    Patient* newNode =(Patient*)malloc(sizeof(Patient));

    newNode->day=day;
    strcpy(newNode->month, month);
    newNode->year=year;
    strcpy(newNode->name, name);

    newNode->next=newNode->prev=NULL;

    return newNode;
}

void pushPQ(int day, char month[], int year, char name[]){
    Patient* newNode=createNode(day, month, year, name);

    if(!head){
        head=tail=newNode;
    }
    else if(year < head->year){
        newNode->next=head;
        head->prev=newNode;
        head=newNode;
    }
    else if(year > tail->year){
        newNode->prev=tail;
        tail->next=newNode;
        tail=newNode;
    }
    else{
        Patient* curr=head;

        while(curr && curr->next->year < newNode->year){
            curr=curr->next;
        }

        if(curr->year == newNode->year){
            int newNodevalue, currvalue;
            for(int i=0;i<12;i++){
                if(!strcmp(newNode->month,months[i])){
                    newNodevalue=i;
                    break;
                }
            }
            for(int i=0;i<12;i++){
                if(!strcmp(curr->month,months[i])){
                    currvalue=i;
                    break;
                }
            }
            if(newNodevalue < currvalue){
                newNode->next=curr;
                newNode->prev=curr->prev;
                curr->prev->next=newNode;
                curr->prev=newNode;
            }
            else if(newNodevalue > currvalue){
                curr->next->prev=newNode;
                newNode->next=curr->next;
                curr->next=newNode;
                newNode->prev=curr;
            }
            else{
                if(newNode->day < curr->day){
                    newNode->next=curr;
                    newNode->prev=curr->prev;
                    curr->prev->next=newNode;
                    curr->prev=newNode;
                }
                else if(newNode->day > curr->day){
                    curr->next->prev=newNode;
                    newNode->next=curr->next;
                    curr->next=newNode;
                    newNode->prev=curr;
                }
                else{
                    int i=0;
                    while(i<strlen(newNode->name) && i>strlen(curr->name)){
                        if(newNode->name[i] < curr->name[i]){
                            curr->next->prev=newNode;
                            newNode->next=curr->next;
                            curr->next=newNode;
                            newNode->prev=curr;
                            break;
                        }
                        else{
                            newNode->next=curr;
                            newNode->prev=curr->prev;
                            curr->prev->next=newNode;
                            curr->prev=newNode;
                            break;
                        }
                        i++;
                    }
                }
            }
        }
        else{
            curr->next->prev=newNode;
            newNode->next=curr->next;
            curr->next=newNode;
            newNode->prev=curr;
        }
    }
}

void popPQ(){
    while(patientCount && cureCount){
        Patient* temp = tail->prev;
        temp->next=tail->prev=NULL;
        free(tail);
        tail=temp;
        patientCount--;
        cureCount--;
    }
}

void printPQ(){
    Patient* curr=head;

    while(curr){
        printf("%d %s %d - %s\n", curr->day, curr->month, curr->year, curr->name);
        curr=curr->next;
    }
}