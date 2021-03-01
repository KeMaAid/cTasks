/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/
#include <time.h>

#ifndef ali2_h
#define ali2_h

#define taskCharLen 16

typedef struct readNode {
    struct tm time;
    char name[taskCharLen];
    int taskID;
    int userID;
    readNode pNext;
} readNode;

typedef struct analNode {
    char name[taskCharLen];
    int returns; 
} analNode;

//void printLList(readNode *pStart);
readNode * addLList(readNode *pStart, struct tm *pTime, char * sTaskName, int iNameLength, int iTaskID, int iUserID);
readNode * freeLList(readNode *pStart);
readNode * removeLList(readNode *pStart, int index);

#endif