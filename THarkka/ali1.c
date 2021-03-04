/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 21-03-04
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/

/*******************************************************************/
/* 
 * Tiedostoja käsittelevät aliohjelmat
 */
/*******************************************************************/

#include "ali1.h"
#include "ali2.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

/*
 * Function: readFile()
 * ----------------------
 * 
 * Aliohjelma kysyy käyttäjältä tiedoston nimen ja lukee sieltä
 * Palautusaika;TehtavaNimi;TehtavaID;KayttajaID tyypitettyä dataa
 * ja luo niistä linkitetyn listan jonka ensimmäisen elementin palauttaa
 * 
 * Returns: Linkitetyn listan ensimmäinen elementti
 */

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

        
        // finding first and last return
        if(minTime->tm_mday==0){
            memcpy(minTime, pTime, sizeof(struct tm));
            memcpy(maxTime, pTime, sizeof(struct tm));
        } else if(difftime(mktime(minTime), mktime(pTime)) > 0.0){
            memcpy(minTime, pTime, sizeof(struct tm));
        } else if (difftime(mktime(maxTime), mktime(pTime)) < 0.0){
            memcpy(maxTime, pTime, sizeof(struct tm));
        }
        pStart = addReadLList(pStart, pTime, sTaskName, taskCharLen, iTaskID, iUserID);
    }
    fclose(fPtr);

    //couple of buffers for strftime
    char minTimeBuffer[16];
    char maxTimeBuffer[16];
    strftime(minTimeBuffer, 16, printtimeformat, minTime);
    strftime(maxTimeBuffer, 16, printtimeformat, maxTime);
    free(minTime);
    free(maxTime);
    
    printf("Yhteensä %d palautusta %s - %s väliseltä ajalta.\n", iReturns, minTimeBuffer, maxTimeBuffer);
    return pStart;
}

/*
 * Function saveToFile
 * -------------------
 * 
 * avustaja funktio printFile funktiolle, tapauksessa jolloin pitää kirjoittaa tiedostoon
 * kysyy käyttäjältä tiedoston nimen ja kirjoittaa yli formaatilla
 * Tehtävä;Lkm
 * 
 * pStart: analNode tyyppisen listan ensimmäinen osoitin
 * size: listan koko
 * 
 * Returns: 0 jos onnistui
 *          1 jos epäonnistui
 */

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

/*
 * Function printFile
 * -------------------
 * 
 * analNode tyyppisen tiedoston kirjoittaminen tiedostoon tai terminaaliin
 * Tehtävä;Lkm
 * 
 * pStart: analNode tyyppisen listan ensimmäinen osoitin
 * size: listan koko
 * 
 * Returns: 0 jos onnistui
 *          1 jos epäonnistui
 */

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
        printf("Tehtävä;Lkm\n");
        for(int i=0; i<size; i++){
            printf(printoutputformat, pStart->name, pStart->returns);
            pStart++;
        }
    }

    return 0;
}


/*
 * Function saveDayToFile
 * -------------------
 * 
 * avustaja funktio printDayFile funktiolle, tapauksessa jolloin pitää kirjoittaa tiedostoon
 * kysyy käyttäjältä tiedoston nimen ja kirjoittaa yli formaatilla
 * Pvm;Lkm
 * 
 * pStart: dayAnalNode tyyppisen linkitetyn listan ensimmäinen osoitin
 * 
 * Returns: 0 jos onnistui
 *          1 jos epäonnistui
 */

int saveDayToFile(dayAnalNode * pStart){
    char fileName[StringLen];
    char sBuffer[LenTime];
    FILE *fptr;
    findFile(fileName);

    if((fptr=fopen(fileName, "w")) == NULL){
        perror("Tiedostoon kirjoittaminen epäonnistui");
        return 1;
    }

    fprintf(fptr, "Pvm;Lkm\n");
    for(dayAnalNode *ptr = pStart;ptr != NULL; ptr=ptr->pNext){
        strftime(sBuffer, LenTime, printtimeformat, ptr->time);
        fprintf(fptr, printoutputformat, sBuffer, ptr->returns);
    }
    fclose(fptr);
    return 0;
}

/*
 * Function printDayFile
 * -------------------
 * 
 * analNode tyyppisen tiedoston kirjoittaminen tiedostoon tai terminaaliin kysyy käyttäjältä.
 * Pvm;Lkm
 * 
 * pStart: dayAnalNode tyyppisen linkitetyn listan ensimmäinen osoitin
 * 
 * Returns: 0 jos onnistui
 *          1 jos epäonnistui
 */

int printDayFile(dayAnalNode * pStart){
    if(pStart==NULL){
        printf("Ei tulostettavaa, suorita ensin päiväanalyysi.\n");
        return 2;
    }
    char sBuffer[LenTime];
    int saveFlag = handleSaveChoice();

    if(saveFlag){
        if(saveDayToFile(pStart)==1){
            return 1;
        }
    } else {
        printf("Pvm;Lkm\n");
        for(dayAnalNode *ptr = pStart;ptr != NULL; ptr=ptr->pNext){
            strftime(sBuffer, LenTime, printtimeformat, ptr->time);
            printf(printoutputformat, sBuffer, ptr->returns);
        }
    }

    return 0;
}
