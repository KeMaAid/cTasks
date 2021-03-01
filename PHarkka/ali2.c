/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/
//muut aliohjelmat
#include "ali2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*void printLList(readNode *pStart){
    if(pStart == NULL){
        //printf("Lista on tyhjä.\n");
        printf("\n");
        return;
    }
    //printf("Listassa on seuraavat luvut: \n");
    for(readNode *ptr = pStart;ptr != NULL; ptr=ptr->pNext){
        printf("%d ", ptr->value);
    }
    printf("\n");
}*/

readNode * addLList(readNode *pStart, struct tm *pTime, char * sTaskName, int iNameLength, int iTaskID, int iUserID){
    readNode *pNew, *ptr;
    if((pNew = (readNode*)malloc(sizeof(readNode)))== NULL){
        printf("Muistin varaus epäonnistui.\n");
        exit(0);
    }

    pNew->time=*(pTime);
    strncpy(pNew->name, sTaskName, iNameLength);
    pNew->taskID=iTaskID;
    pNew->userID=iUserID;
    pNew->pNext=NULL;

    if(pStart == NULL){
        pNew->pNext=pStart;
        pStart= pNew;
    } else {
        int i = 1;
        for(ptr = pStart;;ptr=ptr->pNext){
            /*
            insertion code
            if(i==index){
                pNew->pNext = ptr->pNext;
                ptr->pNext=pNew;
                break;
            }
            */
            if(ptr->pNext == NULL){
                ptr->pNext=pNew;
                break;
            }
            i++;
        }
    }
    return pStart;
}

readNode * freeLList(readNode *pStart){
    readNode *ptr = pStart;
    while(ptr != NULL){
        pStart = ptr->pNext;
        free(ptr);
        ptr = pStart;
    }
    return pStart;
}
/*
readNode * removeLList(readNode *pStart, int index){
    if(index < 0 ){
        return pStart;
    }
    readNode *ptr;
    int i = 0;
    for(ptr = pStart;ptr != NULL;ptr=ptr->pNext){
        i++;
        if(i==index){
            readNode * tmp = ptr->pNext->pNext;
            free(ptr->pNext);
            ptr->pNext=tmp;
        }
    }
    return pStart;
}
*/
