/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 21-03-03
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/
//muut aliohjelmat
#include "ali2.h"
#include "ali1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

readNode * addReadLList(readNode *pStart, struct tm *pTime, char * sTaskName, int iNameLength, int iTaskID, int iUserID){
    readNode *pNew, *ptr;

    if((pNew = (readNode*)malloc(sizeof(readNode)))== NULL){
        printf("Muistin varaus epäonnistui.\n");
        exit(1);
    }

    //setting the new node
    pNew->time=pTime;
    strncpy(pNew->name, sTaskName, iNameLength);
    pNew->taskID=iTaskID;
    pNew->userID=iUserID;
    pNew->pNext=NULL;

    //adding node to list
    if(pStart == NULL){
        pNew->pNext=pStart;
        pStart= pNew;
    } else {
        int i = 1;
        for(ptr = pStart;;ptr=ptr->pNext){
            if(ptr->pNext == NULL){
                ptr->pNext=pNew;
                break;
            }
            i++;
        }
    }
    return pStart;
}

dayAnalNode * addLList(dayAnalNode *pStart, struct tm *pTime, int iReturns){
    dayAnalNode *pNew, *ptr;

    if((pNew = (dayAnalNode*)malloc(sizeof(dayAnalNode)))== NULL){
        printf("Muistin varaus epäonnistui.\n");
        exit(1);
    }

    //setting the new node
    pNew->time=pTime;
    pNew->returns=iReturns;
    pNew->pNext=NULL;

    //adding node to list
    if(pStart == NULL){
        pNew->pNext=pStart;
        pStart= pNew;
    } else {
        int i = 1;
        for(ptr = pStart;;ptr=ptr->pNext){
            if(ptr->pNext == NULL){
                ptr->pNext=pNew;
                break;
            }
            i++;
        }
    }
    return pStart;
}

readNode * freeReadLList(readNode *pStart){
    readNode *ptr = pStart;

    while(ptr != NULL){
        pStart = ptr->pNext;
        free(ptr);
        ptr = pStart;
    }

    return NULL;
}

dayAnalNode * freeAnalLList(dayAnalNode *pStart){
    dayAnalNode *ptr = pStart;

    while(ptr != NULL){
        pStart = ptr->pNext;
        free(ptr);
        ptr = pStart;
    }

    return NULL;
}

void analFile(readNode *pStart, analNode * tasks, int analListSize){
    if(pStart == NULL){
        printf("Ei analysoitavaa, lue ensin palautustiedosto.\n");
        return;
    }

    int numOfReturns = 0;
    int numOfReturnedTasks = 0;
    int iAverage = 0;

    
    for(int i = 0; i<analListSize; i++){
        strcpy(tasks[i].name, "Tyhjä");
        tasks[i].returns= 0;
    }

    //Genereting the analList
    for(readNode *ptr = pStart;ptr != NULL; ptr=ptr->pNext){
        strcpy(tasks[(ptr->taskID)-1].name, ptr->name);
        tasks[(ptr->taskID)-1].returns += 1;
    }

    //Analysing
    for(int i=0; i<analListSize;i++){
        if(tasks[i].returns != 0){
            numOfReturnedTasks++;
        }
        numOfReturns += tasks[i].returns;
    }
    iAverage = numOfReturns / numOfReturnedTasks;

    printf("Palautuksia oli yhteensä %d, %d eri tehtävässä, keskimäärin %d per tehtävä.\n", numOfReturns, numOfReturnedTasks, iAverage);
    return;
}

dayAnalNode * dayAnalFile(dayAnalNode * pAnalStart, readNode *pReadStart){
    if(pReadStart == NULL){
        printf("Ei analysoitavaa, lue ensin palautustiedosto.\n");
        return NULL;
    }
    // variables for max and min time
    struct tm *minTime= strp(0,0,0,0,0);
    struct tm *maxTime= strp(0,0,0,0,0);

    // luodaan bufferit tiedostonlukua varten
    int days;
    int months;
    int years;

    printf("Anna alku pvm (pp.mm.vvvv): ");
    scanf("%d.%d.%d", &days, &months, &years);
    minTime = strp(years, months,days, 0, 0);
    printf("Anna loppu pvm (pp.mm.vvvv): ");
    scanf("%d.%d.%d", &days, &months, &years);
    maxTime = strp(years, months,days, 0, 0);

    int totNumOfReturns = 0;
    int numOfReturns = 0;
    struct tm *pLastTime = minTime;
    for(readNode *ptr=pReadStart; pReadStart != NULL; ptr=ptr->pNext){
        if((difftime(mktime(minTime), mktime(ptr->time)) < 0.0) && (difftime(mktime(maxTime), mktime(ptr->time)) > 0.0)){
            totNumOfReturns++;

            if(pLastTime->tm_year==ptr->time->tm_year && pLastTime->tm_mon==ptr->time->tm_mon && pLastTime->tm_mday== ptr->time->tm_mday){
                numOfReturns++;
            } else {
                pAnalStart= addAnalLList(pAnalStart, pLastTime, numOfReturns);
                numOfReturns=1;
            }
        }
    }
    pAnalStart= addAnalLList(pAnalStart, pLastTime, numOfReturns);


    //couple of buffers for strftime
    char minTimeBuffer[16];
    char maxTimeBuffer[16];
    strftime(minTimeBuffer, 16, printtimeformat, minTime);
    strftime(maxTimeBuffer, 16, printtimeformat, maxTime);
    free(minTime);
    free(maxTime);
    
    printf("Palautuksia oli yhteensä %d aikavälillä %s - %s.\n", totNumOfReturns, minTimeBuffer, maxTimeBuffer);
    return pAnalStart;
}


struct tm * strp(int years, int months, int days, int hours, int minutes){
    struct tm *pNew;
    if((pNew = (struct tm*)malloc(sizeof(struct tm)))== NULL){
        printf("Muistin varaus epäonnistui.\n");
        exit(1);
    }
    memset(pNew,0,sizeof(struct tm));

    //adding data to pTime
    pNew->tm_min=minutes;
    pNew->tm_hour=hours;
    pNew->tm_mday=days;
    pNew->tm_mon=months-1;
    pNew->tm_year=years+100;

    return pNew; 
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