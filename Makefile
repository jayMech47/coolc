
ASSN = 1
BUILDIR = bin/
CLASS= cs143
CLASSDIR= ../..
LEXSRC= lexer.c
PARSRC= parser.c
TOKLISTSRC= tokenList.c
SOURCEFOLDER=src/
WARN = -Wno-write-strings
		
SRC= stack.cl README 
LSRC= Makefile atoi.cl stack.test

CC=g++
CFLAGS=-g

# %.c: %.o
	# ${CC} ${CFLAGS} -c $<

all: hello

hello: ${CSRC}
	${CC} -o ${BUILDIR}Lexer ${CFLAGS} ${SOURCEFOLDER}${LEXSRC} ${WARN}
	${CC} -o ${BUILDIR}Parser ${CFLAGS} ${SOURCEFOLDER}${PARSRC} ${WARN}
# ${CC} -o ${BUILDIR}TokenList ${CFLAGS} ${SOURCEFOLDER}${TOKLISTSRC} ${WARN}


compile: stack.s

stack.s: stack.cl atoi.cl
	${CLASSDIR}/bin/coolc stack.cl atoi.cl 

test:	compile
	@echo stack.test
	${CLASSDIR}/bin/spim -file stack.s < stack.test

clean :
	rm -f bin/Parser bin/Lexer  bin/TokenList
