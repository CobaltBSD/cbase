# We build doas separately and uncrunched, so that we don't need to setuid the entire cbtutils binary

CFLAGS+=-I../libcobalt
LDFLAGS+=-lcobalt -L../libcobalt

MAN=	doas.1 doas.conf.5
SRCS=	doas.c env.c shadow.c y.tab.c
PROG=	doas
BINMODE=4755

CLEANFILES += y.tab.c

y.tab.c:
	byacc parse.y

.include <bsd.prog.mk>
