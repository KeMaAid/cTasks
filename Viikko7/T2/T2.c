/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 2021.02.24
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int menu(void){
    int buffer;
    printf("1) Luo lista\n");
    printf("2) Lisää alkio listan loppuun\n");
    printf("3) Lisää alkio listan keskelle\n");
    printf("4) Tyhjennä lista\n");
    printf("5) Poista alkio listasta\n");
    printf("6) Tulosta lista\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &buffer);
    return buffer;
};

int main(void){
    int loopFlag = 1;
    int nextCallNumber=1;
    Node *pListStart = NULL;
    printf("Tämä ohjelma hallitsee listaa ja sen alkioita.\n");
    while(loopFlag){
        switch(menu()){
            case 0:
                loopFlag=0;
                break;
            case 1:
                pListStart = createLList(&nextCallNumber);
                printLList(pListStart);
                break;
            case 2:
                pListStart = addLList(pListStart, -1, &nextCallNumber);
                printLList(pListStart);
                break;
            case 3:
                //TODO add mechanism to find index to insert
                pListStart = addLList(pListStart, -1, &nextCallNumber);
                printLList(pListStart);
                break;
            case 4:
                pListStart = freeLList(pListStart);
                break;
            case 5:
                //TODO add mechanism to find index to insert
                pListStart = removeLList(pListStart, -1);
                break;
            case 6:
                printLList(pListStart);
                break;
            default:
                printf("Tuntematon valinta, yritä uudestaan.\n");
                break;
        }
    }
    pListStart = freeLList(pListStart);
    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}
