# Builds a standalone libcobalt.so and make utility

CFLAGS := -Llibcobalt -lcobalt -Ilibcobalt

PREFIX := /usr

MAGICVARSLOTS=82
MAGICCONDSLOTS=65

all: make/make

libcobalt/libcobalt.so:
	$(CC) -fPIC -shared -Ilibcobalt \
		libcobalt/pledge.c \
		libcobalt/getprogname.c \
		libcobalt/strtonum.c \
		libcobalt/pwcache.c \
		libcobalt/setmode.c \
		libcobalt/warnc.c \
		libcobalt/vwarnc.c \
		libcobalt/strtofflags.c \
		libcobalt/fts.c \
		libcobalt/malloc.c \
		libcobalt/errc.c \
		libcobalt/verrc.c \
		libcobalt/logwtmp.c \
		libcobalt/getbsize.c \
		libcobalt/fmt_scaled.c \
		libcobalt/siphash.c \
		libcobalt/srandom_deterministic.c \
		libcobalt/ohash.c \
		libcobalt/db.c \
		libcobalt/hash.c \
		libcobalt/hash_bigkey.c \
		libcobalt/hash_buf.c \
		libcobalt/hash_func.c \
		libcobalt/hash_log2.c \
		libcobalt/hash_page.c \
		libcobalt/ndbm.c \
		libcobalt/base64.c \
		libcobalt/vis.c \
		libcobalt/unvis.c \
		libcobalt/strmode.c \
		-o $@

make/generate: libcobalt/libcobalt.so
	$(CC) make/generate.c make/stats.c make/memory.c $(CFLAGS) -o $@

make/varhashconsts.h: make/generate
	LD_LIBRARY_PATH=libcobalt ./make/generate 1 ${MAGICVARSLOTS} > $@

make/condhashconsts.h: make/generate
	LD_LIBRARY_PATH=libcobalt ./make/generate 2 ${MAGICCONDSLOTS} > $@

make/nodehashconsts.h: make/generate
	LD_LIBRARY_PATH=libcobalt ./make/generate 3 0 > $@

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
	rm -fv libcobalt/libcobalt.so make/generate make/varhashconsts.h make/condhashconsts.h make/nodehashconsts.h make/make
