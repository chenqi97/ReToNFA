#include "retonfa.h"

int reToNfa(StateListPtr stateListPtr, char *re, char *alphaTable)
{
    int i = 0;
    int tempCurrentListLen = VEC_LIST_LEN + 1;
    int tempCurrentList[VEC_LIST_LEN];
    if(!re)
    {
        printf("re is null!\n");
        return 0;
    }
    if(strlen(re) == 0)
    {
         printf("Length of re is 0!\n");
         return 0;
    }
    while(re[i]!='\0')
    {
        switch(re[i])
        {
            case 40://"("
                //store before vec list and vec list len
                for(int j = 0; j < stateListPtr->currentListLen; j++)
                {
                    stateListPtr->beforeUnionList[j] = stateListPtr->currentList[j];
                }
                stateListPtr->beforeUnionListLen = stateListPtr->currentListLen;
                break;
            case 41://")"
                stateListPtr->flag = 0;//union end
                break;
            case 42://"*" 
                for(int j = 0; j < stateListPtr->beforeUnionListLen; j++)
                {
                    //insert a new state after every before-union state to the end of stateList
                    VecNodePtr newState = (VecNodePtr)malloc(sizeof(VecNode));
                    newState->flag = 2;
                    newState->firstEdgePtr = stateListPtr->stateList[stateListPtr->beforeUnionList[j]]->firstEdgePtr;
                    stateListPtr->stateList[stateListPtr->stateListLen++] = newState;
                    EdgeNodePtr newEdge = (EdgeNodePtr)malloc(sizeof(EdgeNode));
                    newEdge->transChar = 'e';
                    newEdge->vecNum = stateListPtr->stateListLen - 1;
                    newEdge->nextEdgePtr = NULL;
                    stateListPtr->stateList[stateListPtr->beforeUnionList[j]]->firstEdgePtr = newEdge;

                    for(int k = 0; k < stateListPtr->currentListLen; k++){
                        EdgeNodePtr newEdgePtr = (EdgeNodePtr)malloc(sizeof(EdgeNode));
                        newEdgePtr->transChar = 'e';
                        newEdgePtr->vecNum = stateListPtr->stateListLen - 1;
                        newEdgePtr->nextEdgePtr = stateListPtr->stateList[stateListPtr->currentList[k]]->firstEdgePtr;
                        stateListPtr->stateList[stateListPtr->currentList[k]]->firstEdgePtr = newEdgePtr;
                    }
                    stateListPtr->currentList[stateListPtr->currentListLen++] = stateListPtr->beforeUnionList[j];
                }
                
                break;
            case 43://"+"
                for(int j = 0; j < stateListPtr->beforeUnionListLen; j++)
                {
                    VecNodePtr newState = (VecNodePtr)malloc(sizeof(VecNode));
                    newState->flag = 2;
                    newState->firstEdgePtr = stateListPtr->stateList[stateListPtr->beforeUnionList[j]]->firstEdgePtr;
                    stateListPtr->stateList[stateListPtr->stateListLen++] = newState;
                    EdgeNodePtr newEdge = (EdgeNodePtr)malloc(sizeof(EdgeNode));
                    newEdge->transChar = 'e';
                    newEdge->vecNum = stateListPtr->stateListLen - 1;
                    newEdge->nextEdgePtr = NULL;
                    stateListPtr->stateList[stateListPtr->beforeUnionList[j]]->firstEdgePtr = newEdge;

                    for(int k = 0; k < stateListPtr->currentListLen; k++){
                        EdgeNodePtr newEdgePtr = (EdgeNodePtr)malloc(sizeof(EdgeNode));
                        newEdgePtr->transChar = 'e';
                        newEdgePtr->vecNum = stateListPtr->beforeUnionList[j];
                        newEdgePtr->nextEdgePtr = stateListPtr->stateList[stateListPtr->currentList[k]]->firstEdgePtr;
                        stateListPtr->stateList[stateListPtr->currentList[k]]->firstEdgePtr = newEdgePtr;
                    }
                    stateListPtr->currentList[stateListPtr->currentListLen++] = stateListPtr->stateListLen - 1;
                }
                break;
            case 85://"U"
            {
                //EdgeNodePtr tempEdgePtr;
                EdgeNodePtr newEdgePtr;
                char tempRe[RE_MAX_LEN];
                int tempCount = 0;
                int preStateLen = stateListPtr->stateListLen;
                char preChar;
                i += 1;
                preChar = re[i];
                while(re[i] != ')')
                    tempRe[tempCount++] = re[i++];
                tempRe[tempCount++] = ')';
                tempRe[tempCount] = '\0';
                tempCount = 0;

                stateListPtr->flag = 1;//in union
                //stateListPtr->currentListLen = 0;
                reToNfa(stateListPtr, tempRe, alphaTable);

                for(int j = 0; j < stateListPtr->beforeUnionListLen; j++)
                {
                    //tempEdgePtr = stateListPtr->stateList[stateListPtr->beforeUnionList[j]]->firstEdgePtr;
                    //create new edge node
                    newEdgePtr = (EdgeNodePtr)malloc(sizeof(EdgeNode));
                    newEdgePtr->transChar = preChar;
                    newEdgePtr->vecNum = preStateLen;
                    //insert from header
                    newEdgePtr->nextEdgePtr = stateListPtr->stateList[stateListPtr->beforeUnionList[j]]->firstEdgePtr;
                    stateListPtr->stateList[stateListPtr->beforeUnionList[j]]->firstEdgePtr = newEdgePtr;
                }                
                break;
            }
            default://input is alpha
            {
                if(!isInAlphaTable(re[i],alphaTable))
                {
                    printf("The Alpha is not in Alpha Table!\n");
                    return 0;
                }
                //before store the current state
                if(stateListPtr->flag)
                {
                    //the first time in union
                    if(i - 1 < 0)
                    {
                        tempCurrentListLen = stateListPtr->currentListLen;
                        for(int j = 0; j < stateListPtr->currentListLen; j++)
                        //{
                            tempCurrentList[j] = stateListPtr->currentList[j];
                        //     printf("tempCurrentListLen:%d\n",tempCurrentList[j]);
                        // }
                        stateListPtr->currentListLen = 0;
                    }
                }

                EdgeNodePtr tempEdgePtr;
                EdgeNodePtr newEdgePtr;
                VecNodePtr newState = (VecNodePtr)malloc(sizeof(VecNode));

                newState->flag = 2;
                newState->firstEdgePtr = NULL;
                stateListPtr->stateList[stateListPtr->stateListLen++] = newState;
                for(int j = 0; j < stateListPtr->currentListLen; j++)
                {
                    //tempEdgePtr = stateListPtr->stateList[stateListPtr->currentList[j]]->firstEdgePtr;
                    //printf("%d %d\n",stateListPtr->stateList[stateListPtr->currentList[j]]->flag,stateListPtr->currentListLen);
                    newEdgePtr = (EdgeNodePtr)malloc(sizeof(EdgeNode));
                    newEdgePtr->transChar = re[i];
                    newEdgePtr->vecNum = stateListPtr->stateListLen - 1;
                    //insert from header
                    newEdgePtr->nextEdgePtr = stateListPtr->stateList[stateListPtr->currentList[j]]->firstEdgePtr;
                    stateListPtr->stateList[stateListPtr->currentList[j]]->firstEdgePtr = newEdgePtr;
                }
                //judge if in union
                if(!stateListPtr->flag)
                {
                    stateListPtr->currentListLen = 1;
                    stateListPtr->currentList[0] = stateListPtr->stateListLen - 1;
                }
                else 
                {         
                    if(re[i+1] == ')' || re[i+1] == 'U')
                    {
                        for(int j = 0; j < tempCurrentListLen; j++)
                            stateListPtr->currentList[j] = tempCurrentList[j];
                        stateListPtr->currentList[tempCurrentListLen] = stateListPtr->stateListLen - 1;
                        stateListPtr->currentListLen = tempCurrentListLen + 1;
                        //printf("tempCurrentListLen:%d\n",tempCurrentListLen);
                    }else
                        stateListPtr->currentList[stateListPtr->currentListLen++] = stateListPtr->stateListLen - 1;
                }
                break; 
            } 
        }
        i++;
    }
    //change the currentVec flag to 1
    for(int j = 0; j < stateListPtr->currentListLen; j++)
        stateListPtr->stateList[stateListPtr->currentList[j]]->flag = 1;
    return 1;
}

int isInAlphaTable(char testChar, char *alphaTable)
{
    int i = 0;
    while(alphaTable[i] != '\0')
    {
        if(testChar == alphaTable[i])
            return 1;
        else
            i++;
    }
    return 0;
}