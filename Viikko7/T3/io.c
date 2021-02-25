/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 2021.02.25
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/

#include "io.h"
#include <stdlib.h>
#include <stdio.h>
#define max 37
#define min 0

void arvoNumerot(int *pNums, int iSize){
    srand(40);
    int iTemp;
    for(int i=0;i<iSize;i++){
        do{
            iTemp = rand() % (max +1);
        } while(tarkistaNumero(pNums, iTemp, iSize));
        *(pNums+i) = iTemp;
    }

}
int tarkistaNumero(int *pNums, int iTarget, int iSize){
    for(int i=0; i<iSize;i++){
        if(iTarget==*(pNums+i)){
            return 1;
        }
    }
    return 0;
}
void tulostaNumerot(int *pNums, int iSize){
    for(int i=0; i<iSize;i++){
        printf("%d ", *(pNums+i));
    }
    printf("\n");
}