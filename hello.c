#include <stdio.h>
#include "lang_spec.h"
#include "lexer.h"
#include "lexer.c"
#include "utils_coolc.c"


int main(int argc, char * argv[]){
    if(argc != 2){
        printf("Need file to compile");
        return 1;
    }
    FILE *fp;
    char buff[255];
    fp = fopen(argv[1], "r");

    createPatterns();
    int i;
    while(fgets(buff, 255, fp)){
        if(matchLine(buff, i)){
            printf("ERROR Occured: Halting execution\n");
            return 1;
        }
    }
    matchLine("$", i);
}

int matchLine(char * line, int lineNumber){

    int col = 0;
    static char currToken[255];

    static int activePattern;
    static int acceptedPattern = -1;
    static int tokenIdx = 0;
    static int nextState = -1;

    static int commentMode = 0;
    static int lastWasSplat = 0;
    static int lastWasOpenParen = 0;
    static int openCount = 0;

    while(*line){
        activePattern = -1;
        if(commentMode){
            if(lastWasSplat && *line==')'){
                openCount--;
            }
            if(lastWasOpenParen && *line=='*'){
                openCount++;
            }
            if(*line == '*'){
                lastWasSplat = 1;
            }else{
                lastWasSplat = 0;
            }
            if(*line == '('){
                lastWasOpenParen = 1;
            }else{
                lastWasOpenParen = 0;
            }
            col++;
            currToken[tokenIdx++] = *line++;
            currToken[tokenIdx] = '\0';

            if(openCount == 0){
                //TODO: replace commentMode with openCount
                for(int i =0; i< NUM_PATTERNS; ++i){
                	patternList[i].currState = 0;
                }
                printf("%02d:%s\n", acceptedPattern, repr(currToken));
                commentMode = 0;
                tokenIdx = 0;
                acceptedPattern = -1;
            }
        }else{
            for(int i = 0; i<NUM_PATTERNS; ++i){
                if(patternList[i].currState != -1){
                    nextState = patternList[i].fsm[patternList[i].currState][*line];
                    if(nextState != -1){
                        activePattern = i;
                    }else{
                        if(patternList[i].currState == patternList[i].acceptState){
                            if(i == OPEN_STREAM){
                                commentMode = 1;
                                openCount = 1;
                                activePattern = OPEN_STREAM;
                                acceptedPattern = OPEN_STREAM;
                            }else{
                                acceptedPattern = i;
                            }
                        }
                    }
                    patternList[i].currState = nextState;
                }
            }
            if(activePattern != -1){
                col++;
                currToken[tokenIdx++] = *line++;
                currToken[tokenIdx] = '\0';
            }else{
                if(acceptedPattern != -1){
                    for(int i = 0; i<NUM_PATTERNS; ++i){
                        patternList[i].currState = 0;
                    }
                    if(acceptedPattern != WHITE_SPACE){
                        printf("%02d:%s\n", acceptedPattern, repr(currToken));
                    }
                    tokenIdx = 0;
                    acceptedPattern = -1;
                }else{
                    if(*line == '$'){
                        printf("34:$\n");
                    }else{
                        printf("ERROR: Couldn't find valid pattern\n");
                        printf("  currToken: %s\n", repr(currToken));
                        printf("  currChar : '%c' at line: %d col: %d\n", *line, lineNumber+1, col+1);
                    }
                    return 1;
                }
            }
        }
    }

    return 0;
}
