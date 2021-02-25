/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 2021.02.25
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/

#ifndef lista_h
#define lista_h

typedef struct Node {
    int value;
    struct Node *pNext;
} Node;

void printLList(Node *pStart);
Node * addLList(Node *pStart, int index, int *nextCallNumber);
Node * freeLList(Node *pStart);
Node * createLList(int *nextCallNumber);
Node * removeLList(Node *pStart, int index);

#endif