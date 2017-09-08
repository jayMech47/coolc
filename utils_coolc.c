char reprBuff[1024];
char * repr(char * str){
    char *buff = &reprBuff[0];
    *buff++ = '"';
    while(*str){
        if(*str =='\n'){
            *buff++ = '\\';
            *buff++ = 'n';
            str++;
        }else if(*str =='\t'){
            *buff++ = '\\';
            *buff++ = 't';
            str++;
        }else if(*str =='\r'){
            *buff++ = '\\';
            *buff++ = 'r';
            str++;
        }else{
            *buff++ = *str++;
        }
    }
    *buff++ = '"';
    *buff = '\0';
    return reprBuff;
}

