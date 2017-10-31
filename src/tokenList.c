#include <stdio.h>
#include <stdlib.h>

#define INIT_TOK_BUF_SIZE 256
#define INIT_NUM_CHILDREN 2
#define INIT_STRING_TABLE_SIZE 512

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
    int capacity;
    char *buffer;
    char *writePtr;
} StringTable;

typedef struct _TokenTable
{
    int numEntries;
    int capacity;
    tokenNode *buffer;
    tokenNode *writePtr;
} TokenTable;

typedef struct _AstState
{
    StringTable stringTable;
    TokenTable tokenTable;
} AstState;

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

void initToken(char* type, tokenNode* tok, StringTable* strTable)
{
    tok->type = addToStringTable(type, strTable);
    tok->tokens = (tokenNode **)malloc(INIT_NUM_CHILDREN*sizeof(tokenNode*));
    tok->capacity = INIT_NUM_CHILDREN;
    tok->len = 0;
}

tokenNode* appendNode(tokenNode* par, char* child_type, AstState* astState){
    //TODO: make this more memory stable
    tokenNode* child = astState->tokenTable.writePtr++;
    initToken(child_type, child, &astState->stringTable);

    if(par->len+1 > par->capacity){
        tokenNode** tempPtr = (tokenNode **)realloc(par->tokens, 2*par->capacity*sizeof(tokenNode*));
        if(!tempPtr)
        {
            //TODO: Error checking
            printf("ERROR");
            return NULL;
        }
        par->tokens = tempPtr;
        par->capacity = 2*par->capacity;
    }
    *(par->tokens + par->len) = child;
    par->len += 1;
    return child;
}


tokenNode* appendNode(tokenNode* par, tokenNode* child){
    //TODO: make this more memory stable
    if(par->len+1 > par->capacity){
        tokenNode** tempPtr = (tokenNode **)realloc(par->tokens, 2*par->capacity*sizeof(tokenNode*));
        if(!tempPtr)
        {
            //TODO: Error checking
            printf("ERROR");
            return NULL;
        }
        par->tokens = tempPtr;
        par->capacity = 2*par->capacity;
    }
    *(par->tokens + par->len) = child;
    par->len += 1;
    return child;
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

void printTree(AstState* astState){
    printTree(astState->tokenTable.buffer, 0, &astState->stringTable);
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


void initAstState(AstState* astState) {
    astState->stringTable.numEntries = 0;
    astState->stringTable.capacity = INIT_STRING_TABLE_SIZE;
    astState->stringTable.buffer = (char*)malloc(INIT_STRING_TABLE_SIZE*sizeof(char));
    astState->stringTable.writePtr = astState->stringTable.buffer;

    astState->tokenTable.capacity = INIT_TOK_BUF_SIZE;
    astState->tokenTable.numEntries = 0;
    astState->tokenTable.buffer = (tokenNode*)malloc(INIT_TOK_BUF_SIZE*sizeof(tokenNode));
    astState->tokenTable.writePtr = astState->tokenTable.buffer;
}

#if 0 //Test case
int main()
{
    StringTable stringTable;
    stringTable.numEntries = 0;
    stringTable.capacity = INIT_STRING_TABLE_SIZE;
    stringTable.buffer = (char*)malloc(INIT_STRING_TABLE_SIZE*sizeof(char));
    stringTable.writePtr = stringTable.buffer;

    TokenTable tokenTable;
    tokenTable.capacity = INIT_TOK_BUF_SIZE;
    tokenTable.numEntries = 0;
    tokenTable.buffer = (tokenNode*)malloc(INIT_TOK_BUF_SIZE*sizeof(tokenNode));
    tokenTable.writePtr = tokenTable.buffer;

    AstState astState;
    astState.stringTable = stringTable;
    astState.tokenTable = tokenTable;

    tokenNode* parent = astState.tokenTable.writePtr++;
    initToken("Parent", parent, &astState.stringTable);
    tokenNode* tempNode = appendNode(parent, "Child", &astState);
    appendNode(parent, "Child", &astState);
    appendNode(parent, "Child", &astState);
    appendNode(tempNode, "Child2", &astState);
    appendNode(tempNode, "Child2", &astState);
    tempNode = appendNode(tempNode, "Child2", &astState);
    appendNode(tempNode, "Child3", &astState);
    appendNode(tempNode, "Child3", &astState);
    printTree(parent, 0, &stringTable);
}
#endif
