#include <stdio.h>

int str2int (char* str, int n){
    int ret = 0;
    for(int i = 0; i<n; ++i){
        ret *= 10;
        ret += *str++-0x30;
    }
    return ret;
}

void main(int argc, char*argv[]){
    char line[255];
    char* line2 = &line[0];
    size_t n_chars = 255;

    while(1){
        getline(&line2, &n_chars, stdin);
        printf("%d\n", str2int(line, 2));
        if(line[3] == '$'){
            break;
        }
    }
}
