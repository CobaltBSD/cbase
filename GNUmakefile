# Builds a standalone libopenbsd.so and make utility

CFLAGS := -Llibopenbsd -lopenbsd -Ilibopenbsd

PREFIX := /usr

MAGICVARSLOTS=82
MAGICCONDSLOTS=65

all: make/make

libopenbsd/libopenbsd.so:
	$(CC) -fPIC -shared -Ilibopenbsd \
		libopenbsd/pledge.c \
		libopenbsd/getprogname.c \
		libopenbsd/strtonum.c \
		libopenbsd/pwcache.c \
		libopenbsd/setmode.c \
		libopenbsd/warnc.c \
		libopenbsd/vwarnc.c \
		libopenbsd/strtofflags.c \
		libopenbsd/fts.c \
		libopenbsd/malloc.c \
		libopenbsd/errc.c \
		libopenbsd/verrc.c \
		libopenbsd/logwtmp.c \
		libopenbsd/getbsize.c \
		libopenbsd/fmt_scaled.c \
		libopenbsd/siphash.c \
		libopenbsd/srandom_deterministic.c \
		libopenbsd/ohash.c \
		libopenbsd/db.c \
		libopenbsd/hash.c \
		libopenbsd/hash_bigkey.c \
		libopenbsd/hash_buf.c \
		libopenbsd/hash_func.c \
		libopenbsd/hash_log2.c \
		libopenbsd/hash_page.c \
		libopenbsd/ndbm.c \
		libopenbsd/base64.c \
		libopenbsd/vis.c \
		libopenbsd/unvis.c \
		libopenbsd/strmode.c \
		-o $@

make/generate: libopenbsd/libopenbsd.so
	$(CC) make/generate.c make/stats.c make/memory.c $(CFLAGS) -o $@

make/varhashconsts.h: make/generate
	LD_LIBRARY_PATH=libopenbsd ./make/generate 1 ${MAGICVARSLOTS} > $@

make/condhashconsts.h: make/generate
	LD_LIBRARY_PATH=libopenbsd ./make/generate 2 ${MAGICCONDSLOTS} > $@

make/nodehashconsts.h: make/generate
	LD_LIBRARY_PATH=libopenbsd ./make/generate 3 0 > $@

make/make: make/varhashconsts.h make/condhashconsts.h make/nodehashconsts.h
	$(CC) \
		make/main.c \
		make/arch.c \
		make/buf.c \
		make/cmd_exec.c \
		make/compat.c \
		make/cond.c \
		make/dir.c \
		make/direxpand.c \
		make/dump.c \
		make/engine.c \
		make/enginechoice.c \
		make/error.c \
		make/expandchildren.c \
		make/for.c \
		make/init.c \
		make/job.c \
		make/lowparse.c \
		make/make.c \
		make/parse.c \
		make/parsevar.c \
		make/str.c \
		make/suff.c \
		make/targ.c \
		make/targequiv.c \
		make/timestamp.c \
		make/var.c \
		make/varmodifiers.c \
		make/varname.c \
		make/memory.c \
		make/stats.c \
		make/lst.lib/lstAddNew.c \
		make/lst.lib/lstAppend.c \
		make/lst.lib/lstConcat.c \
		make/lst.lib/lstConcatDestroy.c \
		make/lst.lib/lstDeQueue.c \
		make/lst.lib/lstDestroy.c \
		make/lst.lib/lstDupl.c \
		make/lst.lib/lstFindFrom.c \
		make/lst.lib/lstForEachFrom.c \
		make/lst.lib/lstInsert.c \
		make/lst.lib/lstMember.c \
		make/lst.lib/lstRemove.c \
		make/lst.lib/lstReplace.c \
		make/lst.lib/lstRequeue.c \
		make/lst.lib/lstSucc.c \
		-Imake $(CFLAGS) -o $@

clean:
	rm -fv libopenbsd/libopenbsd.so make/generate make/varhashconsts.h make/condhashconsts.h make/nodehashconsts.h make/make
