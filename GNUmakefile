CFLAGS += -lzxcvbn -lcobalt -lm -lncurses
BINDIR := /usr/bin
SBINDIR := /usr/sbin

all:
	$(MAKE) -C doas
	$(MAKE) -C fortune
	EXECNAME=cbutils LIBS=-lncurses ./crunchgen/genmakefile.sh > cbutils-makefile
	$(MAKE) -f cbutils-makefile

clean:
	rm -rfv cbutils-makefile crunchgen/cbutils crunchgen/entry_points.h
	$(MAKE) -C doas clean
	$(MAKE) -C fortune clean
	find . -name "*.o" -delete

install:
	$(MAKE) -C doas install
	$(MAKE) -C fortune install-datfiles
	$(MAKE) -C units install-lib
	install -D crunchgen/cbutils $(DESTDIR)$(BINDIR)/cbutils
	mkdir -p $(DESTDIR)$(SBINDIR)
	ln -sf cbutils $(DESTDIR)$(BINDIR)/cp
	ln -sf cbutils $(DESTDIR)$(BINDIR)/mv
	ln -sf cbutils $(DESTDIR)$(BINDIR)/fortune
	ln -sf cbutils $(DESTDIR)$(BINDIR)/grdc
	ln -sf cbutils $(DESTDIR)$(BINDIR)/locale
	ln -sf cbutils $(DESTDIR)$(BINDIR)/ls
	ln -sf cbutils $(DESTDIR)$(BINDIR)/number
	ln -sf cbutils $(DESTDIR)$(BINDIR)/tetris
	ln -sf cbutils $(DESTDIR)$(BINDIR)/units
	ln -sf cbutils $(DESTDIR)$(BINDIR)/arch
	ln -sf cbutils $(DESTDIR)$(BINDIR)/banner
	ln -sf cbutils $(DESTDIR)$(BINDIR)/basename
	ln -sf cbutils $(DESTDIR)$(BINDIR)/cat
	ln -sf ../bin/cbutils $(DESTDIR)$(SBINDIR)/chroot
	ln -sf cbutils $(DESTDIR)$(BINDIR)/cmp
	ln -sf cbutils $(DESTDIR)$(BINDIR)/comm
	ln -sf cbutils $(DESTDIR)$(BINDIR)/cut
	ln -sf cbutils $(DESTDIR)$(BINDIR)/date
	ln -sf cbutils $(DESTDIR)$(BINDIR)/dd
	ln -sf cbutils $(DESTDIR)$(BINDIR)/diff
	ln -sf cbutils $(DESTDIR)$(BINDIR)/dirname
	ln -sf cbutils $(DESTDIR)$(BINDIR)/echo
	ln -sf cbutils $(DESTDIR)$(BINDIR)/expr
	ln -sf cbutils $(DESTDIR)$(BINDIR)/false
	ln -sf cbutils $(DESTDIR)$(BINDIR)/fold
	ln -sf cbutils $(DESTDIR)$(BINDIR)/getopt
	ln -sf cbutils $(DESTDIR)$(BINDIR)/head
	ln -sf cbutils $(DESTDIR)$(BINDIR)/hostname
	ln -sf cbutils $(DESTDIR)$(BINDIR)/indent
	ln -sf cbutils $(DESTDIR)$(BINDIR)/jot
	ln -sf cbutils $(DESTDIR)$(BINDIR)/kill
	ln -sf cbutils $(DESTDIR)$(BINDIR)/ln
	ln -sf cbutils $(DESTDIR)$(BINDIR)/logger
	ln -sf cbutils $(DESTDIR)$(BINDIR)/logname
	ln -sf cbutils $(DESTDIR)$(BINDIR)/mkdir
	ln -sf cbutils $(DESTDIR)$(BINDIR)/mktemp
	ln -sf cbutils $(DESTDIR)$(BINDIR)/nl
	ln -sf cbutils $(DESTDIR)$(BINDIR)/printenv
	ln -sf cbutils $(DESTDIR)$(BINDIR)/printf
	ln -sf cbutils $(DESTDIR)$(BINDIR)/pwd
	ln -sf cbutils $(DESTDIR)$(BINDIR)/readlink
	ln -sf cbutils $(DESTDIR)$(BINDIR)/realpath
	ln -sf cbutils $(DESTDIR)$(BINDIR)/rev
	ln -sf cbutils $(DESTDIR)$(BINDIR)/rm
	ln -sf cbutils $(DESTDIR)$(BINDIR)/rmdir
	ln -sf cbutils $(DESTDIR)$(BINDIR)/rs
	ln -sf cbutils $(DESTDIR)$(BINDIR)/seq
	ln -sf cbutils $(DESTDIR)$(BINDIR)/sleep
	ln -sf cbutils $(DESTDIR)$(BINDIR)/split
	ln -sf cbutils $(DESTDIR)$(BINDIR)/tail
	ln -sf cbutils $(DESTDIR)$(BINDIR)/timeout
	ln -sf cbutils $(DESTDIR)$(BINDIR)/touch
	ln -sf cbutils $(DESTDIR)$(BINDIR)/tr
	ln -sf cbutils $(DESTDIR)$(BINDIR)/true
	ln -sf cbutils $(DESTDIR)$(BINDIR)/tsort
	ln -sf cbutils $(DESTDIR)$(BINDIR)/tty
	ln -sf cbutils $(DESTDIR)$(BINDIR)/uname
	ln -sf cbutils $(DESTDIR)$(BINDIR)/uniq
	ln -sf cbutils $(DESTDIR)$(BINDIR)/unvis
	ln -sf cbutils $(DESTDIR)$(BINDIR)/vis
	ln -sf cbutils $(DESTDIR)$(BINDIR)/wc
	ln -sf cbutils $(DESTDIR)$(BINDIR)/yes
	ln -sf cbutils $(DESTDIR)$(BINDIR)/freq
	ln -sf cbutils $(DESTDIR)$(BINDIR)/unicode
	ln -sf cbutils $(DESTDIR)$(BINDIR)/wisdom
	ln -sf cbutils $(DESTDIR)$(BINDIR)/shsecret
	ln -sf cbutils $(DESTDIR)$(BINDIR)/unifdef
	# `version` utility is deliberately un-symlinked
	install -m755 -d "${DESTDIR}/usr/share/man"
	cp -rf doc/man1 "${DESTDIR}/usr/share/man"
	cp -rf doc/man5 "${DESTDIR}/usr/share/man"
	cp -rf doc/man6 "${DESTDIR}/usr/share/man"
	cp -rf doc/man8 "${DESTDIR}/usr/share/man"
