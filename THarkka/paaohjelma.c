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
 * Main ja sille menu-apufunktio
 * 
 */
/*******************************************************************/

#include "ali1.h"
#include "ali2.h"
#include <stdio.h>
#define NumOfTasks 60

int menu(void){
    int temp;
    printf("1) Lue tiedosto\n");
    printf("2) Analysoi tiedot\n");
    printf("3) Tulosta tulokset\n");
    printf("4) Suorita päiväanalyysi\n");
    printf("5) Tulosta päiväanalyysin tulokset\n");
    printf("6) Tyhjennä tuloslista\n");
    printf("0) Lopeta\n");
    printf("Valintasi: ");
    scanf("%d", &temp);
    fflush(stdin);
    return(temp);
}

int main(void){
    int loopFlag =1;
    readNode *pReadStart = NULL;
    analNode pAnalList[NumOfTasks];
    dayAnalNode *pDayAnalStart = NULL;
    while(loopFlag){
        switch (menu()){
        case 0:
            freeReadLList(pReadStart);
            freeAnalLList(pDayAnalStart);
            loopFlag = 0; //ihan hyvin vois käyttää loputonta silmukkaa ja goto:a (säästäisi pari mikrokoodiriviä ja pari bittiä)
            break;
        case 1:
            pReadStart = freeReadLList(pReadStart);
            pReadStart = readFile();
            printf("\n");
            break;
        case 2:
            analFile(pReadStart, pAnalList, NumOfTasks);
            printf("\n");
            break;
        case 3:
            printFile(pAnalList, NumOfTasks);
            printf("\n");
            break;
        case 4:
            //pDayAnalStartista alkaa Linkitettyä listaa ei poisteta, sillä käyttäjä voi haluta monta eri päivähaarukkaa tulostukseen.
            pDayAnalStart = dayAnalFile(pDayAnalStart, pReadStart);
            printf("\n");
            break;
        case 5:
            printDayFile(pDayAnalStart);
            printf("\n");
            break;
        case 6:
            pDayAnalStart = freeAnalLList(pDayAnalStart);
            printf("\n");
            break;
        default:
            printf("Tuntematon valinta, yritä uudestaan.\n\n");
            break;
        }
    }
    printf("Kiitos ohjelman käytöstä.\n\n");
}
