CC=gcc
CFLAGS=-g -Wall
LIBS=-lncurses

SRC_DIR=.
EXE_DIR=.

EXES = \
    ${EXE_DIR}/helloworld		\
	${EXE_DIR}/simple_read_key	\
	${EXE_DIR}/simple_printw	\
	${EXE_DIR}/simple_scanw		\
	${EXE_DIR}/simple_attr		\
	${EXE_DIR}/simple_mvchgat

${EXE_DIR}/%: %.c
	${CC} ${CFLAGS} -o $@ $< ${LIBS}

all: ${EXES}

clean:
	@rm -f ${EXES}