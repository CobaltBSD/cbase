# Since doas requires setuid, it is built separately and un-crunched

CFLAGS+=-I../libcobalt

MAN=	doas.1 doas.conf.5
SRCS=	doas.c env.c shadow.c y.tab.c
PROG=	doas

CLEANFILES += y.tab.c

y.tab.c:
	byacc parse.y

.include <bsd.prog.mk>
