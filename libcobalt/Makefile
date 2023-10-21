LIB=	cobalt
SHLIB_MAJOR=0
SHLIB_MINOR=0

CFLAGS += -I.

HDRS=base64.h icdb.h md5.h ohash.h openbsd.h readpassphrase.h rmd160.h sha1.h sha2.h siphash.h util.h vis.h
SYSHDRS=cdefs.h tree.h

includes:
	mkdir -p "${DESTDIR}/usr/include/sys"
	for i in ${HDRS}; do \
		j="cmp -s $$i ${DESTDIR}/usr/include/$$i || \
		${INSTALL} ${INSTALL_COPY} -m 644 $$i ${DESTDIR}/usr/include"; \
		echo $$j; \
		eval "$$j"; \
	done
	for i in ${SYSHDRS}; do \
		j="cmp -s sys/$$i ${DESTDIR}/usr/include/sys/$$i || \
		${INSTALL} ${INSTALL_COPY} -m 644 sys/$$i ${DESTDIR}/usr/include/sys"; \
		echo $$j; \
		eval "$$j"; \
	done

SRCS =	pledge.c \
	getprogname.c \
	strtonum.c \
	pwcache.c \
	setmode.c \
	warnc.c \
	vwarnc.c \
	malloc.c \
	errc.c \
	verrc.c \
	getbsize.c \
	fmt_scaled.c \
	ohash.c \
	vis.c \
	unvis.c \
	strmode.c \
	base64.c \
	siphash.c \
	radixsort.c \
	icdb.c \
	md5.c \
	rmd160.c \
	sha1.c \
	sha2.c \
	readpassphrase.c \
	strlcpy.c \
	strlcat.c \
	fgetln.c

.include <bsd.lib.mk>
.include <bsd.subdir.mk>
#TODO: man pages
