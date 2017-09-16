#include <stdio.h>
#include "lexer.h"
#include "parser.h"

Token tokenArray[1024];
int numTokens = 0;

int tokenCursor = 0;

char _stringTable[1024];
char *stringTable = &_stringTable[0];

char* strcpy(char* src, char* dest){
    char* save_dest = dest;
    while(*src){
        *dest++ = *src++;
    }
    *dest++ = *src++;
    return save_dest;
}
// TODO: add match_token function
// takes a Token enum and returns success, prints error "expect TOK"
// needs TOK name string table

//cool class production
//cl_class_prd := class TYPE V { U }
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

int expression_prd(){
    return 1;
}

int U(){
    if (expression_prd()){
        return 1;
    }
    return 1;
}
int cl_class_prd(){
    int tempTokCursor = tokenCursor;
    if(tokenArray[tokenCursor++].id == CLASS
            && tokenArray[tokenCursor++].id == COOL_TYPE
            && V()
            && tokenArray[tokenCursor++].id == OPEN_CURL
            && U()
            && tokenArray[tokenCursor++].id == CLOSE_CURL
            && tokenArray[tokenCursor++].id == SEMI_COLON
            ){
        printf("class ");
        return 1;
    }
    tokenCursor = tempTokCursor;
    return 0;
}

// Program := T$
// T := cl_class_prd T | e
int T(){
    if(cl_class_prd()){
        T();
    }
    return 1;
}

int matchProg(){
    if(T() && tokenArray[tokenCursor].id == CL_EOF){
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

    while(tokId != CL_EOF){
        getline(&line2, &n_chars, stdin);
        char* val;
        tokId = str2int(line, 2);
        if(tokId == COOL_ID
                || tokId == COOL_TYPE){
            tempToken.data.name= stringTable;
            stringTable = strcpy(line+2, stringTable);
        }
        tempToken.id = tokId;
        tokenArray[tokIdx++] = tempToken;
    }
    numTokens = tokIdx;
    int retVal = matchProg();
    printf("%d\n", retVal);
    return 1;
}

