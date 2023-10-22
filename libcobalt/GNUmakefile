LIB=	cobalt
SHLIB_MAJOR=0
SHLIB_MINOR=0

CFLAGS += -I.

HDRS=base64.h icdb.h md5.h ohash.h openbsd.h readpassphrase.h rmd160.h sha1.h sha2.h siphash.h util.h vis.h tree.h

OBJS =	pledge.o \
	getprogname.o \
	strtonum.o \
	pwcache.o \
	setmode.o \
	warnc.o \
	vwarnc.o \
	malloc.o \
	errc.o \
	verrc.o \
	getbsize.o \
	fmt_scaled.o \
	ohash.o \
	vis.o \
	unvis.o \
	strmode.o \
	base64.o \
	siphash.o \
	radixsort.o \
	icdb.o \
	md5.o \
	rmd160.o \
	sha1.o \
	sha2.o \
	readpassphrase.o \
	strlcpy.o \
	strlcat.o \
	fgetln.o

all: libcobalt.so

clean:
	rm -fv *.o libcobalt.so

libcobalt.so: $(OBJS)
	$(CC) -fPIC -shared $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

includes-install:
	mkdir -p "${DESTDIR}/usr/include/sys"
	for i in ${HDRS}; do \
		j="cmp -s $$i ${DESTDIR}/usr/include/$$i || \
		install -m 644 $$i ${DESTDIR}/usr/include"; \
		echo $$j; \
		eval "$$j"; \
	done

$(OBJS):
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(basename $@).c

#TODO: man pages
