/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 21-03-05
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/

/*******************************************************************/
/*
 * Tiedosto kaikille muille alifunktioille
 */
/*******************************************************************/
#include "ali2.h"
#include "ali1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//MAKRO: seuraavalle kahdelle ohjelmalle

#define addToEndOfList {\
    if(pStart == NULL){\
        pNew->pNext=pStart;\
        pStart= pNew;\
    } else {\
        int i = 1;\
        for(ptr = pStart;;ptr=ptr->pNext){\
            if(ptr->pNext == NULL){\
                ptr->pNext=pNew;break;\
            }\
            i++;\
        }\
    }\
}
/*
 * Function: addReadLList
 * ----------------------
 * 
 * Funktio joka saa parametreinaan tiedot readNode tyyppisen rakentteen täyttämiseksi.
 * Funktio luo linkitetyn listan tai lisää uuden elementin viimeiseksi
 * 
 * !!Funktio kaataa ohjelman jos muistinvaraus ei onnistu!!
 * 
 * pStart: Ensimmäisen elementin osoite
 *         jos NULL niin lisätään uusi elementti ensimmäiseksi
 * sTaskName: Tehtävän nimike
 * iNameLength: nimen pituus, käytetään kopioinnissa rakenteeseen
 * iTaskID: Tehtävän Numerollinen tunnus
 * iUserID: Opiskeljanumero
 * 
 * Returns: Linkitetyn listan ensimmäisen elementin osoite
 */ 

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

    //adding node to end of list
    addToEndOfList;
    return pStart;
}

/*
 * Function: addAnalLList
 * ----------------------
 * 
 * Kopio funktiosta addReadLList, toiselle tietuetyypille.
 * Funktio luo linkitetyn listan ensimmäisen elementin tai lisää uuden elementin viimeiseksi
 * 
 * !!Funktio kaataa ohjelman jos muistinvaraus ei onnistu!!
 * 
 * pStart: Ensimmäisen elementin osoite
 *         jos NULL niin lisätään uusi elementti ensimmäiseksi
 * pTime: Osoite aikatietuelle
 *          katso että aikatietue on kunnolla varatulla muistilla.
 * iReturns: palautuksien määrä kyseiselle päivälle
 * 
 * 
 * Returns: Linkitetyn listan ensimmäisen elementin osoite
 */ 

dayAnalNode * addAnalLList(dayAnalNode *pStart, struct tm *pTime, int iReturns){
    dayAnalNode *pNew, *ptr;

    if((pNew = (dayAnalNode*)malloc(sizeof(dayAnalNode)))== NULL){
        printf("Muistin varaus epäonnistui.\n");
        exit(1);
    }

    //generating a copy of pTime
    struct tm *pTimeLocal;
    if((pTimeLocal = (struct tm*)malloc(sizeof(struct tm)))== NULL){
        printf("Muistin varaus epäonnistui.\n");
        exit(1);
    }
    memcpy(pTimeLocal, pTime, sizeof(struct tm));


    //setting the new node
    pNew->time=pTimeLocal;
    pNew->returns=iReturns;
    pNew->pNext=NULL;

    //adding node to end of list
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


/*
 * Functio freeReadLList ja freeAnalLList
 * --------------------------------------
 * 
 * Funktioiden tehtävä on tyhjentää niille annettu lista
 * Funktioilla on sama toteutus, joka on nyt esitetty makron kanssa
 * 
 * Returns: NULL
 */
#define freeLList {\
    while(ptr != NULL){\
        pStart = ptr->pNext;\
        free(ptr);\
        ptr = pStart;\
        }\
    return NULL;\
    }

readNode * freeReadLList(readNode *pStart){
    readNode *ptr = pStart;
    freeLList;
}

dayAnalNode * freeAnalLList(dayAnalNode *pStart){
    dayAnalNode *ptr = pStart;
    freeLList;
}

/*
 * Function analFile
 * -----------------
 * 
 * Funktio analysoi readNode tyyppisen linkitetyn listan ja tulostaa analyysin konsoliin.
 * Analyysissä paulautuksien määrä, palautettujen tehtävien määrä ja näiden keskiverto
 * 
 * pStart: Linkitetyn listan ensimmäinen osoite
 * tasks: kirjoitettavan tiedostolistan osoite
 * size: kirjoitettavan tiedostolistan koko
 * 
 * Returns: void
 */

void analFile(readNode *pStart, analNode * tasks, int size){
    if(pStart == NULL){
        printf("Ei analysoitavaa, lue ensin palautustiedosto.\n");
        return;
    }

    int numOfReturns = 0;
    int numOfReturnedTasks = 0;
    int iAverage = 0;

    
    for(int i = 0; i<size; i++){
        strcpy(tasks[i].name, "Tyhjä");
        tasks[i].returns= 0;
    }

    //Genereting the analList
    for(readNode *ptr = pStart;ptr != NULL; ptr=ptr->pNext){
        strcpy(tasks[(ptr->taskID)-1].name, ptr->name);
        tasks[(ptr->taskID)-1].returns += 1;
    }

    //Analysing
    for(int i=0; i<size;i++){
        if(tasks[i].returns != 0){
            numOfReturnedTasks++;
        }
        numOfReturns += tasks[i].returns;
    }
    iAverage = numOfReturns / numOfReturnedTasks;

    printf("Palautuksia oli yhteensä %d, %d eri tehtävässä, keskimäärin %d per tehtävä.\n", numOfReturns, numOfReturnedTasks, iAverage);
    return;
}

