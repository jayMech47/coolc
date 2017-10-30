int strLen(char* str){
    int letterCount = 0;
    while(*str != 0){
        letterCount++;
        str++;
    }
    return letterCount;
}

void writeChar(char str){
    putc(str, stdout);
}

void printHeader(char* title, int columnCount){
    if(strLen(title)-2 > columnCount){
        for(int i = 0;
                i< columnCount;
                i++)
        {
            writeChar(*title++);
        }
    }else{
        int titleCount = strLen(title);
        int prefixCount = (columnCount - 2 - titleCount)/2;
        int suffixCount = columnCount - 2 - prefixCount -titleCount;
        for(int i = 0;
                i< prefixCount;
                i++)
        {
            writeChar('*');
        }
        writeChar(' ');
        for(int i = 0;
                i< titleCount;
                i++)
        {
            writeChar(*title++);
        }
        writeChar(' ');
        for(int i = 0;
                i< suffixCount;
                i++)
        {
            writeChar('*');
        }
    }
    writeChar('\n');
}

void printHeader(char* title){
    printHeader(title, 80);
}

void printFooter(int columnWidth){
    for(int i = 0;
            i< columnWidth;
            i++)
    {
        writeChar('*');
    }
    writeChar('\n');
}

void printFooter(){
    printFooter(80);
}


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

