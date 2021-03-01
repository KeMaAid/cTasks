/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/
#include "ali2.h"

#ifndef ali1_h
#define ali1_h

readNode* readFile();
int printFile(analNode *pStart, int size);
int saveToFile(analNode * pStart, int size);
void findFile(char * target);
int handleSaveChoice();

#define StringLen 32
#define LenTime 16
#define printoutputformat "%s;%d\n"
#define timeinputformat  "%d/%m/%y, %R"
#define printtimeformat "%d.%m.%Y"

#endif