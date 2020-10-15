#include "retonfa.h"

int main(){
    StateListPtr stateListPtr = (StateListPtr)malloc(sizeof(StateListNode));
    VecNodePtr startNodePtr = (VecNodePtr)malloc(sizeof(VecNode));
    EdgeNodePtr tempEdgePtr;
    char re[RE_MAX_LEN];
    char alphaTable[RE_MAX_LEN];

    //initiate stateListPtr
    for(int j = 0; j < VEC_MAX_LEN; j++)
        stateListPtr->stateList[j] = NULL;
    stateListPtr->stateListLen = 1;
    stateListPtr->currentList[0] = 0;
    stateListPtr->currentListLen = 1;
    stateListPtr->flag = 0;
    //initiate startNodePtr
    startNodePtr->flag = 0;
    startNodePtr->firstEdgePtr = NULL;
    stateListPtr->stateList[0] = startNodePtr;

    printf("Please Enter a Regular Expression(eg:(abcUac)*ab):");
    scanf("%s",re);
    printf("Please Enter the Alpha Table(eg:abc):");
    scanf("%s",alphaTable);
    reToNfa(stateListPtr, re, alphaTable);
    printf("--------------------------------------\n");
    printf("The Alpha Table of NFA is : ");
    for(int i = 0; i < strlen(alphaTable); i++)
        printf("%c ",alphaTable[i]);
    printf("\n");
    printf("The State Set of NFA is : ");
    for(int i = 0; i < stateListPtr->stateListLen; i++)
    {
        printf("%d ",i);
    }
    printf("\n");
    printf("The Transfer Fuction is : \n");
    printf("State   Input   Output\n");
    for(int i = 0; i < stateListPtr->stateListLen; i++)
    {
        tempEdgePtr = stateListPtr->stateList[i]->firstEdgePtr;
        while(tempEdgePtr != NULL)
        {
            printf("  %d   ",i);
            printf("    %c   ",tempEdgePtr->transChar);
            printf("    %d\n",tempEdgePtr->vecNum);
            tempEdgePtr = tempEdgePtr->nextEdgePtr;
        }
    }

    printf("The Start State of NFA is : %d\n", 0);
    printf("The Accept State of NFA is : ");
    for(int i = 0; i < stateListPtr->currentListLen; i++)
        printf("%d ", stateListPtr->currentList[i]);

    free(stateListPtr);
    free(startNodePtr);
    return 0;
}