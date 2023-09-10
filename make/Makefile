#	$OpenBSD: Makefile,v 1.64 2020/01/13 15:41:53 espie Exp $

MAN=	make.1

CLEANFILES+=generate varhashconsts.h condhashconsts.h nodehashconsts.h

# may need tweaking if you add variable synonyms or change the hash function
MAGICVARSLOTS=82
MAGICCONDSLOTS=65

varhashconsts.h: generate
	${.OBJDIR}/generate 1 ${MAGICVARSLOTS} >$@.tmp && mv $@.tmp $@

condhashconsts.h: generate
	${.OBJDIR}/generate 2 ${MAGICCONDSLOTS} >$@.tmp && mv $@.tmp $@

nodehashconsts.h: generate
	${.OBJDIR}/generate 3 0 >$@.tmp && mv $@.tmp $@

generate: generate.c stats.c memory.c
	${CC} -I../libopenbsd -o ${.TARGET} ${.ALLSRC}

all: varhashconsts.h condhashconsts.h nodehashconsts.h

clean:
	rm -fv generate varhashconsts.h condhashconsts.h nodehashconsts.h

.include <bsd.prog.mk>
