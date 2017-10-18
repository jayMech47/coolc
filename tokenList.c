#include <stdio.h>
#include <stdlib.h>

#define TOK_BUF_LEN 256

typedef struct _tokenNode
{ 
    int type;
    struct _tokenNode** tokens;
    int len;
    int capacity;
} tokenNode;

typedef struct _StringTable
{
    int numEntries;
    char *buffer;
    char *writePtr;
} StringTable;

int addToStringTable(char* str, StringTable* strTable)
{
    char* tempPtr = strTable->writePtr;
    while(*str)
    {
        *strTable->writePtr++ = *str++;
    }
    *strTable->writePtr++ = 0;
    strTable->numEntries += 1;
    return tempPtr - strTable->buffer;
}

void initToken(char* str, tokenNode* tok, StringTable* strTable)
{
    tok->type = addToStringTable(str, strTable);
    tok->tokens = (tokenNode **)malloc(4*sizeof(tokenNode*));
    tok->capacity = 4;
    tok->len = 0;
}

void appendNode(tokenNode* par, tokenNode* child){
    //TODO: make this more memory stable
    if(par->len+1 > par->capacity){
        tokenNode** tempPtr = (tokenNode **)realloc(par->tokens, 2*par->capacity*sizeof(tokenNode*));
        if(!tempPtr)
        {
            //TODO: Error checking
            printf("ERROR");
            return;
        }
        par->tokens = tempPtr;
        par->capacity = 2*par->capacity;
    }
    *(par->tokens + par->len) = child;
    par->len += 1;
}

void printTree(tokenNode* tok, int depth, StringTable *strTable)
{
    for(int i=0; i<depth; i++)
    {
        printf(" ");
    }
    printf("%s\n", strTable->buffer + tok->type);

    tokenNode** nodePtr = tok->tokens;

    for(int i =0; i<tok->len; i++)
    {
        printTree(*nodePtr++, depth+1, strTable);
    }
}

void resizeStringTable(StringTable* strTable)
{
    char* newBuffer = (char*)malloc(2048);
    char* newWritePtr = newBuffer;
    
    char* tempPtr =strTable->buffer;
    while(tempPtr != strTable->writePtr)
    {
        *newWritePtr++ = *tempPtr++;
    }
    strTable->buffer = newBuffer;
    strTable->writePtr = newWritePtr;
}

#if 1
int main()
{
    tokenNode* tokenBuf = (tokenNode*)malloc(TOK_BUF_LEN*sizeof(tokenNode));
    tokenNode program;

}
#endif
