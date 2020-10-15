#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VEC_LIST_LEN 10
#define VEC_MAX_LEN 50
#define RE_MAX_LEN 50

typedef struct Edge{
    char transChar;//transition char
    int vecNum;//vec number
    struct Edge *nextEdgePtr;
}EdgeNode, *EdgeNodePtr;

typedef struct Vec{
    int flag;//0 is start state; 1 is exccept state; 2 is simple state
    struct Edge *firstEdgePtr;
}VecNode, *VecNodePtr;

typedef struct State{
    struct Vec *stateList[VEC_MAX_LEN];
    int stateListLen;//point next empty position
    int currentList[VEC_LIST_LEN];
    int currentListLen;
    int beforeUnionList[VEC_LIST_LEN];
    int beforeUnionListLen;
    int flag;//1 is in union 
}StateListNode, *StateListPtr;

int reToNfa(StateListPtr stateListPtr,char *re, char *alphaTable);
int isInAlphaTable(char testChar, char *alphaTable);