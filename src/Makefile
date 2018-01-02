# Makefile for proj

COMPILER_TYPE= gnu

CC= gcc

PROG= proj
SRCS= proj.c graphics.c vbe.c timer.c keyboard.c mouse.c MemGame.c Bitmap.c rtc.c

CFLAGS= -Wall

DPADD+= ${LIBDRIVER} ${LIBSYS}
LDADD+= -ldriver -lsys -llm

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>
