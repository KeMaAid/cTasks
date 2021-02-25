/*******************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
 * Otsikkotiedot:
 * Tekijä: Konsta Keski-Mattinen
 * Opiskelijanumero: 0568752
 * Päivämäärä: 2021.02.24
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void printLList(Node *pStart){
    if(pStart == NULL){
        //printf("Lista on tyhjä.\n");
        printf("\n");
        return;
    }
    //printf("Listassa on seuraavat luvut: \n");
    for(Node *ptr = pStart;ptr != NULL; ptr=ptr->pNext){
        printf("%d ", ptr->value);
    }
    printf("\n");
}

Node * addLList(Node *pStart, int index, int *nextCallNumber){
    Node *pNew, *ptr;
    if((pNew = (Node*)malloc(sizeof(Node)))== NULL){
        printf("Muistin varaus epäonnistui.\n");
        exit(0);
    }

    pNew->value=*nextCallNumber;
    pNew->pNext=NULL;

    if(pStart == NULL || index ==0){
        pNew->pNext=pStart;
        pStart= pNew;
        //printf("DEBUG: Adding first element %p, value %d and pNext %p\n", pNew, pNew->value, pNew->pNext);
    } else {
        int i = 1;
        for(ptr = pStart;;ptr=ptr->pNext){
            //printf("DEBUG: Now looking at index %d at %p\n", i, ptr);
            if(i==index){
                //printf("DEBUG: Inserting to index %d which was %p. Now is %p with value %d and pNext %p\n", index, ptr->pNext, pNew, pNew->value, pNew->pNext);
                pNew->pNext = ptr->pNext;
                ptr->pNext=pNew;
                break;
            }
            if(ptr->pNext == NULL){
                //printf("DEBUG: Adding to end of list with index %d pointer %p with pNext %p. Previous was %p,%d\n", i+1, pNew, pNew->pNext, ptr, ptr->value);
                ptr->pNext=pNew;
                break;
            }
            i++;
        }
    }
    (*nextCallNumber)++;
    return pStart;
}

Node * freeLList(Node *pStart){
    Node *ptr = pStart;
    while(ptr != NULL){
        pStart = ptr->pNext;
        free(ptr);
        ptr = pStart;
    }
    return pStart;
}

Node * createLList(int *nextCallNumber){
    int newSize;
    printf("Anna listan pituus: ");
    scanf("%d", &newSize);

    if(newSize<0){
        printf("Listan pituus ei voi olla negatiivinen.\n");
        return NULL;
    };

    Node *ptr = NULL;
    for(int i = 0;i<newSize;i++){  
        ptr = addLList(ptr,i, nextCallNumber);
    }
    
    return ptr;
}

Node * removeLList(Node *pStart, int index){
    if(index < 0 ){
        return pStart;
    }
    Node *ptr;
    int i = 0;
    for(ptr = pStart;ptr != NULL;ptr=ptr->pNext){
        i++;
        if(i==index){
            Node * tmp = ptr->pNext->pNext;
            free(ptr->pNext);
            ptr->pNext=tmp;
        }
    }
    return pStart;
}