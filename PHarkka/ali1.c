/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 21-03-03
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/
//Tiedostonkäsittely
#include "ali1.h"
#include "ali2.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>


readNode* readFile(){
    int iReturns =0;
    char fileName[StringLen];
    FILE *fPtr;
    readNode *pStart = NULL;

    findFile(fileName);

    if((fPtr = fopen(fileName, "r")) == NULL){
        perror("Tiedoston lukeminen epäonnistui");
        return NULL;
    }
    fscanf(fPtr, "%*s\n");  // luetaan otsikko
    
    // variables for max and min time
    struct tm *minTime= strp(0,0,0,0,0);
    struct tm *maxTime= strp(0,0,0,0,0);

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

    while (fscanf(fPtr, "%d/%d/%d, %d:%d;%5s;%d;%d\n", &days, &months, &years, &hours, &minutes, sTaskName, &iTaskID, &iUserID) != -1){
        iReturns++;

        pTime = strp(years, months, days, hours, minutes);

        /*//debug
        char tstring[32];
        strftime(tstring,32,"%d/%m/%Y %H:%M",pTime);
        printf("Adding to list %s;%s;%d;%d\n", tstring, sTaskName, iTaskID, iUserID);
        */
        // finding first and last return
        if(minTime->tm_mday==0){
            //printf("  Setting first min and max\n");
            minTime=pTime;
            maxTime=pTime;
        } else if(difftime(mktime(minTime), mktime(pTime)) > 0.0){
            //printf(" Iter %d pTime %s is smallest\n", iReturns, tstring);
            minTime=pTime;
        } else if (difftime(mktime(maxTime), mktime(pTime)) < 0.0){
            //printf(" Iter %d pTime %s is largest\n", iReturns, tstring);
            maxTime=pTime;
        }
        pStart = addLList(pStart, pTime, sTaskName, taskCharLen, iTaskID, iUserID);
    }
    fclose(fPtr);

    //couple of buffers for strftime
    char minTimeBuffer[16];
    char maxTimeBuffer[16];
    strftime(minTimeBuffer, 16, printtimeformat, minTime);
    strftime(maxTimeBuffer, 16, printtimeformat, maxTime);
    free(minTime);
    free(maxTime);
    
    printf("Yhteensä %d palautusta %s - %s väliseltä ajalta.", iReturns, minTimeBuffer, maxTimeBuffer);
    printf("\n");
    return pStart;
}

void findFile(char * target){
    fflush(stdin); //tyhjennetään stdin
    printf("Anna tiedoston nimi: ");
    scanf("%s", target);
}

int handleSaveChoice(){
    fflush(stdin); // tyhjennetään stdin
    char buffer;
    printf("Tulosta tiedostoon (k/e): ");
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
        if(pStart->returns != 0){
            fprintf(fptr, printoutputformat, pStart->name, pStart->returns);
        }
        pStart++;
    }

    fclose(fptr);
    return 0;
}


int printFile(analNode * pStart, int size){
    if(pStart==NULL){
        printf("Ei tulostettavaa, analysoi ensin palautustiedosto.\n\n");
        return 2;
    }

    int saveFlag = handleSaveChoice();

    if(saveFlag){
        if(saveToFile(pStart, size)==1){
            return 1;
        }
    } else {
        //printf("\n");
        printf("Tehtävä;Lkm\n");
        for(int i=0; i<size; i++){
            if(pStart->returns != 0){
                printf(printoutputformat, pStart->name, pStart->returns);
            }
            pStart++;
        }
    }

    printf("\n");
    return 0;
}
