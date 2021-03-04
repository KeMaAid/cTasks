/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 21-03-04
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/

/*******************************************************************/
/* 
 * Header files for ali1.c
 * esittelee funktiot ja määrittelee monessa paikkaa esiintyvät vakiot
 */
/*******************************************************************/
#include "ali2.h"

#ifndef ali1_h
#define ali1_h

readNode* readFile();
int printFile(analNode *pStart, int size);
int saveToFile(analNode * pStart, int size);
int printDayFile(dayAnalNode *pStart);
int saveDayToFile(dayAnalNode *pStart);

#define StringLen 32 
#define LenTime 16
#define printoutputformat "%s;%d\n"
#define printtimeformat "%d.%m.%Y"

#endif