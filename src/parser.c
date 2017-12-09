#include <stdio.h>
#include "utils_coolc.c"
#include "lexer.h"
#include "parser.h"
#include "tokenList.c"

Token tokenArray[1024];
int numTokens = 0;
AstState astState;

int tokenCursor = 0;

char _stringTable[1024];
char *stringTable = &_stringTable[0];

AstState initAst(){
    astState.stringTable.numEntries = 0;
    astState.stringTable.capacity = INIT_STRING_TABLE_SIZE;
    astState.stringTable.buffer = (char*)malloc(INIT_STRING_TABLE_SIZE*sizeof(char));
    astState.stringTable.writePtr = astState.stringTable.buffer;

    astState.tokenTable.capacity = INIT_TOK_BUF_SIZE;
    astState.tokenTable.numEntries = 0;
    astState.tokenTable.buffer = (tokenNode*)malloc(INIT_TOK_BUF_SIZE*sizeof(tokenNode));
    astState.tokenTable.writePtr = astState.tokenTable.buffer;
    return astState;
}

// TODO: add match_token function
// takes a Token enum and returns success, prints error "expect TOK"
// needs TOK name string table
int matchLeaf(int token_type){
    if(tokenArray[tokenCursor++].id == token_type){
        return 1;
    }else{
        return 0;
    }
}

//cool class production
//cl_class_prd := class TYPE V { feature_list }
//V := inherits TYPE || e
int V(){
    int tempTokCursor = tokenCursor;
    if(tokenArray[tokenCursor++].id == INHERITS
            && tokenArray[tokenCursor++].id == COOL_TYPE){
        return 1;
    }
    tokenCursor = tempTokCursor;
    return 1;
}

//TODO:@jchristensen remove temp productions
int tempIntPrd(){
    if(matchLeaf(33)){
        return 1;
    }
    return 0;
}

int expression_prd(){
    return tempIntPrd();
}

int attribute_prd(){
    return 0;
}

int formal_prd(){
    return 1;
}

int method_prd(){
    int tempTokCursor = tokenCursor;
    if(        matchLeaf(COOL_ID)
            && matchLeaf(OPEN_PAREN)
            && formal_prd()
            && matchLeaf(CLOSE_PAREN)
            && matchLeaf(COLON)
            && matchLeaf(COOL_TYPE)
            && matchLeaf(OPEN_CURL)
            && expression_prd()
            && matchLeaf(CLOSE_CURL)
            && matchLeaf(SEMI_COLON)
            )
    {
        return 1;
    }
    tokenCursor = tempTokCursor;
    return 0;
}

int feature_list(){
    int tempTokCursor = tokenCursor;
    if(attribute_prd()){
        return 1;
    }

    tokenCursor = tempTokCursor;
    if (method_prd()){
        return 1;
    }
    tokenCursor = tempTokCursor;
    return 1;
}

int cl_class_prd(tokenNode* parent, AstState* astState){
    int tempTokCursor = tokenCursor;
    char* name;
    
    if(tokenArray[tokenCursor++].id == CLASS){
            if(tokenArray[tokenCursor].id == COOL_TYPE)
                name = tokenArray[tokenCursor++].data.name;

            if(V()
                && tokenArray[tokenCursor++].id == OPEN_CURL
                && feature_list()
                && tokenArray[tokenCursor++].id == CLOSE_CURL
                && tokenArray[tokenCursor++].id == SEMI_COLON
            ){

                appendNode(parent, name, astState);

                return 1;
            }
    }
    tokenCursor = tempTokCursor;
    return 0;
}

// Program := T$
// T := cl_class_prd T | e
int T(tokenNode* parent, AstState* astState){
    // TODO: do I add the token to the Tree before or after it matches, it might only match if children match, so adding it first might be necessary. Removing later is an option.
    if(cl_class_prd(parent, astState)){
        T(parent, astState);
    }
    return 1;
}

int matchProg(AstState* astState){
    
    tokenNode* prgNode = astState->tokenTable.writePtr++;
//TODO: write init that doesn;t require a Node and takes an AstState
    initToken("Program", prgNode, &astState->stringTable);

    if(T(prgNode, astState) && tokenArray[tokenCursor].id == CL_EOF){
        return 1;
    }else{
        return 0;
    }
}

int main(int argc, char*argv[]){
    char line[255];
    char* line2 = &line[0];
    size_t n_chars = 255;
    Token tempToken;
    int tokIdx = 0;
    int tokId;

    // Is this loop neccessary? can we have this as a "stream"?
    char* writePtr = stringTable;
    while(tokId != CL_EOF){
        getline(&line2, &n_chars, stdin);
        char* val;
        tokId = str2int(line, 2);
        if(tokId == COOL_ID
                || tokId == COOL_TYPE){
            tempToken.data.name= writePtr;
            writePtr = strcpy(line+2, writePtr); //TODO: remove magic number (token format?) add strings to hash table for duplicates, in the mean time add a "add to string table" function that checks for duplicates the long way.
        }
        tempToken.id = tokId;
        tokenArray[tokIdx++] = tempToken;
    }
    AstState _astState;
    AstState* astState = &_astState;
    initAstState(astState);
    numTokens = tokIdx;
    int retVal = matchProg(astState);
    printHeader("Parse Tree");
    printTree(astState);
    printFooter();

    if(retVal){
        printf("Program matched\n");
    }

    return 1;
}

