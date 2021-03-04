/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 21-03-02
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/
//main ja valikko

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
    printf("6) Tyhjennä tuloslista");
    printf("0) Lopeta\n");
    printf("Valintasi: ");
    scanf("%d", &temp);
    return(temp);
}

int main(void){
    int loopFlag =1;
    readNode *pReadStart = NULL;
    analNode pAnalList[NumOfTasks];
    dayAnalNode *pDayAnalStart = NULL;
    while(loopFlag){
        switch (menu())
        {
        case 0:
            freeLList(pReadStart);
            freeLList(pDayAnalStart);
            loopFlag = 0; //ihan hyvin vois käyttää loputonta silmukkaa ja goto:a (säästäisi pari mikrokoodiriviä ja pari bittiä)
            break;
        case 1:
            pReadStart = freeLList(pReadStart);
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
            pDayAnalStart = dayAnalFile(pDayAnalStart, pReadStart);
            printf("\n");
            break;
        case 5:
            printDayFile(pDayAnalStart);
            printf("\n");
            break;
        case 6:
            pDayAnalStart = freeLList(pDayAnalStart);
            printf("\n");
            break;
        default:
            printf("Tuntematon valinta, yritä uudestaan.\n\n");
            break;
        }
    }
    printf("Kiitos ohjelman käytöstä.\n\n");
}
