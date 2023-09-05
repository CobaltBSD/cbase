#	$OpenBSD: Makefile,v 1.4 1997/04/27 20:56:56 millert Exp $

MAN=	units.1

install:
	${INSTALL} ${INSTALL_COPY} -d ${DESTDIR}${PREFIX}/share/misc
	${INSTALL} ${INSTALL_COPY} -m 444 \
	    ${.CURDIR}/units.lib ${DESTDIR}${PREFIX}/share/misc

.include <bsd.prog.mk>
