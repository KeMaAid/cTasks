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
#include <time.h>

#define StringLen 32
#define taskCharLen 16

readNode* readFile(){
    char fileName[StringLen];
    FILE *fPtr;
    readNode *pStart = NULL;
    pritnf("Anna tiedoston nimi: ");
    scanf("%s",fileName);

    if((fPtr = fopen(fileName, "r")) == NULL){
        perror("Tiedoston lukeminen epäonnistui");
        exit(1);
    }
    fscanf(fPtr, "%*s\n");  // luetaan otsikko
    

    // luodaan bufferit tiedostonlukua varten
    char sTime[16];
    char sTaskName[taskCharLen];
    int iTaskID;
    int iUserID;
    struct tm *pTime;
    while (fscanf(fPtr, "%s;%s;%d;%d", sTime, sTaskName, iTaskID, iUserID) != NULL)
    {
        strptime(sTime, "%d/%m/%y, %R", pTime);
        pStart = addLList(pStart, &pTime, sTaskName, taskCharLen, iTaskID, iUserID);
    }

    fclose(fPtr);
    printf("\n");
}

analNode* analFile(readNode * pStart){




    printf("\n");
}

int printFile(analNode * pStart, int size){




    printf("\n");
}