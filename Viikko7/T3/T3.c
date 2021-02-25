/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 2021.02.25
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/
#include <stdio.h>
#include "muisti.h"
#include "io.h"


int main(void){
    int iLot;
    int iAddlot;
    int* pStart;
    printf("Lottoarvonta\n");
    printf("Kuinka monta numeroa arvotaan: ");
    scanf("%d", &iLot);
    printf("Kuinka monta lisänumeroa arvotaan: ");
    scanf("%d", &iAddlot);
    printf("\n");
    pStart = varaaMuistiaNumerolle(iLot);
    arvoNumerot(pStart,iLot);
    printf("Arvottiin seuraavat numerot ja lisänumerot.\n");
    printf("Numerot: ");
    tulostaNumerot(pStart, iLot);
    printf("Lisänumerot: ");
    tulostaNumerot(pStart, iAddlot);
}
