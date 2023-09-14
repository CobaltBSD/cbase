#	$OpenBSD: Makefile,v 1.7 2016/09/02 11:55:24 tb Exp $
#	$NetBSD: Makefile,v 1.15 1996/02/29 00:21:16 jtc Exp $
#	@(#)Makefile	8.2 (Berkeley) 4/19/94

SRCS=	fortunes fortunes-o startrek zippy recipes limerick
BLDS=	fortunes.dat startrek.dat zippy.dat \
	fortunes-o.dat recipes.dat limerick.dat
#TODO should probably only install .dat files

# TO INSTALL THE POTENTIALLY OFFENSIVE FORTUNES, UNCOMMENT THE THREE
# LINES AND COMMENT OUT THE FOURTH LINE.

CLEANFILES+=${BLDS}

STRFILE!=cd $(.CURDIR)/../strfile; \
	printf "xxx:\n\techo \$${.OBJDIR}/strfile\n" | \
	${MAKE} -r -s -f - xxx | grep strfile

all: ${BLDS}

install: ${SRCS} ${BLDS}
	(cd ${.CURDIR} && ${INSTALL} -d ${DESTDIR}/usr/share/fortunes/ && ${INSTALL} ${INSTALL_COPY} -m 444 \
	    ${SRCS} ${DESTDIR}/usr/share/fortunes/)
	${INSTALL} ${INSTALL_COPY} -D -m 444 ${BLDS} \
	    ${DESTDIR}/usr/share/fortunes

fortunes.dat fortunes-o.dat limerick.dat startrek.dat zippy.dat recipes.dat:
	${STRFILE} -s ${.CURDIR}/${.TARGET:R} ${.TARGET}

.include <bsd.prog.mk>
