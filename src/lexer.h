#ifndef LEXER_H
#define LEXER_H

#define NUM_STATES 10 //Yikes, tables are getting big, move to array of pointers?
#define NUM_PATTERNS 34

//TODO: Add operators
//TODO: Make into enum
#define LINE_COMMENT 0
#define WHITE_SPACE 1
#define COOL_TYPE 2
#define COOL_ID 3
#define CLASS 4
#define INHERITS 5
#define LET 6
#define IN 7
#define ISVOID 8
#define NOT 9
#define WHILE 10
#define LOOP 11
#define POOL 12
#define IF 13
#define THEN 14
#define ELSE 15
#define FI 16
#define OPEN_PAREN 17
#define CLOSE_PAREN 18
#define OPEN_CURL 19
#define CLOSE_CURL 20
#define OPEN_STREAM 21
#define COLON 22
#define SEMI_COLON 23
#define COMMA 24
#define ASSIGN 25
#define DOT 26
#define STRING 27
#define EQUALS 28
#define PLUS 29
#define MINUS 30
#define MULT 31
#define DIVIDE 32
#define INT_LITERAL 33
#define CL_EOF 34

int matchLine(char * line, int lineNumber);

#endif //LEXER_H
