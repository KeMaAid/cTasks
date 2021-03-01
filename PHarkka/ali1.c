/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/
//Tiedostonkäsittely
#include "ali1.h"
#include "ali2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define StringLen 32
#define taskCharLen 16
#define NumOfTasks 60
#define LenTime 16
#define printoutputformat "%s;%d\n"
#define printtimeformat "%d.%m.%Y"

readNode* readFile(){
    char fileName[StringLen];
    int iReturns;
    FILE *fPtr;
    readNode *pStart = NULL;
    findFile(fileName);

    if((fPtr = fopen(fileName, "r")) == NULL){
        perror("Tiedoston lukeminen epäonnistui");
        exit(1);
    }
    fscanf(fPtr, "%*s\n");  // luetaan otsikko
    
    // variables for max and min time
    struct tm *minTime;
    struct tm *maxTime;
    // luodaan bufferit tiedostonlukua varten
    char sTime[LenTime];
    char sTaskName[taskCharLen];
    int iTaskID;
    int iUserID;
    struct tm *pTime;
    while (fscanf(fPtr, "%s;%s;%d;%d", sTime, sTaskName, &iTaskID, &iUserID) != 0){
        iReturns++;
        strptime(sTime, "%d/%m/%y, %R", time);
        if(difftime(mktime(minTime), mktime(pTime)) > 0.0){
            minTime = pTime;
        } else if (difftime(mktime(maxTime), mktime(pTime)) < 0.0){
            maxTime = pTime;
        }
        pStart = addLList(pStart, pTime, sTaskName, taskCharLen, iTaskID, iUserID);
    }

    fclose(fPtr);

    //couple of buffers for strftime
    char minTimeBuffer[16];
    char maxTimeBuffer[16];
    strftime(minTimeBuffer, 16, printtimeformat, minTime);
    strftime(maxTimeBuffer, 16, printtimeformat, maxTime);
    
    printf("Yhteensä %d palautusta %s - %s väliseltä ajalta.", iReturns, minTimeBuffer, maxTimeBuffer);
    printf("\n");
    return pStart;
}

analNode* analFile(readNode * pStart){
    if(pStart == NULL){
        printf("Ei analysoitavaa, lue ensin palautustiedosto.\n");
        return NULL;
    }

    static analNode tasks[NumOfTasks];
    for(int i = 0; i<NumOfTasks; i++){
        strcpy(tasks[i].name, "Tyhjä");
        tasks[i].returns= 0;
    }

    for(readNode *ptr = pStart;ptr != NULL; ptr=ptr->pNext){
        strcpy(tasks[ptr->taskID-1].name, ptr->name);
        tasks[ptr->taskID-1].returns += 1;
    }

    printf("\n");
    return tasks;
}

void findFile(char * target){
    printf("Anna tiedoston nimi: ");
    scanf("%s", target);
}

int handleSaveChoice(){
    char buffer;
    printf("Tulosta tiedostoon (k/e)");
    scanf("%c", &buffer);

    if(buffer=='k'){
        return 1;
    } 
    return 0;
}

void saveToFile(analNode * pStart, int size){
    char fileName[StringLen];
    FILE *fptr;
    findFile(fileName);
    if((fptr=fopen(fileName, "w")) == NULL){
        perror("Tiedostoon kirjoittaminen epäonnistui");
    }
    fprintf(fptr, "Tehtävä;Lkm\n");
    for(int i=0; i<size; i++){
        fprintf(fptr, printoutputformat, pStart->name, pStart->returns);
        pStart++;
    }
    fclose(fptr);
}


void printFile(analNode * pStart, int size){
    if(pStart==NULL){
        printf("Ei tulostettavaa, analysoi ensin palautustiedosto.\n");
        return;
    }

    int saveFlag = handleSaveChoice();

    if(saveFlag){
        saveToFile(pStart, size);
    } else {
        printf("\n");
        printf("Tehtävä;Lkm\n");
        for(int i=0; i<size; i++){
            printf(printoutputformat, pStart->name, pStart->returns);
            pStart++;
        }
    }
    printf("\n");
}

