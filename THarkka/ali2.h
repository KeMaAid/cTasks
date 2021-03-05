/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 21-03-05
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/

/*******************************************************************/
/* 
 * Headerit ali2.c
 * Määrittää rakenteet readNode, analNode ja dayAnalNode
 * Määrittää pari käytettävää vakiota
 * Esittelee funktiot
 */
/*******************************************************************/

#include <time.h>
#define taskCharLen 16
#define NumOfTasks 60

#ifndef ali2_h
#define ali2_h

typedef struct readNode {
    struct tm *time;
    char name[taskCharLen];
    int taskID;
    int userID;
    struct readNode *pNext;
} readNode;

typedef struct analNode {
    char name[taskCharLen];
    int returns; 
} analNode;

typedef struct dayAnalNode{
    struct tm *time;
    int returns;
    struct dayAnalNode *pNext;
} dayAnalNode;


readNode * addReadLList(readNode *pStart, struct tm *pTime, char * sTaskName, int iNameLength, int iTaskID, int iUserID);
dayAnalNode * addAnalLList(dayAnalNode * pStart, struct tm *pTime, int returns);
readNode * freeReadLList(readNode *pStart);
dayAnalNode * freeAnalLList(dayAnalNode * pStart);
void analFile(readNode *pStart, analNode * tasks, int analListSize);
dayAnalNode * dayAnalFile(dayAnalNode * pAnalStart, readNode *pReadStart);
struct tm * strp(int years, int months, int days, int hours, int minutes, int seconds);
void findFile(char * target);
int handleSaveChoice();

#endif
