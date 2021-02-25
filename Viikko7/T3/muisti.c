/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 2021.02.25
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/
#include <stdlib.h>
#include "muisti.h"

int* varaaMuistiaNumerolle(int size){
    int *ptr;
    if((ptr = (int*)malloc(sizeof(int)*size))== NULL){
        perror("Muistin varaus epäonnistui!\n");
        exit(0);
    }
    return ptr;
}
void vapautaMuisti(int* ptr){
    free(ptr);
}