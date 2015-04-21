CC=gcc
CFLAGS=-g -Wall
LIBS=-lncurses

SRC_DIR=.
EXE_DIR=./exec

EXES = \
    ${EXE_DIR}/helloworld		\
	${EXE_DIR}/simple_read_key	\
	${EXE_DIR}/simple_printw	\
	${EXE_DIR}/simple_scanw		\
	${EXE_DIR}/simple_attr		\
	${EXE_DIR}/simple_mvchgat	\
	${EXE_DIR}/simple_winbox	\
	${EXE_DIR}/simple_winbox2	\
	${EXE_DIR}/simple_color

${EXE_DIR}/%: %.c
	${CC} ${CFLAGS} -o $@ $< ${LIBS}

all: mkdir ${EXES}

mkdir:
	@mkdir -p exec

clean:
	@rm -f ${EXES}