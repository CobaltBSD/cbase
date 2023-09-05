#	$OpenBSD: Makefile,v 1.18 2020/07/30 17:45:44 millert Exp $

MAN=	awk.1
CLEANFILES+=proctab.c maketab awkgram.tab.c awkgram.tab.h
CFLAGS+=-I. -I${.CURDIR} -DHAS_ISBLANK -DNDEBUG

awkgram.tab.c awkgram.tab.h: awkgram.y
	${YACC} -o awkgram.tab.c -d ${.CURDIR}/awkgram.y

BUILDFIRST = awkgram.tab.h

proctab.c: maketab
	./maketab awkgram.tab.h > proctab.c

maketab: awkgram.tab.h maketab.c
	${HOSTCC} ${HOSTCFLAGS} ${.CURDIR}/maketab.c -o $@

all: awkgram.tab.c awkgram.tab.h proctab.c

clean:
	rm -fv maketab

.include <bsd.prog.mk>
