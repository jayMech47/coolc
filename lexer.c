#include "lexer.h"

typedef struct Pattern{
    int acceptState;
    int currState;
    char fsm[NUM_STATES][128];
} Pattern;

Pattern patternList[NUM_PATTERNS];

Pattern createKwdPattern(char *kwd, Pattern keywordPattern){
    int idx = 0;
    while(*kwd){
        for(int i = 0; i < 128; ++i){
            if(i == *kwd){
                keywordPattern.fsm[idx][i] = idx+1;
            }else{
                keywordPattern.fsm[idx][i] = -1;
            }
        }
        kwd++;
        idx++;
    }

    keywordPattern.currState = 0;
    keywordPattern.acceptState = idx;
    for(int i = 0; i< 128; ++i){
        keywordPattern.fsm[idx][i] = -1;
    }
    return keywordPattern;
}

void createPatterns(){

    // line comment patterns
	//TODO: consolidate loops
    for(int i = 0; i<128; ++i){
        if(i == '-'){
            patternList[LINE_COMMENT].fsm[0][i] = 1;
        }else{
            patternList[LINE_COMMENT].fsm[0][i] = -1;
        }
    }

    for(int i = 0; i<128; ++i){
        if(i == '-'){
            patternList[LINE_COMMENT].fsm[1][i] = 2;
        }else{
            patternList[LINE_COMMENT].fsm[1][i] = -1;
        }
    }

    for(int i = 0; i<128; ++i){
        if(i == '\n'){
            patternList[LINE_COMMENT].fsm[2][i] = -1;
        }else{
            patternList[LINE_COMMENT].fsm[2][i] = 2;
        }
    }
    patternList[LINE_COMMENT].currState = 0;
    patternList[LINE_COMMENT].acceptState = 2;

    // Whitespace pattern
    patternList[WHITE_SPACE].currState = 0;
    for(int i=0; i<128; ++i){
        if(i=='\n' || i==' ' 
            || i=='\t' || i=='\r'){
            patternList[WHITE_SPACE].fsm[0][i] = 1;
            patternList[WHITE_SPACE].fsm[1][i] = 1;
        }else{
            patternList[WHITE_SPACE].fsm[0][i] = -1;
            patternList[WHITE_SPACE].fsm[1][i] = -1;
        }
    }
    patternList[WHITE_SPACE].acceptState = 1;

    patternList[COOL_ID].currState = 0;
    for(int i=0; i<128; ++i){
        if((i>='a' && i<='z') || i=='_'){
            patternList[COOL_ID].fsm[0][i] = 1;
            patternList[COOL_ID].fsm[1][i] = 1;
        }else if((i>='A' && i<='Z') || (i>='0' && i<='9')){
            patternList[COOL_ID].fsm[0][i] = -1;
            patternList[COOL_ID].fsm[1][i] = 1;
        }else{
            patternList[COOL_ID].fsm[0][i] = -1;
            patternList[COOL_ID].fsm[1][i] = -1;
        }
    }
    patternList[COOL_ID].acceptState = 1;

    patternList[COOL_TYPE].currState = 0;
    for(int i=0; i<128; ++i){
        if((i>='A' && i<='Z') || i=='_'){
            patternList[COOL_TYPE].fsm[0][i] = 1;
            patternList[COOL_TYPE].fsm[1][i] = 1;
        }else if((i>='a' && i<='z') || (i>='0' && i<='9')){
            patternList[COOL_TYPE].fsm[0][i] = -1;
            patternList[COOL_TYPE].fsm[1][i] = 1;
        }else{
            patternList[COOL_TYPE].fsm[0][i] = -1;
            patternList[COOL_TYPE].fsm[1][i] = -1;
        }
    }
    patternList[COOL_TYPE].acceptState = 1;

    //String Pattern
    patternList[STRING].currState = 0;
    for(int i=0; i<128; ++i){
        if(i == '"'){
            patternList[STRING].fsm[0][i] = 1;
            patternList[STRING].fsm[1][i] = 3; //Accepted string
            patternList[STRING].fsm[2][i] = 1;
            patternList[STRING].fsm[3][i] = -1;
        }else if(i=='\\'){
            patternList[STRING].fsm[0][i] = -1;
            patternList[STRING].fsm[1][i] = 2;
            patternList[STRING].fsm[2][i] = 1;
            patternList[STRING].fsm[3][i] = -1;
        }else{
            patternList[STRING].fsm[0][i] = -1;
            patternList[STRING].fsm[1][i] = 1;
            patternList[STRING].fsm[2][i] = 1;
            patternList[STRING].fsm[3][i] = -1;
        }
    }
    patternList[STRING].acceptState = 3;

    // integer literal Pattern
    patternList[INT_LITERAL].currState = 0;
    for(int i=0; i<128; ++i){
        if(i>='0' && i<='9' ){
            patternList[INT_LITERAL].fsm[0][i] = 1;
            patternList[INT_LITERAL].fsm[1][i] = 1;
        }else{
            patternList[INT_LITERAL].fsm[0][i] = -1;
            patternList[INT_LITERAL].fsm[1][i] = -1;
        }
    }
    patternList[INT_LITERAL].acceptState = 1;

    // KeywordPatterns
    patternList[CLASS] = createKwdPattern("class", patternList[CLASS]);
    patternList[INHERITS] = createKwdPattern("inherits", patternList[INHERITS]);
    patternList[LET] = createKwdPattern("let", patternList[LET]);
    patternList[IN] = createKwdPattern("in", patternList[IN]);
    patternList[ISVOID] = createKwdPattern("isvoid", patternList[ISVOID]);
    patternList[NOT] = createKwdPattern("not", patternList[NOT]);
    patternList[WHILE] = createKwdPattern("while", patternList[WHILE]);
    patternList[LOOP] = createKwdPattern("loop", patternList[LOOP]);
    patternList[POOL] = createKwdPattern("pool", patternList[POOL]);
    patternList[IF] = createKwdPattern("if", patternList[IF]);
    patternList[THEN] = createKwdPattern("then", patternList[THEN]);
    patternList[ELSE] = createKwdPattern("else", patternList[ELSE]);
    patternList[FI] = createKwdPattern("fi", patternList[FI]);
    patternList[OPEN_PAREN] = createKwdPattern("(", patternList[OPEN_PAREN]);
    patternList[CLOSE_PAREN] = createKwdPattern(")", patternList[CLOSE_PAREN]);
    patternList[OPEN_CURL] = createKwdPattern("{", patternList[OPEN_CURL]);
    patternList[CLOSE_CURL] = createKwdPattern("}", patternList[CLOSE_CURL]);
    patternList[OPEN_STREAM] = createKwdPattern("(*", patternList[OPEN_STREAM]);
    patternList[COLON] = createKwdPattern(":", patternList[COLON]);
    patternList[SEMI_COLON] = createKwdPattern(";", patternList[SEMI_COLON]);
    patternList[COMMA] = createKwdPattern(",", patternList[COMMA]);
    patternList[ASSIGN] = createKwdPattern("<-", patternList[ASSIGN]);
    patternList[DOT] = createKwdPattern(".", patternList[DOT]);
    patternList[EQUALS] = createKwdPattern("=", patternList[EQUALS]);
    patternList[PLUS] = createKwdPattern("+", patternList[PLUS]);
    patternList[MINUS] = createKwdPattern("-", patternList[MINUS]);
    patternList[MULT] = createKwdPattern("*", patternList[MULT]);
    patternList[DIVIDE] = createKwdPattern("/", patternList[DIVIDE]);
}
