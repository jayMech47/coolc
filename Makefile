
ASSN = 1
CLASS= cs143
CLASSDIR= ../..
LEXSRC= hello.c
PARSRC= parser.c
		
SRC= stack.cl README 
LSRC= Makefile atoi.cl stack.test

CC=gcc
CFLAGS=-g

# %.c: %.o
	# ${CC} ${CFLAGS} -c $<

all: hello

hello: ${CSRC}
	${CC} -o lexer ${CFLAGS} ${LEXSRC}
	${CC} -o parser ${CFLAGS} ${PARSRC}


compile: stack.s

stack.s: stack.cl atoi.cl
	${CLASSDIR}/bin/coolc stack.cl atoi.cl 

test:	compile
	@echo stack.test
	${CLASSDIR}/bin/spim -file stack.s < stack.test

clean :
	rm -f *.s core *~
