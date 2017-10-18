#ifndef PARSER_H
#define PARSER_H

int str2int (char* str, int n){
    int ret = 0;
    for(int i = 0; i<n; ++i){
        ret *= 10;
        ret += *str++-0x30;
    }
    return ret;
}

struct Token{
    int id;
    union {
        char* name;
    } data;
};

#endif //PARSER_H
