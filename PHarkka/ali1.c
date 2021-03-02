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
#include <stdio.h>
#include <time.h>


readNode* readFile(){
    char fileName[StringLen];
    int iReturns;
    FILE *fPtr;
    readNode *pStart = NULL;
    findFile(fileName);

    if((fPtr = fopen(fileName, "r")) == NULL){
        perror("Tiedoston lukeminen epäonnistui");
        return NULL;
    }
    fscanf(fPtr, "%*s\n");  // luetaan otsikko
    
    // variables for max and min time
    struct tm *minTime= NULL;
    struct tm *maxTime= NULL;
    // luodaan bufferit tiedostonlukua varten
    int minutes;
    int hours;
    int days;
    int months;
    int years;
    char sTaskName[taskCharLen];
    int iTaskID;
    int iUserID;
    struct tm *pTime;

    while (fscanf(fPtr, "%d/%d/%d, %d:%d;%s;%d;%d", &days, &months, &years, &hours, &minutes, sTaskName, &iTaskID, &iUserID) != -1){
        iReturns++;
        printf("LOOPING with iter: %d task %s\n", iReturns, sTaskName);
        pTime = strp(years, months, days, hours, minutes);

        if(minTime == NULL || maxTime == NULL){
            minTime = pTime;
            maxTime = pTime;
        } else if(difftime(mktime(minTime), mktime(pTime)) > 0.0){
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

int saveToFile(analNode * pStart, int size){
    char fileName[StringLen];
    FILE *fptr;
    findFile(fileName);

    if((fptr=fopen(fileName, "w")) == NULL){
        perror("Tiedostoon kirjoittaminen epäonnistui");
        return 1;
    }

    fprintf(fptr, "Tehtävä;Lkm\n");
    for(int i=0; i<size; i++){
        fprintf(fptr, printoutputformat, pStart->name, pStart->returns);
        pStart++;
    }

    fclose(fptr);
    return 0;
}


int printFile(analNode * pStart, int size){
    if(pStart==NULL){
        printf("Ei tulostettavaa, analysoi ensin palautustiedosto.\n");
        return 2;
    }

    int saveFlag = handleSaveChoice();

    if(saveFlag){
        if(saveToFile(pStart, size)==1){
            return 1;
        }
    } else {
        printf("\n");
        printf("Tehtävä;Lkm\n");
        for(int i=0; i<size; i++){
            printf(printoutputformat, pStart->name, pStart->returns);
            pStart++;
        }
    }

    printf("\n");
    return 0;
}
