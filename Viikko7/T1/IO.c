/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 2021.02.24
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/
#include "IO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define fileName "askeldata.txt"

int lue_askeleet_listaan(int * pStart, int size){
    memset(pStart, 0, size*sizeof(int));
    int steps=0;
    int sum=0;
    FILE *pFile;

    if((pFile = fopen(fileName, "r")) == NULL){
        perror("Tiedoston luvussa virhe");
        exit(0);
    }

    for(int i=0; (fscanf(pFile, "%*d.%*d.%*d:%d\n", &steps) !=0) && i<size; i++){
        *(pStart+i)= steps;
        sum += steps;
    }

    fclose(pFile);
    return sum;
}
void tulosta_lista(int * pStart, int size){
    printf("Listan askeleet: ");
    for(int i=0;i<size;i++){
        printf("%d ", *(pStart+i));
    }
    printf("\n");
}