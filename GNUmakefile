CFLAGS += -lzxcvbn -Ilibcobalt -Llibcobalt -lcobalt -lm -lncurses
BINDIR := /usr/bin
SBINDIR := /usr/sbin

all:
	$(MAKE) CFLAGS=-fPIC -C libcobalt
	$(MAKE) -C doas
	$(MAKE) -C fortune
	EXECNAME=cbtutils LIBS=-lncurses ./crunchgen/genmakefile.sh > cbtutils-makefile
	$(MAKE) -f cbtutils-makefile

clean:
	rm -rfv cbtutils-makefile crunchgen/cbtutils crunchgen/entry_points.h
	$(MAKE) -C libcobalt clean
	$(MAKE) -C doas clean
	$(MAKE) -C fortune clean
	find . -name "*.o" -delete

install:
	$(MAKE) -C doas install
	$(MAKE) -C fortune install-datfiles
	$(MAKE) -C units install-lib
	$(MAKE) -C libcobalt install-extras
	install -D crunchgen/cbtutils $(DESTDIR)$(BINDIR)/cbtutils
	mkdir -p $(DESTDIR)$(SBINDIR)
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/cp
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/mv
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/fortune
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/grdc
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/locale
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/ls
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/number
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/tetris
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/units
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/arch
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/banner
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/basename
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/cat
	ln -sf ../bin/cbtutils $(DESTDIR)$(SBINDIR)/chroot
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/cmp
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/comm
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/cut
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/date
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/dd
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/diff
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/dirname
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/echo
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/expr
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/false
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/fold
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/getopt
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/head
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/hostname
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/indent
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/jot
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/kill
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/ln
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/logger
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/logname
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/mkdir
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/mktemp
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/nl
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/printenv
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/printf
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/pwd
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/readlink
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/realpath
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/rev
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/rm
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/rmdir
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/rs
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/seq
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/sleep
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/split
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/tail
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/timeout
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/touch
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/tr
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/true
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/tsort
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/tty
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/uname
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/uniq
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/unvis
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/vis
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/wc
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/yes
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/freq
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/unicode
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/entropy
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/wisdom
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/shsecret
	ln -sf cbtutils $(DESTDIR)$(BINDIR)/unifdef
	# `version` utility is deliberately un-symlinked
	install -m644 -d "${DESTDIR}/usr/share/man"
	cp -rf doc/man1 "${DESTDIR}/usr/share/man"
	cp -rf doc/man3 "${DESTDIR}/usr/share/man"
	cp -rf doc/man5 "${DESTDIR}/usr/share/man"
	cp -rf doc/man6 "${DESTDIR}/usr/share/man"
	cp -rf doc/man8 "${DESTDIR}/usr/share/man"

#TODO: install libcobalt headers
#TODO: other bsd man pages?
#TODO: install man pages
