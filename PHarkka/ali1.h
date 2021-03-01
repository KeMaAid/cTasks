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

#ifndef ali1_h
#define ali1_h
#define taskCharLen 16

typedef struct readNode {
    struct tm time;
    char name[taskCharLen];
    int id;
    int userID;
} readNode;

typedef struct analNode {
    char name[taskCharLen];
    int returns; 
} analNode;

readNode* readFile();
analNode* analFile(readNode *);
int printFile(analNode *, int);

#endif