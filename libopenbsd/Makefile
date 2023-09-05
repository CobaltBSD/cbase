LIB=	openbsd
SHLIB_MAJOR=0
SHLIB_MINOR=0

SRCS =	pledge.c \
	getprogname.c \
	strtonum.c \
	pwcache.c \
	setmode.c \
	warnc.c \
	vwarnc.c \
	strtofflags.c \
	fts.c \
	malloc.c \
	errc.c \
	verrc.c \
	logwtmp.c \
	getbsize.c \
	fmt_scaled.c \
	siphash.c \
	srandom_deterministic.c \
	ohash.c \
	db.c \
	hash.c \
	hash_bigkey.c \
	hash_buf.c \
	hash_func.c \
	hash_log2.c \
	hash_page.c \
	ndbm.c \
	base64.c \
	vis.c \
	unvis.c \
	strmode.c

#MAN=	editline.3 editrc.5 editline.7

#CFLAGS+=-Wall

.PHONY: generated
generated: ${GENERATED}
BUILDFIRST = ${GENERATED}

.include <bsd.lib.mk>
.include <bsd.subdir.mk>