/*
 * Function dayAnalNode
 * ---------------------
 * 
 * Kysyy käyttäjältä kaksi päivää ja analysoi päiviän välissä tapahtuneet palautukset (myös merkatut päivät)
 *  
 * pAnalStart: tallennettavaan linkitetyn lstan ensimmäisen tietuen osoite
 * pReadStart: luettavan linkitetyn listan ensimmäisen tietueen osoite
 * 
 * Returns: tallennus Linkitetyn listan ensimmäinen osoite
 *          tai NULL, jos ei ole luettavaa listaa
 */

#define daySeconds 86400

dayAnalNode * dayAnalFile(dayAnalNode * pAnalStart, readNode *pReadStart){
    if(pReadStart == NULL){
        printf("Ei analysoitavaa, lue ensin palautustiedosto.\n");
        return NULL;
    }

    // variables for max and min time
    struct tm *minTime;
    struct tm *maxTime;

    // luodaan bufferit päivämäärien asettamista varten
    int days;
    int months;
    int years;

    fflush(stdin);
    printf("Anna alku pvm (pp.mm.vvvv): ");
    scanf("%d.%d.%*2d%d", &days, &months, &years);
    minTime = strp(years, months, days, 0, 0, 0);
    printf("Anna loppu pvm (pp.mm.vvvv): ");
    scanf("%d.%d.%*2d%d", &days, &months, &years);
    maxTime = strp(years, months, days, 23, 59, 59);



    time_t compTime= mktime(minTime); //used as a stepper for days
    //luodaan linkitetty lista, johon syötetään dataa
    int diffdays = (difftime(mktime(maxTime), mktime(minTime)) / daySeconds);
    for(int i = 0;i<=diffdays;i++){
        pAnalStart= addAnalLList(pAnalStart, localtime(&compTime), 0);
        compTime += daySeconds;
    }

    int numOfReturns = 0;
    //analysoidaan
    for(readNode *ptr=pReadStart;ptr != NULL;ptr=ptr->pNext){
        compTime = mktime(ptr->time);
        if(difftime(mktime(minTime), compTime) < 0.0){
            /*if(difftime(mktime(maxTime), compTime) < -daySeconds){
                break;
            }*/
            printf("Current day in outer loop %d.%d.%d\n", ptr->time->tm_mday, ptr->time->tm_mon+1, ptr->time->tm_year+1900);
            for(dayAnalNode *ptrAnal=pAnalStart;ptrAnal != NULL;ptrAnal=ptrAnal->pNext){
                printf(" Current day in inner loop %d.%d.%d\n", ptrAnal->time->tm_mday, ptrAnal->time->tm_mon+1, ptrAnal->time->tm_year+1900);
                //jos molemmissa on päivä sama
                if(ptr->time->tm_year==ptrAnal->time->tm_year && ptr->time->tm_mon==ptrAnal->time->tm_mon && ptr->time->tm_mday==ptrAnal->time->tm_mday){
                    printf("  Adding a return\n");
                    numOfReturns++;
                    ptrAnal->returns +=1;
                    break;
                }         
            }
        }
    }
    


    //couple of buffers for strftime
    char minTimeBuffer[16];
    char maxTimeBuffer[16];
    strftime(minTimeBuffer, LenTime, printtimeformat, minTime);
    strftime(maxTimeBuffer, LenTime, printtimeformat, maxTime);
    free(minTime);
    free(maxTime);
    
    return pAnalStart;
}


/*
 * Function strp
 * -------------
 * 
 * Funktio varaa aikatietueelle tilaa ja täyttää sen parametreillä
 * 
 * !! Kaataa ohjelman jos ei pysty varaamaan muistia !!
 * 
 * Returns: Pointer to a newly allocated tm struct
 */

struct tm * strp(int years, int months, int days, int hours, int minutes, int seconds){
    struct tm *pNew;

    if((pNew = (struct tm*)malloc(sizeof(struct tm)))== NULL){
        printf("Muistin varaus epäonnistui.\n");
        exit(1);
    }
    memset(pNew,0,sizeof(struct tm));


    //adding data to pTime
    pNew->tm_sec=seconds;
    pNew->tm_min=minutes;
    pNew->tm_hour=hours;
    pNew->tm_mday=days;
    pNew->tm_mon=months-1;
    pNew->tm_year=years+100;

    printf("  strp:  %d.%d.%d %d:%d\n", pNew->tm_mday, pNew->tm_mon+1, pNew->tm_year+1900, pNew->tm_hour, pNew->tm_min);
    return pNew; 
}

/*
 * Function findFile
 * -----------------
 * 
 * Kysyy käyttäjältä tiedostonnimen ja sijoittaa parametreissa annettuun muistipaikkaan
 * 
 * target: kohde mihin kirjoitetaan tiedostonnimi
 * 
 * Returns: void
 */

void findFile(char * target){
    fflush(stdin); //tyhjennetään stdin
    printf("Anna tiedoston nimi: ");
    scanf("%s", target);
}

/*
 * Function handleSaveChoice
 * -------------------------
 * 
 * Kysyy käyttäjältä tallennetaanko tiedostoon vai tulostetaanko näytölle
 * 
 * Returns: 1, jos syöte on k
 *          0, jos syöte on jotain muuta
 */

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