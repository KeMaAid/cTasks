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
#include <stdlib.h>
#include <stdio.h>
#define reads 10

int main(void){
    int list[reads];
    int sum;
    printf("Askelanalyysi\n");
    sum = lue_askeleet_listaan(list, reads);
    tulosta_lista(list, reads);
    printf("Askelia yhteensä: %d\n", sum);
    return 0;
}