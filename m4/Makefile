#	$OpenBSD: Makefile,v 1.16 2017/07/09 14:04:50 espie Exp $

MAN=	m4.1

y.tab.c parser.h:
	byacc -b parser -d -H parser.h parser.y

lex.yy.c:
	lex -t tokenizer.l > lex.yy.c

all: y.tab.c parser.h lex.yy.c

clean:
	rm -fv parser.tab.c parser.h lex.yy.c

.include <bsd.prog.mk>
